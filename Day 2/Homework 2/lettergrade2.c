#include <stdio.h>

int main () {
    int grade;
    printf("Enter the grade: ");
    scanf("%d", &grade);

    if (grade < 0 || grade > 100) {
        printf("Invalid grade.\n");
        return 0;
    }

    if (grade <= 60 ) {
        printf("Your grade is F\n");
        return 0;
    }   

    printf("Your grade is ");
    if (grade <= 70) {
        printf("D");
    } else if (grade <= 80) {
        printf("C");
    } else if (grade <= 90) {
        printf("B");
    } else if (grade <= 100) {
        printf("A");
    }

    int lastdigit = grade % 10;
    if (lastdigit >= 1 && lastdigit <= 3) {
        printf("-");
    } else if (lastdigit == 7 || lastdigit == 8 || lastdigit == 9) {
        printf("+");
    }

}



















