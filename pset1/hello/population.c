#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Finds out the starting and ending size
    int start_size;
    do
    {
        start_size = get_int("Put in the starting size: ");
    }
    while (start_size < 9);
    
    int end_size;
    do
    {
        end_size = get_int("Put in the ending size: ");
    }
    while (end_size < start_size);
    
    // Calculates the years required
    int years = 0;
    while (end_size > start_size)
    {
        float lives = start_size / 3;
        float deaths = start_size / 4;
        start_size = (lives - deaths) + start_size;
        years++;
    }
    
    //Prints the number of years
    printf("Years: %i\n", years);
}