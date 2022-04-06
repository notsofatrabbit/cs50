#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_LIMIT 100

int computeScore(int points[], char word[]);

int main(void){

    // Get user string
    char word1[MAX_LIMIT];
    printf("word1: ");
    fgets(word1, MAX_LIMIT, stdin);  //string has a lot of garbage behind resulting in question marks

    char word2[MAX_LIMIT];
    printf("word2: ");
    fgets(word2, MAX_LIMIT, stdin);  //string has a lot of garbage behind resulting in question marks    

    int points[26] =   {1, 3, 3, 2, 1, 
                        4, 2, 4, 1, 8, 
                        5, 1, 3, 1, 1, 
                        3, 10, 1, 1, 1, 
                        1, 4, 4, 8, 4, 
                        10,};


    int score1 = computeScore(points, word1);
    int score2 = computeScore(points, word2);

    //printf("Score1: %d\n", score1);
    //printf("Score2: %d\n", score2);

    if (score1 > score2){
        printf("Player 1 wins!\n");
    }else if (score2 > score1){
        printf("Player 2 wins!\n");
    } else {
        printf("Tie!\n");
    }

}

int computeScore(int points[], char word[]){

        // Finds point of letter
    int tempInt;
    int score = 0;

    for (int i = 0; word[i]; i++){
        tempInt = (int)(toupper(word[i]));
        
        //printf("flag1 - tempInt: %d\n", tempInt);

        if  (tempInt > 64 && tempInt < 91){
            
            score += points[tempInt-65];

            //printf("points: %d\n", points[tempInt-65]);

        }
    }

    //printf("total points: %d\n", score);
    return score;
}