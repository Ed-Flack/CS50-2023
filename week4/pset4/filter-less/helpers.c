#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int grayscaleValue = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = grayscaleValue;
            image[i][j].rgbtGreen = grayscaleValue;
            image[i][j].rgbtBlue = grayscaleValue;
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
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int pixelCount = 1;
            double redTotal = image[i][j].rgbtRed;
            double greenTotal = image[i][j].rgbtGreen;
            double blueTotal = image[i][j].rgbtBlue;
            if (i > 0)
            {
                redTotal += image[i - 1][j].rgbtRed;
                greenTotal += image[i - 1][j].rgbtGreen;
                blueTotal += image[i - 1][j].rgbtBlue;
                pixelCount++;
            }
            if (i < height - 1)
            {
                redTotal += image[i + 1][j].rgbtRed;
                greenTotal += image[i + 1][j].rgbtGreen;
                blueTotal += image[i + 1][j].rgbtBlue;
                pixelCount++;
            }
            if (j > 0)
            {
                redTotal += image[i][j - 1].rgbtRed;
                greenTotal += image[i][j - 1].rgbtGreen;
                blueTotal += image[i][j - 1].rgbtBlue;
                pixelCount++;
            }
            if (j < width - 1)
            {
                redTotal += image[i][j + 1].rgbtRed;
                greenTotal += image[i][j + 1].rgbtGreen;
                blueTotal += image[i][j + 1].rgbtBlue;
                pixelCount++;
            }
            if (i > 0 && j > 0)
            {
                redTotal += image[i - 1][j - 1].rgbtRed;
                greenTotal += image[i - 1][j - 1].rgbtGreen;
                blueTotal += image[i - 1][j - 1].rgbtBlue;
                pixelCount++;
            }
            if (i > 0 && j < width - 1)
            {
                redTotal += image[i - 1][j + 1].rgbtRed;
                greenTotal += image[i - 1][j + 1].rgbtGreen;
                blueTotal += image[i - 1][j + 1].rgbtBlue;
                pixelCount++;
            }
            if (i < height - 1 && j < width - 1)
            {
                redTotal += image[i + 1][j + 1].rgbtRed;
                greenTotal += image[i + 1][j + 1].rgbtGreen;
                blueTotal += image[i + 1][j + 1].rgbtBlue;
                pixelCount++;
            }
            if (i < height - 1 && j > 0)
            {
                redTotal += image[i + 1][j - 1].rgbtRed;
                greenTotal += image[i + 1][j - 1].rgbtGreen;
                blueTotal += image[i + 1][j - 1].rgbtBlue;
                pixelCount++;
            }
            temp[i][j].rgbtRed = round(redTotal / pixelCount);
            temp[i][j].rgbtGreen = round(greenTotal / pixelCount);
            temp[i][j].rgbtBlue = round(blueTotal / pixelCount);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
