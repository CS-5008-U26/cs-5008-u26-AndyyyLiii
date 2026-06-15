/* printCsv.c
   Asks for the name of a CSV file and prints its contents.
   Each line is printed whole between > and <, then each field on
   that line (separated by commas) is printed on its own line, also
   between > and <. If a field is wrapped in double quotes, the
   quotes are removed.
   History:
     Wenhao   June 2026   Created
*/

#include <stdio.h>
#include <string.h>

int main() {
    char buffer[1000];

    /* ask the user for the file name */
    printf("Enter the file name: ");
    fgets(buffer, 1000, stdin);

    /* fgets keeps the newline at the end, so remove it */
    if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
    }

    /* open the file */
    FILE *inFile = fopen(buffer, "r");
    if (inFile == NULL) {
        printf("Could not open file: %s\n", buffer);
        return 1;
    }

    char line[1000];

    /* read the file one line at a time */
    while (fgets(line, 1000, inFile) != NULL) {

        /* remove the newline from the end of this line too */
        if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        /* print the whole line first */
        printf(">%s<\n", line);

        /* now walk through the line and pull out one field at a time */
        char field[1000];
        int f = 0;   /* index into field */

        for (int i = 0; i <= strlen(line); i++) {

            if (line[i] == ',' || line[i] == '\0') {
                /* reached the end of a field, finish it off */
                field[f] = '\0';

                /* if the field starts and ends with a double quote,
                   remove the quotes */
                int len = strlen(field);
                if (len >= 2 && field[0] == '"' && field[len - 1] == '"') {
                    field[len - 1] = '\0';
                    for (int j = 0; field[j] != '\0'; j++) {
                        field[j] = field[j + 1];
                    }
                }

                /* print this field */
                printf("    >%s<\n", field);

                f = 0;   /* start collecting the next field */
            } else {
                /* still inside a field, keep collecting characters */
                field[f] = line[i];
                f++;
            }
        }
    }

    fclose(inFile);
    return 0;
}