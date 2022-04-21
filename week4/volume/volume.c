// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    //Create blank space for read
    uint8_t arr[HEADER_SIZE];

    // read data to blank space
    fread(arr, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(arr, sizeof(uint8_t), HEADER_SIZE, output);

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer = 0;
    int i = 0;
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        if (i > 21){
            //printf("buffer no fact: %i\n",buffer);
            buffer = buffer * factor;
            //printf("buffer factor: %i\n", buffer);
            fwrite(&buffer, sizeof(uint16_t), 1, output);
        }else{
            i+=1;
        }

    }


    // Close files
    fclose(input);
    fclose(output);
}
