#include "../cs50.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){

    int x = 12;

    int y = 0;

    y += x%10;
    printf("%d \n", x);
    printf("%d \n", y);

    y += x/10;
    printf("%d \n", x);
    printf("%d \n\n", y);

    printf("%d\n", 12%10);
    printf("%d\n", 12/10);
    printf("%d\n", 2%10);
    printf("%d\n", 2/10);
}