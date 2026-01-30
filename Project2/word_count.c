#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1024 // Maximum buffer size for reading input 

int word_count(FILE *file) { // Accept FILE * parameter
    printf("(word_count.c): Process 2 is counting words now ...\n");

    char buffer[MAX_BUFFER];
    int count = 0;
    int in_word = 0;

    // Read input from the provided file
    while (fgets(buffer, MAX_BUFFER, file) != NULL) { // Read input line by line
        for (size_t i = 0; i < strlen(buffer); i++) { // Iterate through each character in the buffer
            if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') { // Check for whitespace characters
                in_word = 0; // Not in a word
            } else if (in_word == 0) { // Encounter a non-whitespace character and we are not already in a word
                in_word = 1; // Now in a word
                count++;
            }
        }
    }

    printf("(word_count.c): Process 2 has finished counting words.\n");

    return count; // Return the total word count
}