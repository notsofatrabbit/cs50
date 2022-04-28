#include "helpers.h"
#include "stdio.h"
#include "math.h"

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
    
    int newRed = 0;
    int newBlue = 0;
    int newGreen = 0;

    int counter = 0;
    int checkCol = 0;
    int checkRow = 0;


    int TEST = 0;
    int testRow = 200;
    int testCol = 201;

    // Image Loop    
    if (TEST != 1){
        testRow = height;
        testCol = width;
    }

    for (int i = 0; i < testRow; i++){
        for (int j = 0; j < testCol; j++){

            if (TEST == 1){
                printf("NEW BLOCK-----------\n");
            }
            // 9x9 loop
            for (int a = -1; a < 2; a++){
                for (int b = -1; b < 2; b++){

                    
                    //printf("i + a = %i\n", i + a);
                    //printf("j + b = %i\n\n", j + b);
                    checkRow = i + a;
                    checkCol = j + b;

                    if (0 <= i + a && height-1 >= i + a){
                        if (0 <= j + b && width-1 >= j + b){
                            newRed += image[checkRow][checkCol].rgbtRed;
                            newBlue += image[checkRow][checkCol].rgbtBlue;
                            newGreen += image[checkRow][checkCol].rgbtGreen;
                            counter += 1;

                            if (TEST == 1){
                                printf("R: %i [%i]\n",image[checkRow][checkCol].rgbtRed, newRed);
                                printf("G: %i [%i]\n",image[checkRow][checkCol].rgbtGreen, newGreen);
                                printf("B: %i [%i]\n",image[checkRow][checkCol].rgbtBlue, newBlue);
                                printf("Counter: %i\n\n", counter);
                            }
                        }
                    }
                }
            }
            
            newImage[i][j].rgbtRed = newRed/counter;
            newImage[i][j].rgbtBlue = newBlue/counter;
            newImage[i][j].rgbtGreen = newGreen/counter;

            newRed = 0;
            newGreen = 0;
            newBlue = 0;

            if (TEST == 1){
                printf("avg.R: %i\n",newImage[i][j].rgbtRed);
                printf("avg.G: %i\n",newImage[i][j].rgbtGreen);
                printf("avg.B: %i\n\n",newImage[i][j].rgbtBlue);
            }
                        
            counter = 0;
        }
    }

    /*if (TEST == 1){
        for (int i = 0; i < testRow; i++){
            for (int j = 0; j < testCol; j++){
                printf("newimage[%i][%i]: %i %i %i\n",i,j,newImage[i][j].rgbtRed, newImage[i][j].rgbtGreen, newImage[i][j].rgbtBlue );
                printf("image[%i][%i]: %i %i %i\n\n",i,j,image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue );
            }
        }
    }*/

    printf("newimage[%i][%i]: %i %i %i\n",0,2,newImage[0][2].rgbtRed, newImage[0][2].rgbtGreen, newImage[0][2].rgbtBlue );

    for (int i = 0; i < testRow; i++){
        for (int j = 0; j < testCol; j++){
            printf("image[%i][%i]: %i %i %i\n",i,j,image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue );
            image[i][j].rgbtRed = newImage[i][j].rgbtRed; 
            image[i][j].rgbtGreen = newImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = newImage[i][j].rgbtBlue;
            printf("updated - image[%i][%i]: %i %i %i\n\n",i,j,image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue );
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newImage[height][width];

    //printf("Height: %d", height);
    
    int newRed = 0;
    int newBlue = 0;
    int newGreen = 0;

    int counter = 0;
    int checkCol = 0;
    int checkRow = 0;

    int TEST = 0;
    int testRow = 1;
    int testCol = 2;

    int GxKernel[3][3] = {{-1, 0, 1}, {-2, 0 , 2}, {-1, 0, 1}};
    int GyKernel[3][3] = {{-1, -2, -1}, {0, 0 , 0}, {1, 2, 1}};

    int Gy[3] = {0,0,0};
    int Gx[3] = {0,0,0};
    int G = 0;
    
    // Image Loop    
    if (TEST != 1){
        testRow = height;
        testCol = width;
    }

    for (int i = 0; i < testRow; i++){
        for (int j = 0; j < testCol; j++){

            if (TEST == 1){
                printf("NEW BLOCK-----------\n");
            }
            // 9x9 loop
            for (int a = -1; a < 2; a++){
                for (int b = -1; b < 2; b++){

                    
                    //printf("i + a = %i\n", i + a);
                    //printf("j + b = %i\n\n", j + b);
                    checkRow = i + a;
                    checkCol = j + b;

                    if (0 <= i + a && height-1 >= i + a){
                        if (0 <= j + b && width-1 >= j + b){
                            //printf("%i [%i, %i]  ",image[checkRow][checkCol].rgbtRed, GxKernel[a+1][b+1], GyKernel[a+1][b+1]);
         
                            Gx[0] += image[checkRow][checkCol].rgbtRed * GxKernel[a+1][b+1];
                            Gx[1] += image[checkRow][checkCol].rgbtGreen * GxKernel[a+1][b+1]; 
                            Gx[2] += image[checkRow][checkCol].rgbtBlue * GxKernel[a+1][b+1];

                            Gy[0] += image[checkRow][checkCol].rgbtRed * GyKernel[a+1][b+1];
                            Gy[1] += image[checkRow][checkCol].rgbtGreen * GyKernel[a+1][b+1];
                            Gy[2] += image[checkRow][checkCol].rgbtBlue * GyKernel[a+1][b+1];

                        }
                    }
                }
                //printf("\n");
            }


            for (int d = 0; d < 3; d++){

                G = sqrt(pow(Gx[d],2)+pow(Gy[d],2));

                if (G > 255){
                    G = 255;
                }
                Gx[d] = 0;
                Gy[d] = 0;

                if (d == 0){
                    newImage[i][j].rgbtRed = G;
                } else if (d == 1){
                    newImage[i][j].rgbtGreen = G;
                } else if (d == 2){
                    newImage[i][j].rgbtBlue = G;
                }
            }


            /*if (TEST == 1){
                printf("avg.R: %i\n",newImage[i][j].rgbtRed);
                printf("avg.G: %i\n",newImage[i][j].rgbtGreen);
                printf("avg.B: %i\n\n",newImage[i][j].rgbtBlue);
            }*/
        }
    }

    /*if (TEST == 1){
        for (int i = 0; i < testRow; i++){
            for (int j = 0; j < testCol; j++){
                printf("newimage[%i][%i]: %i %i %i\n",i,j,newImage[i][j].rgbtRed, newImage[i][j].rgbtGreen, newImage[i][j].rgbtBlue );
                printf("image[%i][%i]: %i %i %i\n\n",i,j,image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue );
            }
        }
    }*/
 
 
    //printf("newimage[%i][%i]: %i %i %i\n",0,2,newImage[0][2].rgbtRed, newImage[0][2].rgbtGreen, newImage[0][2].rgbtBlue );

    for (int i = 0; i < testRow; i++){
        for (int j = 0; j < testCol; j++){
            //printf("image[%i][%i]: %i %i %i\n",i,j,image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue );
            image[i][j].rgbtRed = newImage[i][j].rgbtRed; 
            image[i][j].rgbtGreen = newImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = newImage[i][j].rgbtBlue;
            //printf("updated - image[%i][%i]: %i %i %i\n\n",i,j,image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue );
        }
    }
 
    return;
}
