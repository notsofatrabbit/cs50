#include "cs50.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int luhnCheck(int nDigits, long long int cardNumber){

    int adjustedNumbers = 0; // numbers mulitplied then added
    int normalNumbers = 0; // numbers just added
    int tempNum = 0;

    // Luhn's Algorithim  
    for (int i = 1; i < nDigits+1; i++){
        
        if (i%2 == 0){
            tempNum = (cardNumber%10)*2;
            //printf("tempNum: %d \n", tempNum);

            adjustedNumbers += tempNum%10;
            adjustedNumbers += tempNum/10;
            
            //printf("%lld \n", 2*cardNumber%10);
        } else{
            normalNumbers += cardNumber%10;
            //printf("%lld \n", cardNumber%10);
        }

        cardNumber/=10;
    }

    printf("\nAdjust Numbers: %d \n", adjustedNumbers);
    printf("Normal Numbers: %d \n", normalNumbers);

    int sum = adjustedNumbers + normalNumbers;

    if (sum%10 == 0){
        return 1;
    } else {
        return 0;
    }
}

int startCheck(int nDigits, long long int cardNumber){
    // Check start
        // AE (15) 34, 37
        // MC (16) 51, 52, 53, 54, 55
        // VI (13/16)   4

    int frontSum = cardNumber / pow(10, nDigits-2);

    string test  = get_string("HI THERE");

    //printf("This is front sum: %d \n", frontSum);

    if (frontSum == 34 || frontSum == 37){
            printf("Cardtype: American Express \n ");
            return 1;
    } else if (frontSum == 51 || frontSum == 51 || frontSum == 53 || frontSum == 54 || frontSum == 55){
            printf("Cardtype: MasterCard \n");
            return 1;
    } else if (frontSum/10 == 4){
            printf("Cardtype: VISA \n");
            return 1;
    } else{
        printf("Cardtype: INVALID \n");
        return 0;
    }
} 

int main(void){

    //long long int cardNumber = 4003600000000014; //VISA
    //long long int cardNumber = 4003600000004; //VISA
    //long long int cardNumber = 340363000000001; //AE
    //long long int cardNumber = 5103620000000042; //MC
    long long int cardNumber;

    int fullDoWhileVal = 0;
    do{
        printf("Number: ");
        scanf("%lld", &cardNumber);
        if (cardNumber == 0){
            fullDoWhileVal = 1;
        }
        //printf("%d \n", cardNumber);

        // Length of card number
        int nDigits = floor(log10(llabs(cardNumber))) + 1;

        //printf("nDigits: %d\n", nDigits);

        if (luhnCheck(nDigits, cardNumber) == 1){
            if (nDigits == 13 || nDigits == 15 || nDigits == 16){
                fullDoWhileVal = startCheck(nDigits, cardNumber);
            }else{
                printf("CardType: INVALID1 \n");
            }
            
        } else{
            printf("Cardtype: Invalid\n");
        }
        // Check Length
            // AE (15)
            // MC (16)
            // VI (13/16)

        //printf("CardNumber: %lld \n", cardNumber);
    } while (fullDoWhileVal == 0);

}