#include "helpers.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

/*    for (int i = 0; i < sizeof(image[0]); i++){
        printf("%d %d %d \n", image[0][i].rgbtRed, image[0][i].rgbtGreen, image[0][i].rgbtBlue);
    }

    printf("H: %i \nW: %i\n", height, width);
    printf("H: %lu \n", sizeof(image[][0]));*/

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
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
