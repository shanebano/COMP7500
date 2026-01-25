
/* Word Count Algorithim */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1024 // Maximum buffer size for reading input 

int word_count{
    char buffer[MAX_BUFFER];
    int count = 0;
    int in_word = 0;

    while (fgets(buffer, MAX_BUFFER, stdin) != NULL) { // Read input line by line
        for (size_t i = 0;i < strlen(buffer); i++) { // Iterate through each character in the buffer
            if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') { // Check for whitespace characters
                in_word = 0; //not in a word
            } else if (in_word == 0) { //encounter a non-whitespace character and we are not already in a word
                in_word = 1; // now in a word
                count++;
            }
        }
    }

    return count;
}