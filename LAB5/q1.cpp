#include <iostream>
#include <unistd.h> // for fork() function
#include <sys/types.h> // for pid_t data type

int main() {
    pid_t pid;

    // create a new process
    pid = fork();

    if (pid < 0) {
        std::cout << "Error: Fork failed." << std::endl;
        return 1;
    } else if (pid == 0) { // child process
        std::cout << "This is the child process. PID = " << getpid() << ", PPID = " << getppid() << std::endl;
    } else { // parent process
        std::cout << "This is the parent process. PID = " << getpid() << ", PPID = " << getppid() << std::endl;
    }

    return 0;
}

