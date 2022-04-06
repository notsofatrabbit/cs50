#include "../cs50.h"
#include <stdio.h>

void preSpacePrinter(int hashLen){
    for(int i = 0; i < hashLen; i++)
        printf(" ");
} 

void hashPrinter(int hashLen){
    for(int i = 0; i < hashLen; i++)
        printf("#");
} 

int main(void)
{
    // Gets tower height
    int levels;
    printf("How many levels: ");
    scanf("%i", &levels);
    
    // Prints each row
    for (int i = 1; i < levels+1; i++){
        
        //prints space before each line
        preSpacePrinter(levels-i);

        // Prints each line with middle spacer
        for(int j = 0; j < 2; j++){
            hashPrinter(i);
            if (j == 0) {
                printf("  ");        
            }
        }

        printf("\n");
    }


}
