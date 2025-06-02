#include "FileSystem.h"
#include "CommandUtils.h"
#include "CommandHandler.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

mutex fs_mutex;

void threadFunction(int threadId, FileSystem& fs) {
    string inputFile = "input_thread" + to_string(threadId) + ".txt";
    string outputFile = "output_thread" + to_string(threadId) + ".txt";
    
    ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        cout << "Thread " << threadId << ": Failed to open " << inputFile << endl;
        return;
    }

    ofstream outFile(outputFile);
    CommandHandler handler(fs);
    string line;
    
    while (getline(inFile, line)) {
        if (!line.empty()) {
            lock_guard<mutex> lock(fs_mutex);
            string result = handler.processCommand(line);
            if (!result.empty()) {
                outFile << "Thread " << threadId << ": " << result << endl;
                cout << "Thread " << threadId << ": " << result << endl;
            }
        }
    }

    inFile.close();
    outFile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <number_of_threads>" << endl;
        return 1;
    }

    int threadCount = stoi(argv[1]);
    FileSystem fs;
    
    // Load initial file system state if needed
    if (ifstream("dil.dat").good()) {
        fs.loadFromFile("dil.dat");
    }

    vector<thread> threads;
    
    // Launch threads
    for (int i = 1; i <= threadCount; i++) {
        threads.push_back(thread(threadFunction, i, ref(fs)));
    }

    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }

    // Save final state
    fs.saveToFile("dil.dat");
    cout << "All threads completed. File system saved." << endl;

    return 0;
}