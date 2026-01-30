#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "process_communication.h"

#define BUFFER_SIZE 1024

void process_communication() {
    printf("(process_communications.c) Process 1 starts sending data to Process 2 ...\n");

    int pipe_fd[2];
    pid_t pid;
    char write_msg[] = "Message from parent to child";
    char read_msg[BUFFER_SIZE];

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        printf("(process_communications.c) Process 2 finishes receiving data from Process 1 ...\n");
        close(pipe_fd[1]); // Close unused write end

        // Read from the pipe
        ssize_t bytes_read = read(pipe_fd[0], read_msg, sizeof(read_msg));
        if (bytes_read < 0) {
            perror("Read failed");
            exit(EXIT_FAILURE);
        }

        close(pipe_fd[0]); // Close read end
        exit(EXIT_SUCCESS);
    } else { // Parent process
        close(pipe_fd[0]); // Close unused read end

        // Write to the pipe
        ssize_t bytes_written = write(pipe_fd[1], write_msg, strlen(write_msg) + 1);
        if (bytes_written < 0) {
            perror("Write failed");
            exit(EXIT_FAILURE);
        }

        close(pipe_fd[1]); // Close write end

        // Wait for child process to finish
        wait(NULL);
    }
}