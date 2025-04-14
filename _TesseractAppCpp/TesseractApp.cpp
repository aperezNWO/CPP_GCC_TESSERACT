/*

g++ -std=c++11 -Wall -Wextra  TesseractApp.cpp -o TesseractApp.exe -m64


*/

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>

// Define function pointer types for the DLL functions
typedef const char* (__cdecl *RunOcrOnImageFunc)(const char*);
typedef const char* (__cdecl *GetTensorFlowOcrOutputFunc)();

int main() {
    // Load the DLL
    HINSTANCE hDll = LoadLibraryA("TensorFlowApp64_CPP.dll");
    if (!hDll) {
        DWORD errorCode = GetLastError(); // Capture the error immediately
        std::cerr << "Failed to load TensorFlowApp64_CPP.dll. Error code: " << errorCode << std::endl;

        // Optional: Format the error message for more detail
        LPVOID errorMsg;
        FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            errorCode,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPSTR)&errorMsg,
            0,
            NULL
        );
        std::cerr << "Error message: " << (LPSTR)errorMsg << std::endl;
        LocalFree(errorMsg);

        return 1;
    }

    // Get the addresses of the exported functions
    GetTensorFlowOcrOutputFunc getOcrOutput = (GetTensorFlowOcrOutputFunc)GetProcAddress(hDll, "GetTensorFlowOcrOutput");

    // Check if the functions were found
    if (!getOcrOutput) {
        std::cerr << "Failed to get function addresses. Error code: " << GetLastError() << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    // Test GetTensorFlowOcrOutput (uses hardcoded "Input.png")
    const char* result2 = getOcrOutput();
    std::cout << "GetTensorFlowOcrOutput result: " << result2 << std::endl;

    // Pause and wait for a keypress
    std::cout << "\nPress any key to exit..." << std::endl;
    _getch();

    // Clean up
    FreeLibrary(hDll);
    return 0;
}
