
/* 
Function to read file contents and return as a string for further processing.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "file_operations.h"

/**
 * Read file contents and return as string
 * 
 * *filename The name of the file to read
 * **content Pointer to store the file content
 * 0 on success, -1 on error
 */

#define MAX_FILE_SIZE 1048576 // 1 MB
int read_file(const char *filename, char **content) { // take filename and pointer to content 
     if (file == NULL) {
        perror("Error opening file"); // print error message
        return -1;
    }

    // Get file size
    fseek(file, 0, SEEK_END); // move to end of file
    long file_size = ftell(file); // get current position (file size)
    fseek(file, 0, SEEK_SET); // move back to beginning of file

    // Check file size limit
    if (file_size > MAX_FILE_SIZE) { // check if file size exceeds limit
        fprintf(stderr, "Error: File too large (max %d bytes)\n", MAX_FILE_SIZE); // print error message 
        fclose(file);
        return -1;
    }

    // Allocate memory for content
    *content = (char *)malloc(file_size + 1); // +1 for null terminator (malloc is used to allocate memory)
    if (*content == NULL) { // check if memory allocation was successful (* used to dereference pointer)
        perror("Error allocating memory");
        fclose(file);
        return -1;
    }

    // Read file content
    size_t bytes_read = fread(*content, 1, file_size, file); // read file content into allocated memory
    (*content)[bytes_read] = '\0'; // null terminate the string because fread does not add null terminator

    fclose(file);
    return 0;
}