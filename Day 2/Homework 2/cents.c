#include <stdio.h>
int main () {
    int cents;
    printf("Enter the number of cents: ");
    scanf("%d", &cents);
    if (cents < 0) {
        printf("Error: cents cannot be negative.\n");
    } else {
        int quarters = cents / 25;
        int dimes = (cents % 25) / 10;
        int nickels = ((cents % 25) % 10) / 5;
        int pennies = ((cents % 25) % 10) % 5;
        printf("That requires %d quarters, %d dimes, %d nickels, and %d pennies\n", quarters, dimes, nickels, pennies);
    }
}