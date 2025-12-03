# Process-Executor-Logger

This is a simple C++ utility designed to launch an external executable file, pass custom arguments to it, and log the execution details, including start/end times, execution duration (in milliseconds and seconds), and the process exit code.

## 🌟 Key Features

* **External Process Execution:** Uses the Windows API function `CreateProcessA` to launch any specified executable.
* **Argument Handling:** Allows passing custom options/arguments to the target executable.
* **Path Quoting:** Automatically encloses the executable path in quotes to handle paths containing spaces.
* **Timestamped Logging:** All actions (start, options, exit, duration) are logged with high-resolution timestamps, including milliseconds.
* **Execution Timing:** Accurately measures the total time elapsed for the external process to complete.
* **Synchronous Execution:** Waits for the launched process to finish before reporting the results, ensuring accurate timing and exit code retrieval.

## 🛠️ Prerequisites

* A C++ compiler that supports C++11 or later (e.g., GCC, Clang, or Visual Studio).
* This code uses the `<Windows.h>` header and Windows-specific functions (`CreateProcessA`, `WaitForSingleObject`, `GetExitCodeProcess`, `localtime_s`), so it must be compiled and run on a **Windows operating system**.

## ⚙️ How to Compile

You can compile this program using a standard C++ compiler. If you are using g++ (MinGW/Cygwin) on Windows, the command would typically look like this:

```bash
g++ your_filename.cpp -o ProcessExecutorLogger.exe
```

*(Replace `your_filename.cpp` with the name of the file containing the code.)*

### Or using make

```bash
make
```

### Or using cmake

```bash
make cmake_build
```

## 💻 How to Run

1. Execute the compiled program:

    ```bash
    ./ProcessExecutorLogger.exe
    ```

2. The program will prompt you for two inputs:
    * **The full path to the executable file** (e.g., `C:\Windows\System32\notepad.exe`).
    * **Options (arguments)** for the executable (e.g., a file path for Notepad to open).
3. The utility will then launch the external process, wait for it to finish, and display the execution logs.

## 📝 Example Output

If you run the program and specify `C:\Windows\System32\ping.exe` with options `-n 3 127.0.0.1`, the output will look similar to this:

```bash
Please enter the path to the executable file: C:\Windows\System32\ping.exe
Please enter options (arguments), or leave blank: -n 3 127.0.0.1
[2025-12-03 14:24:25.123] Executing the executable file: C:\Windows\System32\ping.exe
[2025-12-03 14:24:25.123] With options: -n 3 127.0.0.1
<... ping output will appear here ...>
[2025-12-03 14:24:28.456] Process exited with code: 0
[2025-12-03 14:24:28.456] Elapsed time: 3333 ms (3.333 s)
```

## 💡 Code Details

The core logic relies on these components:

* **`LoggingTime()` function:** Handles generating the high-precision `[YYYY-MM-DD HH:MM:SS.mmm]` timestamp using `<chrono>` and `localtime_s`.
* **`cmdline` construction:** The executable path is quoted to protect against spaces: `std::string quotedPath = "\"" + executablePath + "\"";`
* **`CreateProcessA`:** This is the function that executes the program. Notably, the first parameter (`lpApplicationName`) is set to `NULL`, and the full command line (path + options) is passed via the second parameter (`lpCommandLine`).
* **`WaitForSingleObject`:** Pauses the execution of this utility until the launched process terminates (`INFINITE` timeout).
* **`GetExitCodeProcess`:** Retrieves the integer exit code (return value) of the terminated process.
* **Time Measurement:** Uses `std::chrono::high_resolution_clock` to capture `start_tp` and `end_tp` for accurate duration calculation.
