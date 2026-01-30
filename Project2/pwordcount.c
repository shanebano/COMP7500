#include <stdio.h>
#include <stdlib.h>
#include "process_communication.h"

int main(int argc, char *argv[]) {
    // Check for correct number of arguments
    if (argc != 2) {
        fprintf(stderr, "Error: Wrong number of input arguments.\nUsage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Call process_communication to handle the rest
    process_communication(argv[1]);

    return EXIT_SUCCESS;
}