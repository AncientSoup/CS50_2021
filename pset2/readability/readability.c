#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

int main(void)
{   
    // Get input from user
    string text = get_string("Text: ");
    
    // To record the number of letters, words and sentences.
    float letter = 0.0;
    float sentence = 0.0;
    float words = 1.0;
    
    for (int i = 0; i < strlen(text); i++)
    {
        // To find the number of alphabetical letters in the text. 
        if isalpha(text[i])
        {
            letter++;
        }
        // To find the number of sentences.
        if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            sentence++;
        }
        // To find the number of words.
        if isblank(text[i])
        {
            words++;
        }
    }
    
    // To calculate both the average letters and sentences per 100 words.
    float L = (letter / words) * 100.0;
    float S = (sentence / words) * 100.0;
   
    // Coleman liau index formula
    int index = round(0.0588 * L - 0.296 * S - 15.8);
   
    // To determine whether if grade is above 16, below 1 or in between.
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}