#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

// Note: This is a simplified example since the actual clone() system call
// is Linux-specific and not available on macOS. This example simulates
// the concept using fork() instead.

// Function to be executed by the child process
static int childFunc(void* arg) {
    std::cout << "Child process is running with PID: " << getpid() << std::endl;
    std::cout << "Child's parent PID: " << getppid() << std::endl;
    
    // Execute some command
    char* args[] = {(char*)"ls", (char*)"-la", NULL};
    execvp("ls", args);
    
    // If exec fails, we'll reach here
    std::cerr << "Exec failed: " << strerror(errno) << std::endl;
    return 1;
}

int main() {
    std::cout << "Parent process started with PID: " << getpid() << std::endl;
    std::cout << "NOTE: This is a simulated clone() example using fork() since clone() is Linux-specific" << std::endl;
    
    // Create child process using fork() instead of clone()
    pid_t pid = fork();
    
    if (pid == -1) {
        std::cerr << "fork failed: " << strerror(errno) << std::endl;
        return 1;
    }
    
    if (pid == 0) {
        // Child process
        return childFunc(NULL);
    }
    
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
    
    return 0;
}
