/* Second C Program - for Homework 1
 *
 * Wenhao Li
 * CS-5008 Summer 2026
 *
 * Changes I made to fix this program:
 *   1. Changed fgets(s, ...) to fgets(t, ...) after scanf, so the
 *      leftover \n goes into t instead of overwriting the user's name in s.
 *   2. Changed printf's variable from t to s, so it prints the user's
 *      actual name instead of an uninitialized variable.
 *   3. Added "\n" to the printf format string, and added fgets at the
 *      end to pause the console window before it closes.
 *   4. Added comments throughout the file (this change).
 */

#include <stdio.h>

int main() {
    char s[100];                                // s stores the user's name
    char t[100];                                // t is a "trash bin" for leftover \n

    printf("What is your name? ");              // prompt the user
    scanf("%s", s);                             // read the name into s
    fgets(t, 100, stdin);                       // clean up the leftover \n (into t, not s!)
    printf("%s? That's a funny name!\n", s);    // greet the user

    fgets(t, 100, stdin);                       // pause the window until user hits Enter
}
