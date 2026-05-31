/* primefactors2.c
   Uses a recursive function to print the prime factors of a number.
   Each time the function is called, it prints one prime factor and
   then calls itself to continue with further prime factors.
   The " * " separators appear between successive prime factors,
   not before the first, and not after the last.
   Example: 180 -> 2 * 2 * 3 * 3 * 5
   History:
     Wenhao   May 2026   Created
*/

#include <stdio.h>

/* printFactors prints the prime factors of n recursively.
   Each call finds the next prime factor, prints it, and recurses
   with the reduced value.
   Parameters:
     int n       the remaining value to factor
     int factor  the current candidate prime factor to try
     int first   1 if no factor has been printed yet, 0 otherwise
   Returns:
     void
   Usage:
     printFactors(180, 2, 1);
*/
void printFactors(int n, int factor, int first) {
    if (n <= 1) {
        return;
    }
    if (n % factor == 0) {
        if (!first) {
            printf(" * ");
        }
        printf("%d", factor);
        printFactors(n / factor, factor, 0);
    } else {
        printFactors(n, factor + 1, first);
    }
}

int main() {
    char s[100];
    int n;

    printf("Enter a number: ");
    fgets(s, 100, stdin);
    sscanf(s, "%d", &n);

    printf("The prime factors are ");
    printFactors(n, 2, 1);
    printf("\n");
}