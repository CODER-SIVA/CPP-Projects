#include <iostream>
#include <cstdio>
#include <string>
#include <array>
#include <unistd.h>

int main() {
    std::cout << "Parent process started with PID: " << getpid() << std::endl;
    
    // Execute a command and capture its output using popen()
    std::cout << "Executing command using popen()..." << std::endl;
    
    FILE* pipe = popen("ls -la", "r");
    if (!pipe) {
        std::cerr << "popen() failed!" << std::endl;
        return 1;
    }
    
    // Read output from the command
    std::cout << "\nCommand output:" << std::endl;
    std::cout << "------------------------------" << std::endl;
    
    std::array<char, 128> buffer;
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        std::cout << buffer.data();
    }
    
    std::cout << "------------------------------" << std::endl;
    
    // Close the pipe and get the command's exit status
    int status = pclose(pipe);
    
    std::cout << "Command executed with status: " << status << std::endl;
    
    return 0;
}
