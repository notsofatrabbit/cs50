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
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
