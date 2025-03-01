#include <iostream>
#include <unistd.h> // For pipe(), fork(), and read()/write()
#include <string.h> // For strlen()

int main() {
    int pipefd[2]; // File descriptors for the pipe
    pid_t pid;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        std::cerr << "Pipe creation failed!" << std::endl;
        return 1;
    }

    // Fork the process
    pid = fork();
    if (pid < 0) {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }

    if (pid == 0) { // Child process (consumer)
        close(pipefd[1]); // Close the write end of the pipe

        char buffer[100];
        ssize_t bytesRead;

        // Read data from the pipe
        while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            std::cout << "Consumer received: " << buffer << std::endl;
        }

        close(pipefd[0]); // Close the read end of the pipe
    } else { // Parent process (producer)
        close(pipefd[0]); // Close the read end of the pipe

        const char* message = "11129078087354";
        std::cout << "Producer sending: " << message << std::endl;

        // Write data to the pipe
        write(pipefd[1], message, strlen(message) + 1);

        close(pipefd[1]); // Close the write end of the pipe
    }

    return 0;
}