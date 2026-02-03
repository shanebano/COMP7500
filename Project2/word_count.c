#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int word_count(const char *data) { // Accept char * parameter
    printf("(word_count.c): Process 2 is counting words now ...\n");

    int count = 0;
    int in_word = 0;

    // Iterate through each character in the data
    for (size_t i = 0; i < strlen(data); i++) { // Loop through each character
        if (data[i] == ' ' || data[i] == '\n' || data[i] == '\t') { // Check for whitespace characters
            in_word = 0; // Not in a word
        } else if (in_word == 0) { // Encounter a non-whitespace character and we are not already in a word
            in_word = 1; // Now in a word
            count++; // Increment word count
        }
    }

    return count; // Return the total word count
}