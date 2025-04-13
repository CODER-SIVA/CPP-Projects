#include <iostream>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

int main() {
    std::cout << "Parent process started with PID: " << getpid() << std::endl;
    
    pid_t child_pid;
    char *argv[] = {(char*)"ls", (char*)"-la", NULL};
    
    // Create a new process using posix_spawn
    int status = posix_spawn(&child_pid, "/bin/ls", NULL, NULL, argv, environ);
    
    if (status != 0) {
        std::cerr << "posix_spawn failed: " << strerror(status) << std::endl;
        return 1;
    }
    
    std::cout << "Child process created with PID: " << child_pid << std::endl;
    std::cout << "Parent is waiting for child to complete..." << std::endl;
    
    // Wait for child to complete
    int wait_status;
    waitpid(child_pid, &wait_status, 0);
    
    if (WIFEXITED(wait_status)) {
        std::cout << "Child process exited with status: " << WEXITSTATUS(wait_status) << std::endl;
    }
    
    std::cout << "Parent process terminating" << std::endl;
    
    return 0;
}
