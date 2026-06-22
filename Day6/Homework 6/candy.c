/* candy.c
   Reads candy-data.csv (the "Halloween Candy Rankings" data) and
   stores each candy in a heap-allocated struct. The array holds
   pointers to those structs, and every candy name is also on the
   heap. The first line of the file is column names and is skipped.

   Task 1: read the file, close it, and print every candy name.
   Task 2: list the chocolate candies (upper-case if they also have
           caramel, lower-case if not) and print the percent of
           chocolate candies that also have caramel.
   Task 3: for each of the nine boolean attributes, print the average
           sugar/price/win percent of the candies that have it; then
           print the same averages over the candies whose sugar
           percent is above the overall average, and again over the
           candies whose price percent is above the overall average.
   History:
     Wenhao   June 2026   Created
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_CANDIES 200

/* Candy holds one row of the file. The name is a heap string; the
   nine attributes are booleans stored as ints; the three percents
   are stored as doubles. */
typedef struct {
    char *name;
    int chocolate;
    int fruity;
    int caramel;
    int peanutalmondy;
    int nougat;
    int crispedricewafer;
    int hard;
    int bar;
    int pluribus;
    double sugarpercent;
    double pricepercent;
    double winpercent;
} Candy;

/* The nine boolean attributes, in column order, for printing and for
   looping in Task 3. */
const char *FEATURE_NAMES[9] = {
    "chocolate", "fruity", "caramel", "peanutalmondy", "nougat",
    "crispedricewafer", "hard", "bar", "pluribus"
};

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

/* makeCandy parses one line of the file into a heap-allocated Candy.
   The name (column 0) is copied onto the heap; columns 1-9 are read
   as ints and columns 10-12 as doubles.
   Parameters:
     char *line   one data line of the file (header already skipped)
   Returns:
     Candy *   pointer to a newly allocated, filled-in Candy
   Usage:
     Candy *c = makeCandy(line);
*/
Candy *makeCandy(char *line) {
    Candy *c = malloc(sizeof(Candy));

    char field[1000];
    char *p = line;
    int col = 0;

    while (p != NULL) {
        p = getNextField(p, field);
        if (p != NULL) {
            switch (col) {
                case 0:
                    c->name = malloc(strlen(field) + 1);
                    strcpy(c->name, field);
                    break;
                case 1:  c->chocolate = atoi(field);        break;
                case 2:  c->fruity = atoi(field);           break;
                case 3:  c->caramel = atoi(field);          break;
                case 4:  c->peanutalmondy = atoi(field);    break;
                case 5:  c->nougat = atoi(field);           break;
                case 6:  c->crispedricewafer = atoi(field); break;
                case 7:  c->hard = atoi(field);             break;
                case 8:  c->bar = atoi(field);              break;
                case 9:  c->pluribus = atoi(field);         break;
                case 10: c->sugarpercent = atof(field);     break;
                case 11: c->pricepercent = atof(field);     break;
                case 12: c->winpercent = atof(field);       break;
            }
            col++;
        }
    }

    return c;
}

/* featureValue returns the boolean attribute of a candy named by an
   index 0-8 that matches FEATURE_NAMES. This lets Task 3 loop over
   the nine attributes without repeating code.
   Parameters:
     Candy *c    the candy to inspect
     int index   which attribute (0 = chocolate, ... 8 = pluribus)
   Returns:
     int   1 if the candy has that attribute, 0 otherwise
   Usage:
     if (featureValue(c, 0)) { ... candy has chocolate ... }
*/
int featureValue(Candy *c, int index) {
    switch (index) {
        case 0: return c->chocolate;
        case 1: return c->fruity;
        case 2: return c->caramel;
        case 3: return c->peanutalmondy;
        case 4: return c->nougat;
        case 5: return c->crispedricewafer;
        case 6: return c->hard;
        case 7: return c->bar;
        case 8: return c->pluribus;
    }
    return 0;
}

/* printUpper prints a string in upper case followed by a newline.
   Parameters:
     char *str   the string to print
   Returns:
     void
   Usage:
     printUpper(c->name);
*/
void printUpper(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        putchar(toupper((unsigned char) str[i]));
    }
    putchar('\n');
}

/* printLower prints a string in lower case followed by a newline.
   Parameters:
     char *str   the string to print
   Returns:
     void
   Usage:
     printLower(c->name);
*/
void printLower(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        putchar(tolower((unsigned char) str[i]));
    }
    putchar('\n');
}

/* printAverages prints the average sugar, price and win percent over
   the candies whose include flag is set. It is the shared worker for
   all of Task 3.
   Parameters:
     const char *label   text printed in front of the averages
     Candy **candies      the array of candy pointers
     int count            how many candies are in the array
     int *include         per-candy flag: 1 = use it, 0 = skip it
   Returns:
     void
   Usage:
     printAverages("chocolate", candies, count, include);
*/
void printAverages(const char *label, Candy **candies, int count, int *include) {
    double sumSugar = 0.0;
    double sumPrice = 0.0;
    double sumWin = 0.0;
    int n = 0;

    for (int i = 0; i < count; i++) {
        if (include[i]) {
            sumSugar = sumSugar + candies[i]->sugarpercent;
            sumPrice = sumPrice + candies[i]->pricepercent;
            sumWin = sumWin + candies[i]->winpercent;
            n++;
        }
    }

    if (n == 0) {
        printf("%-22s (no candies)\n", label);
        return;
    }

    printf("%-22s avg sugar %.4f   avg price %.4f   avg win %.4f\n",
           label, sumSugar / n, sumPrice / n, sumWin / n);
}

/* main asks for the file name, skips the header, reads every candy
   into a heap-allocated array of Candy pointers, then runs Tasks 1-3.
   Parameters:
     void
   Returns:
     int   0 on success, 1 if the file could not be opened
   Usage:
     run the program and enter the path to candy-data.csv
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

    Candy *candies[MAX_CANDIES];
    int count = 0;

    char line[1000];

    /* discard the header line */
    fgets(line, 1000, inFile);

    /* read every data line into a heap Candy */
    while (fgets(line, 1000, inFile) != NULL && count < MAX_CANDIES) {
        killNewline(line);
        if (strlen(line) == 0) {
            continue;
        }
        candies[count] = makeCandy(line);
        count++;
    }

    fclose(inFile);

    /* ---------- Task 1: print every candy name ---------- */
    printf("All candies:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", candies[i]->name);
    }

    /* ---------- Task 2: chocolate candies and caramel percent ---------- */
    printf("\nChocolate candies (UPPER = has caramel, lower = no caramel):\n");
    int chocolateCount = 0;
    int chocCaramelCount = 0;

    for (int i = 0; i < count; i++) {
        if (candies[i]->chocolate) {
            chocolateCount++;
            if (candies[i]->caramel) {
                chocCaramelCount++;
                printUpper(candies[i]->name);
            } else {
                printLower(candies[i]->name);
            }
        }
    }

    if (chocolateCount > 0) {
        double pct = 100.0 * chocCaramelCount / chocolateCount;
        printf("\n%.2f%% of chocolate candies also have caramel.\n", pct);
    }

    /* ---------- Task 3: summary information ---------- */
    int include[MAX_CANDIES];

    printf("\nAverages by attribute:\n");
    for (int f = 0; f < 9; f++) {
        for (int i = 0; i < count; i++) {
            include[i] = featureValue(candies[i], f);
        }
        printAverages(FEATURE_NAMES[f], candies, count, include);
    }

    /* overall average sugar and price, used as the thresholds below */
    double totalSugar = 0.0;
    double totalPrice = 0.0;
    for (int i = 0; i < count; i++) {
        totalSugar = totalSugar + candies[i]->sugarpercent;
        totalPrice = totalPrice + candies[i]->pricepercent;
    }
    double avgSugar = (count > 0) ? totalSugar / count : 0.0;
    double avgPrice = (count > 0) ? totalPrice / count : 0.0;

    printf("\nAverages over candies above the mean:\n");

    for (int i = 0; i < count; i++) {
        include[i] = (candies[i]->sugarpercent > avgSugar);
    }
    printAverages("sugar above average", candies, count, include);

    for (int i = 0; i < count; i++) {
        include[i] = (candies[i]->pricepercent > avgPrice);
    }
    printAverages("price above average", candies, count, include);

    /* free the heap memory */
    for (int i = 0; i < count; i++) {
        free(candies[i]->name);
        free(candies[i]);
    }

    return 0;
}