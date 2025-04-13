#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    std::cout << "Parent process started with PID: " << getpid() << std::endl;
    
    // Create a new process using fork()
    pid_t pid = fork();
    
    if (pid < 0) {
        // Error occurred
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    } 
    else if (pid == 0) {
        // Child process
        std::cout << "Child process is running with PID: " << getpid() << std::endl;
        std::cout << "Child's parent PID: " << getppid() << std::endl;
        
        // Child process does some work
        for (int i = 1; i <= 3; i++) {
            std::cout << "Child process counting: " << i << std::endl;
            sleep(1);
        }
        
        std::cout << "Child process terminating" << std::endl;
        return 0;
    } 
    else {
        // Parent process
        std::cout << "Parent created child with PID: " << pid << std::endl;
        
        // Parent does some work
        for (int i = 10; i >= 8; i--) {
            std::cout << "Parent process counting: " << i << std::endl;
            sleep(1);
        }
        
        // Wait for child to complete
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            std::cout << "Child process exited with status: " << WEXITSTATUS(status) << std::endl;
        }
        
        std::cout << "Parent process terminating" << std::endl;
    }
    
    return 0;
}
