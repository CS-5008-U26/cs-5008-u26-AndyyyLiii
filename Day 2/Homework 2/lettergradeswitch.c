#include <stdio.h>

int main () {
    int number;
    printf("Enter the number score: ");
    scanf("%d", &number);
    switch (number) {
        case 1:
        case 2:
        case 3:
            printf("Your grade is F\n");
            break;
        case 4:
        case 5:
            printf("Your grade is E\n");
            break;
        case 6:
            printf("Your grade is D\n");
            break;
        case 7:
            printf("Your grade is C\n");
            break;
        case 8:
            printf("Your grade is B\n");
            break;
        case 9:
        case 10:
            printf("Your grade is A\n");
            break;
        default:
            printf("Error: please enter a number between 1 and 10.\n");
    }
}
