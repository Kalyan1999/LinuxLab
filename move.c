// Moves <source file> into <destination file>

#include<stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

/**
 * Main function
 * 
 * Usage: move <source file> <destination file>
 * 
 * Ex: 
 * $ mov dest.txt destination.txt
 * Successfully moved %s to %ss
*/
int main(int argc, char *argv[]) {
    // Checking if user passes correct arguments.
    if(argc != 3) {
        printf("Invalid arguments.\nUsage: copy <source file> <destination file>\n");
        return -1;
    }

    /* int link(const char *oldpath, const char *newpath) creates a new link to an existing file.
        Creates a new link (also known as a hard link) to an existing file.
        If newpath exists, it will not be overwritten.
        On success, 0 is returned. On error, -1 is returned */
    if((link(argv[1], argv[2])) == -1) {
        printf("Unable to move file: %s\n", argv[1]);
        return -1;
    }

    /* int unlink(const char *pathname)
        Seletes a name from the filesystem. If that name was the last link to a file and 
        no processes have the file open, the file is deleted and the space it was using 
        is made available for reuse.
        On success, 0 is returned. On error, -1 is returned. */
    if((unlink(argv[1])) == -1) {
        printf("Unable to move file: %s\n", argv[1]);

        // Rolling back changes to prevent any side effects.
        unlink(argv[2]);
        return -1;
    }

    printf("Successfully moved %s to %s\n", argv[1], argv[2]);
    return 0;
}
