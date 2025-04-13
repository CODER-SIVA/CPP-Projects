#include <iostream>
#include <cstdlib>
#include <unistd.h>

int main() {
    std::cout << "Parent process started with PID: " << getpid() << std::endl;
    
    std::cout << "Executing command using system()..." << std::endl;
    
    // Execute a command using system()
    int result = system("ls -la");
    
    std::cout << "Command executed with return status: " << result << std::endl;
    
    // Check if command was executed successfully
    if (result == 0) {
        std::cout << "Command executed successfully" << std::endl;
    } else {
        std::cout << "Command failed with status: " << result << std::endl;
    }
    
    return 0;
}
