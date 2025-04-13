#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    std::cout << "Parent process started with PID: " << getpid() << std::endl;
    
    // Create a new process using vfork()
    pid_t pid = vfork();
    
    if (pid < 0) {
        // Error occurred
        std::cerr << "vfork failed!" << std::endl;
        return 1;
    } 
    else if (pid == 0) {
        // Child process
        std::cout << "Child process is running with PID: " << getpid() << std::endl;
        
        // Execute a new program
        char* args[] = {(char*)"ls", (char*)"-la", NULL};
        execvp("ls", args);
        
        // If exec fails, we'll reach here
        std::cerr << "Exec failed: " << strerror(errno) << std::endl;
        _exit(1);  // Must use _exit() with vfork, not exit()
    } 
    else {
        // Parent process
        // With vfork(), parent execution is suspended until child calls exec() or _exit()
        std::cout << "Parent continues after child called exec or _exit" << std::endl;
        std::cout << "Parent created child with PID: " << pid << std::endl;
        
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
