#include <stdio.h>

int main () {
    double rate,hours;

    while (1) {
    printf("Enter the hourly rate: ");
    scanf("%lf", &rate);

    if (rate <= 0) {
        break;
    }

    printf("Enter the number of hours worked: ");
    scanf("%lf", &hours);

    if (hours <= 0) {
        break;
    }

    if (hours <= 40) {
        printf("Paycheck: $%.2lf\n", rate*hours);
    } else {
        printf("Paycheck: $%.2lf\n", (rate*40)+(rate*1.5*(hours-40)));
    }   
    
}
    return 0;   
}