#include <stdio.h>

int main () {
    int number;
    printf("Enter the number score: ");
    scanf("%d", &number);

    if (number < 1 || number > 10) {
    printf("Error: please enter a number between 1 and 10.\n");
    } else if (number <= 3){
        printf("Your grade is F\n");/* code */
    } else if (number <= 5) {
        printf("Your grade is E\n");
    } else if (number == 6) {
        printf("Your grade is D\n");
    } else if (number == 7) {
        printf("Your grade is C\n");
    } else if (number == 8) {
        printf("Your grade is B\n");
    } else{
        printf("Your grade is A\n");
    }    
    return 0;
}

