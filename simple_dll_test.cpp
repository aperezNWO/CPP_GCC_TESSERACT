/*

TOOL CHAIN : C:\msys64\ucrt64\bin

g++ -std=c++11 -Wall -Wextra -I"include" test_simple_dll.cpp -o test_simple_dll.exe -L"lib" -l:tensorflow.lib


*/

#include <iostream>
#include <windows.h>

// Define a function pointer type that matches the exported function signature
typedef const char* (__cdecl *CallTFVersionFunc)();
typedef const char* (__cdecl *CallOcrFunc)();

int main() {
    // Load the DLL
    HINSTANCE hDLL = LoadLibraryA("TensorFlowApp64_CPP.dll"); // Replace "your_tensorflow_dll.dll" with the actual name of your DLL

    if (hDLL == nullptr) {
        std::cerr << "Error loading DLL: " << GetLastError() << std::endl;
        return 1;
    }
 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    CallOcrFunc callOcrFunc = (CallTFVersionFunc)GetProcAddress(hDLL, "GetTensorFlowOcrOutput");


    if (callOcrFunc == nullptr) {
        std::cerr << "Error getting function address for OCR: " << GetLastError() << std::endl;
        FreeLibrary(hDLL);
        return 1;
    }

    // Call the exported function
    std::cout << "Calling OCR function from DLL..." << std::endl;

    const char* ocrOutput = callOcrFunc();

    if (ocrOutput != nullptr) {
        std::cout << "OCR Output: " << ocrOutput << std::endl;
    } else {
        std::cerr << "Error: GetTensorFlowOcrOutput returned a null pointer." << std::endl;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Free the DLL
    FreeLibrary(hDLL);

    return 0;
}



