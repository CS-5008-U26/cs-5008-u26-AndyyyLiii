/* candy.c
   Reads the candy-data.csv file and stores all candies in an array of
   Candy pointers. The first line is column names and is skipped.

   Task 1:
   The program reads all candies from the file and stores the data in
   structs. Each struct is stored on the heap. The candy name string is
   also stored on the heap. After reading the file, the program prints
   the names of all candies.

   Task 2:
   The program lists all chocolate candies. If a chocolate candy also
   has caramel, its name is printed in upper-case. If it does not have
   caramel, its name is printed in lower-case. The program also prints
   the percent of chocolate candies that also have caramel.

   Task 3:
   For each attribute from fields 2 through 10, the program prints the
   average sugar percent, price percent, and win percent for candies
   that have that attribute. The program also prints the same summary
   values for candies whose sugar percent is higher than the average
   sugar percent, and candies whose price percent is higher than the
   average price percent.

   History:
     Wenhao   June 2026   Created
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* Candy stores one row from candy-data.csv.
   The name is stored as a string.
   Fields 2 through 10 are stored as ints.
   Fields 11 through 13 are stored as doubles.
*/
typedef struct Candy {
    char *competitorname;

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

/* killNewline removes a trailing newline from a string, if present.
   fgets leaves the '\n' at the end of what it reads, so this trims it.
   It also removes '\r' for Windows-style line endings.
   Parameters:
     char *str   the string to trim, modified in place
   Returns:
     void
   Usage:
     killNewline(line);
*/
void killNewline(char *str) {
    int len = strlen(str);

    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
}

/* copyString copies a string to heap memory.
   This is needed because all strings should be stored on the heap.
   Parameters:
     char *str   the string to copy
   Returns:
     char *   pointer to the new heap string
   Usage:
     candy->competitorname = copyString(field);
*/
char *copyString(char *str) {
    char *newString = malloc(strlen(str) + 1);

    if (newString == NULL) {
        printf("Could not allocate memory for string.\n");
        exit(1);
    }

    strcpy(newString, str);
    return newString;
}

/* getNextField copies the next comma-separated field of a line into
   out and returns a pointer to the rest of the line, just past the comma.
   If the field is wrapped in double quotes, the quotes are removed.
   Parameters:
     char *start   pointer to the start of the remaining line
     char *out     buffer that receives the next field
   Returns:
     char *   pointer to the rest of the line, or NULL if none remains
   Usage:
     char *p = line;
     p = getNextField(p, field);
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

/* makeCandyFromLine creates one Candy struct from one CSV line.
   The struct is stored on the heap. The candy name is also copied
   to the heap.
   Parameters:
     char *line   one line from candy-data.csv
   Returns:
     Candy *   pointer to the new Candy struct
   Usage:
     candies[candyCount] = makeCandyFromLine(line);
*/
Candy *makeCandyFromLine(char *line) {
    Candy *candy = malloc(sizeof(Candy));

    if (candy == NULL) {
        printf("Could not allocate memory for candy.\n");
        exit(1);
    }

    candy->competitorname = NULL;

    candy->chocolate = 0;
    candy->fruity = 0;
    candy->caramel = 0;
    candy->peanutalmondy = 0;
    candy->nougat = 0;
    candy->crispedricewafer = 0;
    candy->hard = 0;
    candy->bar = 0;
    candy->pluribus = 0;

    candy->sugarpercent = 0.0;
    candy->pricepercent = 0.0;
    candy->winpercent = 0.0;

    char field[1000];
    char *p = line;
    int col = 0;

    while (p != NULL) {
        p = getNextField(p, field);

        if (p != NULL) {
            if (col == 0) {
                candy->competitorname = copyString(field);
            } else if (col == 1) {
                candy->chocolate = atoi(field);
            } else if (col == 2) {
                candy->fruity = atoi(field);
            } else if (col == 3) {
                candy->caramel = atoi(field);
            } else if (col == 4) {
                candy->peanutalmondy = atoi(field);
            } else if (col == 5) {
                candy->nougat = atoi(field);
            } else if (col == 6) {
                candy->crispedricewafer = atoi(field);
            } else if (col == 7) {
                candy->hard = atoi(field);
            } else if (col == 8) {
                candy->bar = atoi(field);
            } else if (col == 9) {
                candy->pluribus = atoi(field);
            } else if (col == 10) {
                candy->sugarpercent = atof(field);
            } else if (col == 11) {
                candy->pricepercent = atof(field);
            } else if (col == 12) {
                candy->winpercent = atof(field);
            }

            col++;
        }
    }

    return candy;
}

/* printAllCandyNames prints the name of every candy.
   Parameters:
     Candy **candies   array of Candy pointers
     int candyCount    number of candies in the array
   Returns:
     void
   Usage:
     printAllCandyNames(candies, candyCount);
*/
void printAllCandyNames(Candy **candies, int candyCount) {
    printf("All candies:\n");

    for (int i = 0; i < candyCount; i++) {
        printf("%s\n", candies[i]->competitorname);
    }

    printf("\n");
}

/* printUpperCase prints a string in upper-case.
   The original string is not changed.
   Parameters:
     char *str   the string to print
   Returns:
     void
   Usage:
     printUpperCase(candyName);
*/
void printUpperCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        printf("%c", toupper((unsigned char) str[i]));
    }
}

/* printLowerCase prints a string in lower-case.
   The original string is not changed.
   Parameters:
     char *str   the string to print
   Returns:
     void
   Usage:
     printLowerCase(candyName);
*/
void printLowerCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        printf("%c", tolower((unsigned char) str[i]));
    }
}

/* printChocolateCandies prints all chocolate candies.
   If the candy also has caramel, the name is printed in upper-case.
   If the candy does not have caramel, the name is printed in lower-case.
   It also prints the percent of chocolate candies that also have caramel.
   Parameters:
     Candy **candies   array of Candy pointers
     int candyCount    number of candies in the array
   Returns:
     void
   Usage:
     printChocolateCandies(candies, candyCount);
*/
void printChocolateCandies(Candy **candies, int candyCount) {
    int chocolateCount = 0;
    int chocolateAndCaramelCount = 0;

    printf("Chocolate candies:\n");

    for (int i = 0; i < candyCount; i++) {
        if (candies[i]->chocolate == 1) {
            chocolateCount++;

            if (candies[i]->caramel == 1) {
                chocolateAndCaramelCount++;
                printUpperCase(candies[i]->competitorname);
            } else {
                printLowerCase(candies[i]->competitorname);
            }

            printf("\n");
        }
    }

    if (chocolateCount > 0) {
        double percent = (double) chocolateAndCaramelCount / chocolateCount * 100.0;
        printf("\nPercent of chocolate candies that also have caramel: %.2f%%\n",
               percent);
    } else {
        printf("\nNo chocolate candies found.\n");
    }

    printf("\n");
}

/* getAttributeValue returns the value of one attribute from a Candy.
   Attribute numbers:
     0 chocolate
     1 fruity
     2 caramel
     3 peanutalmondy
     4 nougat
     5 crispedricewafer
     6 hard
     7 bar
     8 pluribus
   Parameters:
     Candy *candy       pointer to one Candy
     int attributeNum   the attribute number
   Returns:
     int   0 or 1
   Usage:
     value = getAttributeValue(candy, 0);
*/
int getAttributeValue(Candy *candy, int attributeNum) {
    if (attributeNum == 0) {
        return candy->chocolate;
    } else if (attributeNum == 1) {
        return candy->fruity;
    } else if (attributeNum == 2) {
        return candy->caramel;
    } else if (attributeNum == 3) {
        return candy->peanutalmondy;
    } else if (attributeNum == 4) {
        return candy->nougat;
    } else if (attributeNum == 5) {
        return candy->crispedricewafer;
    } else if (attributeNum == 6) {
        return candy->hard;
    } else if (attributeNum == 7) {
        return candy->bar;
    } else if (attributeNum == 8) {
        return candy->pluribus;
    }

    return 0;
}

/* getAttributeName copies the name of an attribute into name.
   Parameters:
     int attributeNum   the attribute number
     char *name         output buffer for the name
   Returns:
     void
   Usage:
     getAttributeName(0, name);
*/
void getAttributeName(int attributeNum, char *name) {
    if (attributeNum == 0) {
        strcpy(name, "chocolate");
    } else if (attributeNum == 1) {
        strcpy(name, "fruity");
    } else if (attributeNum == 2) {
        strcpy(name, "caramel");
    } else if (attributeNum == 3) {
        strcpy(name, "peanutalmondy");
    } else if (attributeNum == 4) {
        strcpy(name, "nougat");
    } else if (attributeNum == 5) {
        strcpy(name, "crispedricewafer");
    } else if (attributeNum == 6) {
        strcpy(name, "hard");
    } else if (attributeNum == 7) {
        strcpy(name, "bar");
    } else if (attributeNum == 8) {
        strcpy(name, "pluribus");
    } else {
        strcpy(name, "unknown");
    }
}

/* printOneSummaryLine prints one summary line.
   It receives the sums and the count, then calculates and prints
   the averages.
   Parameters:
     char *name        name of the group
     double sugarSum   sum of sugarpercent
     double priceSum   sum of pricepercent
     double winSum     sum of winpercent
     int count         number of candies in the group
   Returns:
     void
   Usage:
     printOneSummaryLine(name, sugarSum, priceSum, winSum, count);
*/
void printOneSummaryLine(char *name,
                         double sugarSum,
                         double priceSum,
                         double winSum,
                         int count) {
    if (count == 0) {
        printf("%-20s Count: %3d   No candies\n", name, count);
    } else {
        printf("%-20s Count: %3d   Avg sugar: %.4f   Avg price: %.4f   Avg win: %.4f\n",
               name,
               count,
               sugarSum / count,
               priceSum / count,
               winSum / count);
    }
}

/* printAttributeSummaries prints the average sugar percent, price percent,
   and win percent for each attribute from fields 2 through 10.
   For each attribute, only candies that have that attribute are counted.
   Parameters:
     Candy **candies   array of Candy pointers
     int candyCount    number of candies in the array
   Returns:
     void
   Usage:
     printAttributeSummaries(candies, candyCount);
*/
void printAttributeSummaries(Candy **candies, int candyCount) {
    printf("Attribute summaries:\n");

    for (int attributeNum = 0; attributeNum < 9; attributeNum++) {
        double sugarSum = 0.0;
        double priceSum = 0.0;
        double winSum = 0.0;
        int count = 0;

        for (int i = 0; i < candyCount; i++) {
            if (getAttributeValue(candies[i], attributeNum) == 1) {
                sugarSum = sugarSum + candies[i]->sugarpercent;
                priceSum = priceSum + candies[i]->pricepercent;
                winSum = winSum + candies[i]->winpercent;
                count++;
            }
        }

        char attributeName[100];
        getAttributeName(attributeNum, attributeName);

        printOneSummaryLine(attributeName, sugarSum, priceSum, winSum, count);
    }

    printf("\n");
}

/* printAboveAverageSummaries prints summary information for candies whose
   sugar percent is higher than the average sugar percent. It also prints
   summary information for candies whose price percent is higher than the
   average price percent.
   Parameters:
     Candy **candies   array of Candy pointers
     int candyCount    number of candies in the array
   Returns:
     void
   Usage:
     printAboveAverageSummaries(candies, candyCount);
*/
void printAboveAverageSummaries(Candy **candies, int candyCount) {
    double totalSugar = 0.0;
    double totalPrice = 0.0;

    for (int i = 0; i < candyCount; i++) {
        totalSugar = totalSugar + candies[i]->sugarpercent;
        totalPrice = totalPrice + candies[i]->pricepercent;
    }

    double averageSugar = totalSugar / candyCount;
    double averagePrice = totalPrice / candyCount;

    double highSugarSugarSum = 0.0;
    double highSugarPriceSum = 0.0;
    double highSugarWinSum = 0.0;
    int highSugarCount = 0;

    double highPriceSugarSum = 0.0;
    double highPricePriceSum = 0.0;
    double highPriceWinSum = 0.0;
    int highPriceCount = 0;

    for (int i = 0; i < candyCount; i++) {
        if (candies[i]->sugarpercent > averageSugar) {
            highSugarSugarSum = highSugarSugarSum + candies[i]->sugarpercent;
            highSugarPriceSum = highSugarPriceSum + candies[i]->pricepercent;
            highSugarWinSum = highSugarWinSum + candies[i]->winpercent;
            highSugarCount++;
        }

        if (candies[i]->pricepercent > averagePrice) {
            highPriceSugarSum = highPriceSugarSum + candies[i]->sugarpercent;
            highPricePriceSum = highPricePriceSum + candies[i]->pricepercent;
            highPriceWinSum = highPriceWinSum + candies[i]->winpercent;
            highPriceCount++;
        }
    }

    printf("Overall average sugar percent: %.4f\n", averageSugar);
    printf("Overall average price percent: %.4f\n\n", averagePrice);

    printf("Above average summaries:\n");

    printOneSummaryLine("sugar > average",
                        highSugarSugarSum,
                        highSugarPriceSum,
                        highSugarWinSum,
                        highSugarCount);

    printOneSummaryLine("price > average",
                        highPriceSugarSum,
                        highPricePriceSum,
                        highPriceWinSum,
                        highPriceCount);

    printf("\n");
}

/* freeCandies frees all heap memory used by the candy array.
   Each candy name is freed first. Then each Candy struct is freed.
   Finally, the array of Candy pointers is freed.
   Parameters:
     Candy **candies   array of Candy pointers
     int candyCount    number of candies in the array
   Returns:
     void
   Usage:
     freeCandies(candies, candyCount);
*/
void freeCandies(Candy **candies, int candyCount) {
    for (int i = 0; i < candyCount; i++) {
        free(candies[i]->competitorname);
        free(candies[i]);
    }

    free(candies);
}

/* main asks the user for the CSV file name, opens the file, skips the
   header line, reads all candy rows, and stores them in an array of
   Candy pointers. Then it completes Task 1, Task 2, and Task 3.
   Finally it frees all heap memory.
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

    int capacity = 100;
    int candyCount = 0;

    Candy **candies = malloc(sizeof(Candy *) * capacity);

    if (candies == NULL) {
        printf("Could not allocate memory for candy array.\n");
        fclose(inFile);
        return 1;
    }

    char line[1000];

    /* Skip the first line because it contains the column names. */
    fgets(line, 1000, inFile);

    while (fgets(line, 1000, inFile) != NULL) {
        killNewline(line);

        if (strlen(line) > 0) {
            if (candyCount >= capacity) {
                capacity = capacity * 2;

                Candy **newCandies = realloc(candies, sizeof(Candy *) * capacity);

                if (newCandies == NULL) {
                    printf("Could not reallocate memory for candy array.\n");
                    freeCandies(candies, candyCount);
                    fclose(inFile);
                    return 1;
                }

                candies = newCandies;
            }

            candies[candyCount] = makeCandyFromLine(line);
            candyCount++;
        }
    }

    fclose(inFile);

    printAllCandyNames(candies, candyCount);

    printChocolateCandies(candies, candyCount);

    printAttributeSummaries(candies, candyCount);

    printAboveAverageSummaries(candies, candyCount);

    freeCandies(candies, candyCount);

    return 0;
}