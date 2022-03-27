#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// States size as 512 bytes
#define size 512

// Defines bytes.
typedef uint8_t BYTE;

// JPEG header checker.
int real(BYTE buffer[]);

int main(int argc, char *argv[])
{
    // Makes sure only 1 command line argument is present.
    if (argc != 2)
    {
        printf("Correct usage: ./recover (raw file)\n");
        return 1;
    }

    // Checks if the file chosen is present / can be opened.
    FILE *jpeg = fopen(argv[1], "r");
    if (jpeg == NULL)
    {
        printf("File cannot be opened.\n");
        return 1;
    }

    // Sets buffer array size to 512 bytes.
    BYTE buffer[size];

    // Buffers.
    char space[8];
    int count = 0;
    FILE *image;

    bool isjpeg = false;

    while (fread(buffer, size, 1, jpeg) == 1)
    {
        // Checks if header is JPEG format.
        if (real(buffer) == 1)
        {
            // Closes previously found jpeg
            if (isjpeg == true)
            {
                fclose(image);
                count++;
            }

            isjpeg = true;

            // Creates a .jpg file and writes the contained data.
            sprintf(space, "%03i.jpg", count);
            image = fopen(space, "w");
            fwrite(buffer, size, 1, image);
        }

        // Recovers the rest of the jpeg file until another one has been found.
        else if (isjpeg == true)
        {
            fwrite(buffer, size, 1, image);
        }
    }
}

// JPEG header checker.
int real(BYTE buffer[])
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return 1;
    }

    return 0;
}