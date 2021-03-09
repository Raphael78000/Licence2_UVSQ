#include "api.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Bad usage: %s src dest\n"
               "   - src : source directory\n"
               "   - dest: phantom directory\n", argv[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
