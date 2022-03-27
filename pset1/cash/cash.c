#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{   
    // Values assigned for counting the coins used
    int q = 0;
    int d = 0;
    int n = 0;
    int p = 0;

    // Asks the user for change
    float money;
    do
    {
        money = get_float("Change owed: ");
    }
    while (money < 0);
    
    //Converts float value to integer
    int cents = round(money * 100);
    
    int val = 0;
    bool cond = false;

    // Greedy algorithm
   do
    {
        if (25 <= cents)
        {
            val = cents / 25;
            cents = cents - val * 25;
            q++;
        }
        else if (10 <= cents)
        {
            val = cents / 10;
            cents = cents - val * 10;
            d++;
        }
        else if (5 <= cents)
        {
            val = cents / 5;
            cents = cents - val * 5;
            n++;
        }
        else
        {
            val = cents / 1;
            cents--;
            p++;
        }
    }
    while (cents > 0);
    
    // Prints the coins needed
    int x = q + d + n + p;
    printf("%i\n", x);
}