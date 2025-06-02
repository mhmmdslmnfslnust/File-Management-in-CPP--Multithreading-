#pragma once
#include "FileSystem.h"
#include "CommandUtils.h"
#include <sstream>

class CommandHandler {
private:
    FileSystem& fs;
    std::stringstream output;

public:
    CommandHandler(FileSystem& fileSystem) : fs(fileSystem) {}

    string processCommand(const string& cmdLine) {
        stringstream ss(cmdLine);
        string cmd;
        ss >> cmd;

        output.str("");  // Clear output buffer

        if (cmd == "create") {
            string fname;
            ss >> fname;
            fs.createFile(fname);  // Create new file
        } else if (cmd == "delete") {
            string fname;
            ss >> fname;
            fs.deleteFile(fname);  // Delete specified file
        } else if (cmd == "help") {
            string specificCmd;
            getline(cin, specificCmd);  // Read the rest of the line after "help"
        
            // Trim leading spaces (if any)
            if (!specificCmd.empty() && specificCmd[0] == ' ') {
                specificCmd = specificCmd.substr(1);
            }
        
            if (specificCmd.empty()) {
                fs.showHelp();  // Show general help if no specific command is provided
            } else {
                fs.showSpecificHelp(specificCmd);  // Show help for the specific command
            }
        } else if (cmd == "mkdir") {
            string dname;
            ss >> dname;  
            fs.mkdir(dname);  // Create new directory
        } else if (cmd == "chdir") {
            string dname;
            ss >> dname;  
            fs.chDir(dname);  // Change current directory
        } else if (cmd == "ls") {
            fs.listFiles();  // Lists all files and directories in the current directory
        } else if (cmd == "move") {
            string src, tgt;
            ss >> src >> tgt;  // Read source and target paths
            fs.moveFile(src, tgt);  // Move file from source to target
        } else if (cmd == "open") {
            string fname;
            ss >> fname;           
            fs.openFile(fname);  // Open specified file
        } else if (cmd == "close") {
            string fname;
            ss >> fname;            
            fs.closeFile(fname);  // Close specified file
        } else if (cmd == "write") {
            string fname, text;
            ss >> fname;  
            getline(cin, text);  // Read text to write (allows spaces)
            if (text[0] == ' ') text = text.substr(1);  // Remove leading space if present
            File* file = fs.openFile(fname);  // Get file pointer
            if (file) file->write_to_file(text);  // Write text if file exists
        } else if (cmd == "write_at") {
            string fname;
            int pos;
            string text;
            ss >> fname >> pos;  // Read filename and position
            getline(cin, text);  // Read text to write
            if (text[0] == ' ') text = text.substr(1);
            File* file = fs.openFile(fname);  // Get file pointer
            if (file) file->write_at(pos, text);  // Write at position if file exists
        } else if (cmd == "read") {
            string fname;
            ss >> fname;  // Read filename
            File* file = fs.openFile(fname);  // Get file pointer
            if (file) cout << file->read_from_file() << endl;  // Output file contents
        } else if (cmd == "read_from") {
            string fname;
            int start, size;
            ss >> fname >> start >> size;  // Read filename, start position, and size
            File* file = fs.openFile(fname);  // Get file pointer
            if (file) cout << file->read_from(start, size) << endl;  // Output portion of file
        } else if (cmd == "move_within") {
            string fname;
            int start, size, target;
            ss >> fname >> start >> size >> target;  // Read filename and positions
            File* file = fs.openFile(fname);  // Get file pointer
            if (file) file->move_within_file(start, size, target);  // Move data within file
        } else if (cmd == "truncate") {
            string fname;
            int size;
            ss >> fname >> size;  // Read filename and new size
            File* file = fs.openFile(fname);  // Get file pointer
            if (file) file->truncate_file(size);  // Truncate file to specified size
        } else if (cmd == "memory_map") {
            fs.showMemoryMap();  // Display memory map of file system
        } else if (cmd == "exit") {
            fs.saveToFile("dil.dat");  // Save file system state
            cout << "File system saved. Exiting...\n";
            return output.str();  // Return immediately for exit command
        } else {
            suggestCommand(cmd);  // Handle invalid commands by suggesting similar commands
        }
        

        string result = output.str();
        if (result.empty()) {
            return "Command executed: " + cmdLine + "\n";
        }
        return result;
    }
};
