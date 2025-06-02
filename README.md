# File Management in C++ with Multithreading

This project is an extension of the [File Management in C++](https://github.com/yourusername/File-Management-in-CPP) project, adding concurrent file operations through multithreading capabilities. It simulates a file system where multiple threads can simultaneously create, read, write, and manage files and directories.

## 📋 Project Overview
This multithreaded file system simulator demonstrates concurrent file operations with proper synchronization to prevent race conditions. The system processes commands from separate input files for each thread, with operations logged in corresponding output files.

## Description
This project implements a file management system in C++ utilizing multithreading to improve performance for file operations. It demonstrates concurrent file handling techniques for better efficiency when working with large files or multiple file operations.

## ✨ Key Features
- Multithreaded file operations - Multiple threads can work on files simultaneously
- Thread-safe operations - Mutex-based synchronization prevents data corruption
- Efficient file reading and writing
- File search capabilities
- File metadata management
- Command-based interface - Comprehensive set of file and directory management commands
- Persistent storage - File system state is preserved between runs
- Thread-specific input/output - Each thread works with its own input and output files

## 📦 Requirements
- C++17 or later
- Standard C++ libraries (iostream, fstream, thread, vector, mutex)
- POSIX-compliant system (for threading support)
- CMake 3.10+ (for building)

## 🚀 Installation & Setup

### Clone the Repository
```bash
# Clone the repository
git clone https://github.com/yourusername/File-Management-in-CPP--Multithreading-.git

# Navigate to the project directory
cd File-Management-in-CPP--Multithreading-
```

### Compile the Project
```bash
# Using make
make

# Or using g++ directly
g++ -std=c++17 main.cpp -o file_system_mt -pthread
```

### Running the Application
```bash
./file_system_mt <number_of_threads>

# Example:
./file_system_mt 5  # Run with 5 threads
```

## Usage

### Basic Usage
```cpp
// Example usage of the file management system
#include "filemanager.h"

int main() {
    FileManager fm;
    fm.processFiles("path/to/directory");
    return 0;
}
```

### 💻 Thread Input Files
The system uses separate input files for each thread, following this naming convention:
- `input_thread1.txt`
- `input_thread2.txt`
- `input_thread3.txt`
- etc.

Each file contains a series of commands to be executed by its corresponding thread.

### 📝 Output Files
Thread operations are logged in corresponding output files:
- `output_thread1.txt`
- `output_thread2.txt`
- `output_thread3.txt`
- etc.

## 🔒 Synchronization Mechanism
The system uses a mutex (`fs_mutex`) to ensure thread safety. When a thread needs to access the file system, it acquires the mutex, performs its operations, and then releases it, preventing race conditions and ensuring data integrity.

## 📂 Project Structure

### Files and Their Roles
- `main.cpp`: Entry point, manages thread creation and joining
- `FileSystem.h`: Core file system functionality for directory/file operations
- `Directory.h`: Directory data structure definition
- `File.h`: File data structure definition
- `CommandUtils.h`: Utility functions for command processing
- `CommandHandler.h`: Command processing implementation
- `input_threadX.txt`: Input command files for each thread
- `output_threadX.txt`: Output log files for each thread
- `dil.dat`: Persistent storage file for the file system

## 🔍 Supported Commands

| Command | Description |
|---------|-------------|
| `create <filename>` | Create a new file in current directory |
| `delete <filename>` | Delete a file from current directory |
| `mkdir <dirname>` | Create a new directory |
| `chdir <dirname>` | Change to specified directory (use '..' to go up) |
| `ls` | Lists all files and directories in the current directory |
| `move <source> <target>` | Rename/move a file |
| `open <filename>` | Open a file for writing |
| `close <filename>` | Close an opened file |
| `write <filename> <text>` | Write text at the end of file |
| `write_at <filename> <pos> <text>` | Write text at specific position |
| `read <filename>` | Read entire file content |
| `read_from <filename> <start> <size>` | Read part of file |
| `move_within <filename> <start> <size> <target>` | Move internal file data |
| `truncate <filename> <size>` | Cut file size to specified length |
| `memory_map` | Show current directory and files tree |
| `help` | Show available commands |
| `exit` | Exit the program |

## Examples

### 📊 Example Thread Input File
```
create file1.txt
open file1.txt
write file1.txt This is from thread 1
close file1.txt
```

### 📤 Example Thread Output
```
Thread 1: Command executed: create file1.txt
Thread 1: Command executed: open file1.txt
Thread 1: Command executed: write file1.txt This is from thread 1
Thread 1: Command executed: close file1.txt
```

## 🧵 Thread Functionality
Each thread:
- Opens its assigned input file
- Creates its output log file
- Processes commands line by line
- Acquires the mutex before executing commands
- Logs results in its output file
- Releases the mutex
- Closes files when done

## 🔄 Persistence
The file system state is saved to `dil.dat` when all threads complete execution, ensuring that changes persist between program runs. Additionally, a cleaner version of the initial file system structure is available in `sample.dat`, which provides a more consistent starting point for the application.

```
DIR root
DIR root
FILE file02.txt 
DIR main
FILE file.txt My name is Muhammad Suleman Faisal
DIR submain
ENDDIR
ENDDIR
ENDDIR
ENDDIR
```

## Known Issues
- The application currently requires empty key presses during execution (you can press any key and it won't affect execution). This points to an underlying synchronization issue that could be addressed through contributions.

## 📚 Enhancements from Base Project
This multithreaded version builds on the original File Management in C++ with these additional features:
- Concurrent file operations via multiple threads
- Mutex-based synchronization for thread safety
- Thread-specific input/output file processing
- Command-line argument for thread count flexibility

## 🛠️ Future Enhancements
Possible improvements for future versions:
- More granular locking (per-file/directory locks)
- Advanced thread scheduling
- Web-based UI for file system visualization
- Network file sharing capabilities
- Fix for the empty key press requirement during execution

## Contributing
Contributions are welcome! Please feel free to submit a Pull Request.

## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
