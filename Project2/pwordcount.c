#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word_count.h"

// Function to count words in the file
int word_count(FILE *file);

int main(int argc, char *argv[]) {
    if (argc != 2) { // Check for correct number of arguments
        fprintf(stderr, "Error: Wrong number of input arguments.\nUsage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    // Open the specified file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file '%s'. Please ensure the file exists and is accessible.\n", argv[1]);
        return EXIT_FAILURE;
    }

    // Count words in the given file
    int total_words = word_count(file);
    fclose(file);
    // Check for errors during word counting
    if (total_words < 0) {
        fprintf(stderr, "Error: Failed to read the file '%s'.\n", argv[1]);
        return EXIT_FAILURE;
    }

    // Print the word count result
    printf("Process %s: The total number of words is %d.\n", argv[1], total_words);
    return EXIT_SUCCESS;
}
