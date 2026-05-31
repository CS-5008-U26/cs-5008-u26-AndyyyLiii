/* relative.c
   Accepts an integer n, then prints the ET-function for each
   integer from 2 to n.
   The ET-function et(x) is the number of integers less than x
   that are relatively prime with x. Two numbers are relatively
   prime if they have no factors in common other than 1.
   History:
     Wenhao   May 2026   Created
*/

#include <stdio.h>

/* gcd computes the greatest common divisor of two integers.
   Used to determine if two numbers are relatively prime.
   Parameters:
     int a   the first integer
     int b   the second integer
   Returns:
     int     the greatest common divisor of a and b
   Usage:
     if (gcd(12, 8) == 1) { ... }
*/
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/* et computes the ET-function for x.
   Counts how many integers less than x have no factors
   in common with x other than 1.
   Parameters:
     int x   the number being examined
   Returns:
     int     the count of integers less than x that are
             relatively prime with x
   Usage:
     int count = et(10);
*/
int et(int x) {
    int count = 0;
    for (int i = 1; i < x; i++) {
        if (gcd(x, i) == 1) {
            count++;
        }
    }
    return count;
}

int main() {
    char s[100];
    int n;

    printf("Enter an integer: ");
    fgets(s, 100, stdin);
    sscanf(s, "%d", &n);

    for (int i = 2; i <= n; i++) {
        printf("et(%d) = %d\n", i, et(i));
    }
}