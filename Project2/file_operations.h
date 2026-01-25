/**
 * file_operations.h
 * 
 * Header file for file operation functions
 * Handles file reading and word counting operations
 * 
 * Author: Shane Bano
 * Date: January 25, 2026
 */

#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#define MAX_FILE_SIZE 1048576  // 1MB limit

/**
 * Read file contents and return as string
 * 
  * *filename The name of the file to read
 * **content Pointer to store the file content
 * 0 on success, -1 on error
 */
int read_file(const char *filename, char **content);

/**
 * Count words in a string
 * Words are separated by whitespace characters
 * 
 * test is The text to count words in
 * return the Number of words
 */
int count_words(const char *text);

#endif /* FILE_OPERATIONS_H */