/* primefactors.c
   Asks the user for a number and prints the prime factorization.
   Factors are printed in order from smallest to largest,
   separated by " * ". Uses iteration without any function calls.
   Example: 180 -> 2 * 2 * 3 * 3 * 5
   History:
     Wenhao   May 2026   Created
*/

#include <stdio.h>

int main() {
    char s[100];
    int n;

    printf("Enter a number: ");
    fgets(s, 100, stdin);
    sscanf(s, "%d", &n);

    printf("The prime factors are ");

    int factor = 2;
    int first = 1;

    while (n > 1) {
        while (n % factor == 0) {
            if (!first) {
                printf(" * ");
            }
            printf("%d", factor);
            first = 0;
            n = n / factor;
        }
        factor++;
    }
    printf("\n");
}