#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <Windows.h>
#include <vector>

std::string LoggingTime() {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm;
    localtime_s(&now_tm, &now_c);

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::stringstream ss;
    ss << "[" << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S")
       << "." << std::setfill('0') << std::setw(3) << ms.count() << "]";
    return ss.str();
}

int main() {
    std::string executablePath;
    std::string options;

    std::cout << "Please enter the path to the executable file: ";
    std::getline(std::cin, executablePath);
    if (executablePath.find('"') != std::string::npos) {
        std::cerr << "Error: Executable path cannot contain quote characters." << std::endl;
        return 1;
    }

    std::cout << "Please enter options (arguments), or leave blank: ";
    std::getline(std::cin, options);

    std::cout << LoggingTime() << " Executing the executable file: " << executablePath << std::endl;
    if (!options.empty()) {
        std::cout << LoggingTime() << " With options: " << options << std::endl;
    }
    // Add: Enclose the path in quotes in case it contains spaces
    std::string quotedPath = "\"" + executablePath + "\"";
    std::string cmdline = quotedPath;
    if (!options.empty()) {
        cmdline += " " + options;
    }
    std::vector<char> cmdline_buf(cmdline.begin(), cmdline.end());
    cmdline_buf.push_back('\0');

    // Execute the executable file in a separate window using CreateProcess
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Record start time
    auto start_tp = std::chrono::high_resolution_clock::now();

    // Set the first argument of CreateProcessA to NULL to pass the executable path as a command line argument
    if (!CreateProcessA(
        NULL,   // Application name
        cmdline_buf.data(), // Command line
        NULL,          // Process attributes
        NULL,          // Thread attributes
        FALSE,         // Do not inherit handles
        0,              // Creation flags (if you want to create a new window, use CREATE_NEW_CONSOLE)
        NULL,          // Environment block
        NULL,          // Current directory
        &si,           // STARTUPINFO
        &pi            // PROCESS_INFORMATION
    )) {
        std::cerr << LoggingTime() << " Failed to execute the executable file. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    // Wait until the process completes
    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode = 0;
    if (GetExitCodeProcess(pi.hProcess, &exitCode)) {
        std::cout << LoggingTime() << " Process exited with code: " << exitCode << std::endl;
    } else {
        std::cerr << LoggingTime() << " Failed to get exit code. Error code: " << GetLastError() << std::endl;
    }

    // Record end time and calculate elapsed time
    auto end_tp = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_tp - start_tp).count();
    std::cout << LoggingTime() << " Elapsed time: " << elapsed_ms << " ms"
              << " (" << std::fixed << std::setprecision(3) << (elapsed_ms / 1000.0) << " s)" << std::endl;

    // Close the process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
