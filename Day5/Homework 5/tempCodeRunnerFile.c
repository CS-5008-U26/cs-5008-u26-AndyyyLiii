/* cities.c
   Reads the uscities.csv file and looks at the 20 largest US cities
   (the file is already sorted by population, biggest first). The
   first line is column names and is skipped. The program prints the
   sum of the populations of those 20 cities and the name of the
   northernmost one (the city with the largest latitude).
   Only three columns are used: column 2 (city name), column 7
   (latitude) and column 9 (population).
   History:
     Wenhao   June 2026   Created
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* killNewline removes a trailing newline from a string, if present.
   fgets leaves the '\n' at the end of what it reads, so this trims it.
   Parameters:
     char *str   the string to trim (modified in place)
   Returns:
     void
   Usage:
     killNewline(line);
*/
void killNewline(char *str) {
    if (strlen(str) > 0 && str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
}

/* getNextField copies the next comma-separated field of a line into
   out and returns a pointer to the rest of the line (just past the
   comma). If the field is wrapped in double quotes, they are removed.
   Parameters:
     char *start   pointer to the start of the remaining line
     char *out     buffer that receives the next field
   Returns:
     char *   pointer to the rest of the line, or NULL if none remains
   Usage:
     char *p = line;
     while (p != NULL) {
         p = getNextField(p, field);
         if (p != NULL) { ...use field... }
     }
*/
char *getNextField(char *start, char *out) {
    if (*start == '\0') {
        return NULL;
    }

    char *sepPointer = strchr(start, ',');
    char *rest;

    if (sepPointer == NULL) {
        strcpy(out, start);
        rest = start + strlen(start);
    } else {
        int len = sepPointer - start;
        strncpy(out, start, len);
        out[len] = '\0';
        rest = sepPointer + 1;
    }

    int outLen = strlen(out);
    if (outLen >= 2 && out[0] == '"' && out[outLen - 1] == '"') {
        out[outLen - 1] = '\0';
        for (int i = 0; out[i] != '\0'; i++) {
            out[i] = out[i + 1];
        }
    }

    return rest;
}

/* main asks the user for the CSV file name, skips the header line,
   then reads the next 20 cities. For each city it splits the line
   into fields, keeps the city name, latitude and population, adds up
   the populations and tracks the city with the largest latitude.
   Finally it prints the total population and the northernmost city.
   Parameters:
     void
   Returns:
     int   0 on success, 1 if the file could not be opened
   Usage:
     run the program and enter the path to uscities.csv
*/
int main() {
    char buffer[1000];

    printf("Enter the file name: ");
    fgets(buffer, 1000, stdin);
    killNewline(buffer);

    FILE *inFile = fopen(buffer, "r");
    if (inFile == NULL) {
        printf("Could not open file: %s\n", buffer);
        return 1;
    }

    char line[1000];

    fgets(line, 1000, inFile);

    long totalPop = 0;
    double maxLat = -1000.0;
    char northCity[1000] = "";

    for (int count = 0; count < 20; count++) {

        if (fgets(line, 1000, inFile) == NULL) {
            break;
        }
        killNewline(line);

        char cityName[1000] = "";
        double latitude = 0.0;
        int population = 0;

        char field[1000];
        char *p = line;
        int col = 0;

        while (p != NULL) {
            p = getNextField(p, field);
            if (p != NULL) {
                if (col == 1) {
                    strcpy(cityName, field);
                } else if (col == 6) {
                    latitude = atof(field);
                } else if (col == 8) {
                    population = atoi(field);
                }
                col++;
            }
        }

        totalPop = totalPop + population;

        if (latitude > maxLat) {
            maxLat = latitude;
            strcpy(northCity, cityName);
        }
    }

    fclose(inFile);

    printf("Sum of the populations: %ld\n", totalPop);
    printf("Northernmost city is %s\n", northCity);

    return 0;
}