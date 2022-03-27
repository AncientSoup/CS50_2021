#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Asks the user for block height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    // Prints the block
    for (int x = 1; x <= height; x++)
    {
        for (int y = x; y < height; y++)
        {
            printf(" ");
        }
        for (int z = 1; z <= x; z++)
        {
            printf("#");
        }
        printf("\n");
    }
}