#include "helpers.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < sizeof(image[0]); i++){
        printf("%d %d %d \n", image[0][i].rgbtRed, image[0][i].rgbtGreen, image[0][i].rgbtBlue);
    }

    int greyAvg = 0;

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){

            greyAvg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;

            image[i][j].rgbtRed =   greyAvg;
            image[i][j].rgbtGreen = greyAvg;
            image[i][j].rgbtBlue =  greyAvg;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int holdRed = 0;
    int holdBlue = 0;
    int holdGreen = 0;
    int a = 0;
    int b = 0;

    for (int i = 0; i < height; i++){
        for (int j = 0; j < (width)/2; j++){

            a = j;
            b = width - 1 -j;

            holdRed = image[i][a].rgbtRed;
            holdGreen = image[i][a].rgbtGreen;
            holdBlue = image[i][a].rgbtBlue;

            image[i][a].rgbtRed = image[i][b].rgbtRed;
            image[i][a].rgbtGreen = image[i][b].rgbtGreen;
            image[i][a].rgbtBlue = image[i][b].rgbtBlue;

            image[i][b].rgbtRed = holdRed;
            image[i][b].rgbtGreen = holdGreen;
            image[i][b].rgbtBlue = holdBlue;

        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE newImage[height][width];

    printf("Height: %d", height);


    RGBTRIPLE newNum;
    newNum.rgbtRed = 0;
    newNum.rgbtBlue = 0;
    newNum.rgbtGreen = 0;

    int counter = 0;
    int checkCol = 0;
    int checkRow = 0;

    // Image Loop    
    //for (int i = 0; i < height; i++){
     //   for (int j = 0; j < width; j++){
    for (int i = 0; i < 1; i++){
        for (int j = 0; j < 2; j++){

            printf("NEW BLOCK-----------\n");
            // 9x9 loop
            for (int a = -1; a < 2; a++){
                for (int b = -1; b < 2; b++){

                    
                    printf("i + a = %i\n", i + a);
                    printf("j + b = %i\n\n", j + b);
                    checkRow = i + a;
                    checkCol = j + b;

                    if (0 <= i + a && height-1 >= i + a){
                        if (0 <= j + b && width-1 >= j + b){
                            newNum.rgbtRed += image[checkRow][checkCol].rgbtRed;
                            newNum.rgbtBlue += image[checkRow][checkCol].rgbtBlue;
                            newNum.rgbtGreen += image[checkRow][checkCol].rgbtGreen;
                            counter += 1;

                            printf("R: %i [%i]\n",image[i][j].rgbtRed, newNum.rgbtRed);
                            printf("G: %i [%i]\n",image[i][j].rgbtGreen, newNum.rgbtGreen);
                            printf("B: %i [%i]\n",image[i][j].rgbtBlue, newNum.rgbtBlue);
                            printf("Counter: %i\n\n", counter);
                        }
                    }
                }
            }
            
            newImage[i][j].rgbtRed = newNum.rgbtRed/counter;
            newImage[i][j].rgbtBlue = newNum.rgbtBlue/counter;
            newImage[i][j].rgbtGreen = newNum.rgbtGreen/counter;

            newNum.rgbtRed = 0;
            newNum.rgbtGreen = 0;
            newNum.rgbtBlue = 0;

            printf("avg.R: %i\n",newImage[i][j].rgbtRed);
            printf("avg.G: %i\n",newImage[i][j].rgbtGreen);
            printf("avg.B: %i\n",newImage[i][j].rgbtBlue);
                        
            counter = 0;

        }
    }

        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++){
                image[i][j].rgbtBlue = newImage[i][j].rgbtRed; 
                image[i][j].rgbtGreen = newImage[i][j].rgbtGreen;
                image[i][j].rgbtBlue = newImage[i][j].rgbtBlue;
            }
        }


    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
