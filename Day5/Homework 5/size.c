/* size.c
   Prints the size of a file in bytes. The file name may be given as
   a command line argument; if no argument is provided, the program
   asks the user to type the file name. The size is read from the
   stat structure.
   For example:
     ./size ../Resources/uscities.csv
     ../Resources/uscities.csv has 12345 bytes
   History:
     Wenhao   June 2026   Created
*/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

/* killNewline removes a trailing newline from a string, if present.
   Parameters:
     char *str   the string to trim (modified in place)
   Returns:
     void
   Usage:
     killNewline(filename);
*/
void killNewline(char *str) {
    if (strlen(str) > 0 && str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
}

/* main gets a file name, either from the command line argument or by
   asking the user, then prints how many bytes that file contains.
   Parameters:
     int argc      the number of command line arguments
     char *argv[]  the command line arguments (argv[1] is the file name)
   Returns:
     int   0 on success
   Usage:
     run the program with a file name, or run it and type one in
*/
int main(int argc, char *argv[]) {
    char filename[1000];

    if (argc >= 2) {
        strcpy(filename, argv[1]);
    } else {
        printf("Enter the name of a file: ");
        fgets(filename, 1000, stdin);
        killNewline(filename);
    }

    struct stat st;
    if (stat(filename, &st) == 0) {
        printf("%s has %lld bytes\n", filename, (long long) st.st_size);
    } else {
        printf("Could not get info about %s\n", filename);
    }

    return 0;
}