#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_LIMIT 100

// ./substitution YTNSHKVEFXRBAUQZCLWDMIPGJO

// 1. Take in 26 random leter string
//      1.1 Ignore upper or lower case for string

// 2. Should contain an error message if vaild string is not entered
// should tell the user how to use the program

int main(int argc, char *argv[]){

    if (argc != 2){
        printf("Usage: ./substitution key\n");
        return 1;
    } else if (strlen(argv[1])!= 26){
        printf("Key must contain 26 characters.\n");
        return 1;
    } 

    //printf("%c", argv[1][0]);

    char cipher[26];

    for (int i = 0; argv[1][i]; i++){
        cipher[i] = argv[1][i];
    }

    //char cipher[] = "ZABCDEFGHIJKLMNOPQRSTUVWXY";
    //printf("%lu\n", strlen(cipher));
    //char cipher[] = "YTNSHKVEFXRBAUQZCLWDMIPGJO";

    // Get user string
    char plainText[MAX_LIMIT];
    printf("plainText:  ");
    fgets(plainText, MAX_LIMIT, stdin);  //string has a lot of garbage behind resulting in question marks
    

    int textPosition[strlen(plainText)];
    char secretText[strlen(plainText)];

    for (int i = 0; plainText[i]; i++){
        secretText[i] = plainText[i];
    }

    //printf("%s \n", secretText);


    // Finds alphabetic order of letter 
    int tempInt;

    for (int i = 0; plainText[i]; i++){
        tempInt = (int)(plainText[i]);
        
        //printf("flag1 - tempInt: %d\n", tempInt);

        if  (tempInt > 64 && tempInt < 91){
            
            textPosition[i] = tempInt-65;
            secretText[i] = toupper(cipher[tempInt-65]);

        } else if  (tempInt > 96 && tempInt < 123){
            
            textPosition[i] = tempInt-97;
            secretText[i] = tolower(cipher[tempInt-97]);

        } else {

            textPosition[i] = 99; //Special Characters get 99 in aphabetical placing 

        }

        //printf("flag2 - textPos: %d\n", textPosition[i]);
    }

    //for (int i = 0; plainText[i]; i++){
    //    printf("%d \n", textPosition[i]);
    //}

    //printf("%s \n", cipher);
    //printf("%s \n", plainText);
    printf("secretText: %s", secretText);
    return 0;

    //for in 

    
}