#include <math.h>
#include <stdlib.h>
#include <memory.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE original_red = image[i][j].rgbtRed;
            BYTE original_green = image[i][j].rgbtGreen;
            BYTE original_blue = image[i][j].rgbtBlue;
            int sepia_red = round(.393 * original_red + .769 * original_green + .189 * original_blue);
            if (sepia_red > 255)
            {
                sepia_red = 255;
            }
            image[i][j].rgbtRed = sepia_red;

            int sepia_green = round(.349 * original_red + .686 * original_green + .168 * original_blue);
            if (sepia_green > 255)
            {
                sepia_green = 255;
            }
            image[i][j].rgbtGreen = sepia_green;

            int sepia_blue = round(.272 * original_red + .534 * original_green + .131 * original_blue);
            if (sepia_blue > 255)
            {
                sepia_blue = 255;
            }
            image[i][j].rgbtBlue = sepia_blue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE pxa = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = pxa;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    memcpy(copy, image, sizeof(RGBTRIPLE[height][width]));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_red = 0;
            int sum_green = 0;
            int sum_blue = 0;
            int count = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        sum_red += copy[k][l].rgbtRed;
                        sum_green += copy[k][l].rgbtGreen;
                        sum_blue += copy[k][l].rgbtBlue;
                        count++;
                    }
                }
            }
            image[i][j].rgbtRed = round((float) sum_red / (float) count);
            image[i][j].rgbtGreen = round((float) sum_green / (float) count);
            image[i][j].rgbtBlue = round((float) sum_blue / (float) count);
        }
    }
}
