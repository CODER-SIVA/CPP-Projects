#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

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
        
        // Replace the child process with a new program using exec
        char* args[] = {(char*)"ls", (char*)"-la", NULL};
        execvp("ls", args);
        
        // If exec fails, we'll reach here
        std::cerr << "Exec failed: " << strerror(errno) << std::endl;
        return 1;
    } 
    else {
        // Parent process
        std::cout << "Parent created child with PID: " << pid << std::endl;
        std::cout << "Parent is waiting for child to complete..." << std::endl;
        
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
