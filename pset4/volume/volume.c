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

    // Reads the first 44 bytes (a.k.a header) from the input.wav file.
    uint8_t header[HEADER_SIZE];
    fread(header, 1, HEADER_SIZE, input);
    
    // Copies the contents of header.
    fwrite(header, 1, HEADER_SIZE, output);
    
    // Reads the samples of the input.wav file.
    int16_t buffer;
    while (fread(&buffer, sizeof(buffer), 1, input) == 1)
    {
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(buffer), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
