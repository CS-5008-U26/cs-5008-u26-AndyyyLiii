/* Third C Program - for Homework 1
 *
 * Wenhao Li
 * CS-5008 Summer 2026
 *
 * This program asks for the user's name and age,
 * then greets them with both pieces of information.
 */

#include <stdio.h>

int main() {
    char name[100];           // store the user's name
    int age;                  // store the user's age
    char t[100];              // trash bin for leftover \n

    printf("What is your name? ");
    scanf("%s", name);                   // read the name
    fgets(t, 100, stdin);                // clean up the \n

    printf("How old are you? ");
    scanf("%d", &age);                   // read age as an integer (note the &)
    fgets(t, 100, stdin);                // clean up the \n

    printf("Hi %s! You are %d years old.\n", name, age);   // greet using both

    fgets(t, 100, stdin);                // pause the window
}