#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            int avg = round(sum / 3);
            // Each pixel color is set to the average color from rgb color.
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float originalRed = image[i][j].rgbtRed;
            float originalGreen = image[i][j].rgbtGreen;
            float originalBlue = image[i][j].rgbtBlue;
            
            // Sepia filter formula.
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            
            // Makes sure the maximum number is 255 per color bit as stated by the instructions.
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            
            // Applies sepia formula.
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            // Temporary value.
            RGBTRIPLE opp = image[i][j];
            // Swaps every pixel to its counter position.
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = opp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary value.
    RGBTRIPLE blurry[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float count = 0.0;
            float tRed;
            float tGreen;
            float tBlue;
            tRed = tGreen = tBlue = 0;
            
            for (int k = -1; k < 2; k++)
            {
                // Merges 3 by 3 pixels to apply blurr effect.
                for (int l = -1; l < 2; l++)
                {
                    int blurX = i + k;
                    int blurY = j + l;
                    
                    if (blurX < 0 || blurX > (height - 1) || blurY < 0 || blurY > (width - 1))
                    {
                        continue;
                    }
                    
                    tRed += image[blurX][blurY].rgbtRed;
                    tGreen += image[blurX][blurY].rgbtGreen;
                    tBlue += image[blurX][blurY].rgbtBlue;
                    
                    count++;
                }
                
                blurry[i][j].rgbtRed = round(tRed / count);
                blurry[i][j].rgbtGreen = round(tGreen / count);
                blurry[i][j].rgbtBlue = round(tBlue / count);
            }
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Puts blurred pixels to its original position.
            image[i][j].rgbtRed = blurry[i][j].rgbtRed;
            image[i][j].rgbtGreen = blurry[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blurry[i][j].rgbtBlue;
        }
    }
    return;
}