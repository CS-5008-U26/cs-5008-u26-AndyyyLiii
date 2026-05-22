#include <math.h>
#include <stdio.h>
int main () {
    int radius;
    printf("Enter an integer radius: ");
    scanf("%d", &radius);
    if (radius < 0) {
        printf("Error: radius cannot be negative.\n");
    } else {
        printf("For a circle of radius %.1f the area is %.0f\n", (double)radius, (double)radius*radius*acos(-1));
    }
    
}