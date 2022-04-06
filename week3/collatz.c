#include <stdio.h>

int collatz(int num){
    
    if (num == 1){
        return 0;}
    else if (num%2 == 0){
        return 1 + collatz(num/2);}
    else {
        return 1 + collatz(num*3+1);}
}

int main(void){

    printf("Number please: ");
    int num;
    scanf("%d", &num);

    int count = collatz(num);
    printf("Count is %d\n", count);
    
}

