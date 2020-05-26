#include <math.h>
#include <stdlib.h>

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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][width - 1 - j];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct
    {
        int blue;
        int green;
        int red;
    } bgr;

    bgr result_gx[height][width];
    bgr result_gy[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            result_gx[i][j].red = 0;
            result_gx[i][j].green = 0;
            result_gx[i][j].blue = 0;
            result_gy[i][j].red = 0;
            result_gy[i][j].green = 0;
            result_gy[i][j].blue = 0;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = i - 1, m = 0; k <= i + 1; k++, m++)
            {
                for (int l = j - 1, n = 0; l <= j + 1; l++, n++)
                {
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        result_gx[i][j].red += gx[m][n] * image[k][l].rgbtRed;
                        result_gx[i][j].green +=  gx[m][n] * image[k][l].rgbtGreen;
                        result_gx[i][j].blue +=  gx[m][n] * image[k][l].rgbtBlue;
                        result_gy[i][j].red += gy[m][n] * image[k][l].rgbtRed;
                        result_gy[i][j].green += gy[m][n] * image[k][l].rgbtGreen;
                        result_gy[i][j].blue += gy[m][n] * image[k][l].rgbtBlue;
                    }
                    else
                    {
                        result_gx[i][j].red += 0;
                        result_gx[i][j].green += 0;
                        result_gx[i][j].blue += 0;
                        result_gy[i][j].red += 0;
                        result_gy[i][j].green += 0;
                        result_gy[i][j].blue += 0;
                    }
                }
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int edge_red = round(sqrt((result_gx[i][j].red * result_gx[i][j].red) + (result_gy[i][j].red * result_gy[i][j].red)));
            if (edge_red > 255)
            {
                edge_red = 255;
            }
            image[i][j].rgbtRed = edge_red;

            int edge_green = round(sqrt((result_gx[i][j].green * result_gx[i][j].green) + (result_gy[i][j].green * result_gy[i][j].green)));
            if (edge_green > 255)
            {
                edge_green = 255;
            }
            image[i][j].rgbtGreen = edge_green;

            int edge_blue = round(sqrt((result_gx[i][j].blue * result_gx[i][j].blue) + (result_gy[i][j].blue * result_gy[i][j].blue)));
            if (edge_blue > 255)
            {
                edge_blue = 255;
            }
            image[i][j].rgbtBlue = edge_blue;
        }
    }
}
