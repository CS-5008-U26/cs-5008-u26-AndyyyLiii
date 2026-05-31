/* complement.c
   Asks for an integer and prints the 10's complement.
   The 10's complement is defined by substituting for each digit,
   9 - that digit. For example, the 10's complement of 123 is 876.
   Uses a recursive function to implement this.
   History:
     Wenhao   May 2026   Created
*/

#include <stdio.h>

/* complement calculates the 10's complement of x recursively.
   It removes the rightmost digit, calls itself to complement
   the rest of x, then composes that result with 9 - the rightmost digit.
   Parameters:
     int x   the integer to complement
   Returns:
     int     the 10's complement of x
   Usage:
     int result = complement(12345);
*/
int complement(int x) {
    if (x == 0) {
        return 0;
    }
    int rightmost = x % 10;
    int rest = x / 10;
    return complement(rest) * 10 + (9 - rightmost);
}

int main() {
    char s[100];
    int n;

    printf("Enter an integer: ");
    fgets(s, 100, stdin);
    sscanf(s, "%d", &n);

    printf("The complement is %d\n", complement(n));
}