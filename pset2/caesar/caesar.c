#include <string.h>
#include <ctype.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    // Checks if user does not put anything in the argument line.
    if (argc != 2)
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }
    
    int num = atoi(argv[1]);
    
    // Checks if user has typed in any letter.
    if (num == 0)
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }
    else
    {
        // Get text from user.
        string pt = get_string("plaintext: ");

        printf("ciphertext: ");
        
        for (int i = 0; i < strlen(pt); i++)
        {
            // Prints out anything that isn't a letter (e.g '!' or ',').
            if (!isalpha(pt[i]))
            {
                printf("%c", pt[i]);
            }
            if isalpha(pt[i])
            {
                // Checks if letter is uppercase.
                if isupper(pt[i])
                {
                    int spoint = pt[i] - 'A';
                    int fpoint = (spoint + num) % 26;
                    int total1 = fpoint + 'A';
                    printf("%c", total1);
                }
                // Checks if letter is lowercase.
                else if islower(pt[i])
                {
                    int spoint1 = pt[i] - 'a';
                    int fpoint2 = (spoint1 + num) % 26;
                    int total2 = fpoint2 + 'a';
                    printf("%c", total2);
                }
            }
        }
    }
    printf("\n");
    return 0;
}