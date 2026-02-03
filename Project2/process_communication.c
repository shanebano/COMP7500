#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "process_communication.h"
#include "word_count.h"

#define BUFFER_SIZE 1024

void process_communication(const char *filename) {
    int pipe_fd[2];   // First pipe: Process 1 -> Process 2
    int pipe_fd2[2];  // Second pipe: Process 2 -> Process 1
    pid_t pid;
    char buffer[BUFFER_SIZE];
    int word_count_result;

    // Create the first pipe
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Create the second pipe
    if (pipe(pipe_fd2) == -1) {
        perror("Second pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();
    if (pid < 0) { // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process (Process 2)
        // Close unused ends of the pipes
        close(pipe_fd[1]);  // Close unused write end of the first pipe
        close(pipe_fd2[0]); // Close unused read end of the second pipe

        // Read from the first pipe
        ssize_t bytes_read = read(pipe_fd[0], buffer, sizeof(buffer)); // Read data into buffer
        if (bytes_read < 0) {
            perror("Read failed");
            exit(EXIT_FAILURE);
        }
        close(pipe_fd[0]); // Close the read end of the first pipe after reading

        printf("(process_communications.c): Process 2 finishes receiving data from Process 1 ...\n");

        // Count the words in the received message using the word_count function
        printf("(word_count.c): Process 2 is counting words now ...\n");
        int count = word_count(buffer); // Pass the buffer directly to word_count

        // Write the word count result to the second pipe
        printf("(process_communications.c): Process 2 is sending the result back to Process 1 ...\n");
        if (write(pipe_fd2[1], &count, sizeof(count)) == -1) {
            perror("Write to second pipe failed");
            exit(EXIT_FAILURE);
        }
        close(pipe_fd2[1]); // Close write end after writing

        exit(EXIT_SUCCESS);
    } else { // Parent process (Process 1)
        // Close unused ends of the pipes
        close(pipe_fd[0]);  // Close unused read end of the first pipe
        close(pipe_fd2[1]); // Close unused write end of the second pipe

        // Print the first message
        printf("(process_communications.c): Process 1 is reading file \"%s\" now ...\n", filename);

        // Open the input file
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            fprintf(stderr, "Error: Unable to open file \"%s\".\n", filename);

            // Kill the child process to ensure it doesn't continue running
            kill(pid, SIGKILL);

            // Exit the program with failure status
            exit(EXIT_FAILURE);
        }

        // Read the file and send its content to the child process
        printf("(process_communications.c): Process 1 starts sending data to Process 2 ...\n");
        size_t bytes_read;
        int file_is_empty = 1; // Flag to check if the file is empty
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            file_is_empty = 0; // File is not empty
            if (write(pipe_fd[1], buffer, bytes_read) == -1) {
                perror("Write to first pipe failed");
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
        fclose(file);
        close(pipe_fd[1]); // Close write end after writing

        // If the file is empty, send an empty string to Process 2
        if (file_is_empty) {
            fprintf(stderr, "Error: File \"%s\" is empty.\n", filename);

            // Kill the child process to ensure it doesn't continue running
            kill(pid, SIGKILL);

            // Exit the program with failure status
            exit(EXIT_FAILURE);
        }

        // Wait for the child process to finish
        wait(NULL);

        // Read the word count result from the second pipe
        if (read(pipe_fd2[0], &word_count_result, sizeof(word_count_result)) == -1) {
            perror("Read from second pipe failed");
            exit(EXIT_FAILURE);
        }
        close(pipe_fd2[0]); // Close read end after reading

        // Print the word count result
        printf("(process_communications.c): Process 1: The total number of words is %d.\n", word_count_result);
    }
}