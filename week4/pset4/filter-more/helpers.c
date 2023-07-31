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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int gx[3][3] =  {{-1, 0, 1},
                     {-2, 0, 2},
                     {-1, 0, 1}};
    int gy[3][3] =  {{-1, -2, -1},
                     {0, 0, 0},
                     {1, 2, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxRedTotal = image[i][j].rgbtRed * gx[1][1];
            int gxGreenTotal = image[i][j].rgbtGreen * gx[1][1];
            int gxBlueTotal = image[i][j].rgbtBlue * gx[1][1];
            int gyRedTotal = image[i][j].rgbtRed * gy[1][1];
            int gyGreenTotal = image[i][j].rgbtGreen * gy[1][1];
            int gyBlueTotal = image[i][j].rgbtBlue * gy[1][1];
            if (i > 0)
            {
                gxRedTotal += image[i - 1][j].rgbtRed * gx[0][1];
                gxGreenTotal += image[i - 1][j].rgbtGreen * gx[0][1];
                gxBlueTotal += image[i - 1][j].rgbtBlue * gx[0][1];
                gyRedTotal += image[i - 1][j].rgbtRed * gy[0][1];
                gyGreenTotal += image[i - 1][j].rgbtGreen * gy[0][1];
                gyBlueTotal += image[i - 1][j].rgbtBlue * gy[0][1];
            }
            if (i < height - 1)
            {
                gxRedTotal += image[i + 1][j].rgbtRed * gx[2][1];
                gxGreenTotal += image[i + 1][j].rgbtGreen * gx[2][1];
                gxBlueTotal += image[i + 1][j].rgbtBlue * gx[2][1];
                gyRedTotal += image[i + 1][j].rgbtRed * gy[2][1];
                gyGreenTotal += image[i + 1][j].rgbtGreen * gy[2][1];
                gyBlueTotal += image[i + 1][j].rgbtBlue * gy[2][1];
            }
            if (j > 0)
            {
                gxRedTotal += image[i][j - 1].rgbtRed * gx[1][0];
                gxGreenTotal += image[i][j - 1].rgbtGreen * gx[1][0];
                gxBlueTotal += image[i][j - 1].rgbtBlue * gx[1][0];
                gyRedTotal += image[i][j - 1].rgbtRed * gy[1][0];
                gyGreenTotal += image[i][j - 1].rgbtGreen * gy[1][0];
                gyBlueTotal += image[i][j - 1].rgbtBlue * gy[1][0];
            }
            if (j < width - 1)
            {
                gxRedTotal += image[i][j + 1].rgbtRed * gx[1][2];
                gxGreenTotal += image[i][j + 1].rgbtGreen * gx[1][2];
                gxBlueTotal += image[i][j + 1].rgbtBlue * gx[1][2];
                gyRedTotal += image[i][j + 1].rgbtRed * gy[1][2];
                gyGreenTotal += image[i][j + 1].rgbtGreen * gy[1][2];
                gyBlueTotal += image[i][j + 1].rgbtBlue * gy[1][2];
            }
            if (i > 0 && j > 0)
            {
                gxRedTotal += image[i - 1][j - 1].rgbtRed * gx[0][0];
                gxGreenTotal += image[i - 1][j - 1].rgbtGreen * gx[0][0];
                gxBlueTotal += image[i - 1][j - 1].rgbtBlue * gx[0][0];
                gyRedTotal += image[i - 1][j - 1].rgbtRed * gy[0][0];
                gyGreenTotal += image[i - 1][j - 1].rgbtGreen * gy[0][0];
                gyBlueTotal += image[i - 1][j - 1].rgbtBlue * gy[0][0];
            }
            if (i > 0 && j < width - 1)
            {
                gxRedTotal += image[i - 1][j + 1].rgbtRed * gx[0][2];
                gxGreenTotal += image[i - 1][j + 1].rgbtGreen * gx[0][2];
                gxBlueTotal += image[i - 1][j + 1].rgbtBlue * gx[0][2];
                gyRedTotal += image[i - 1][j + 1].rgbtRed * gy[0][2];
                gyGreenTotal += image[i - 1][j + 1].rgbtGreen * gy[0][2];
                gyBlueTotal += image[i - 1][j + 1].rgbtBlue * gy[0][2];
            }
            if (i < height - 1 && j < width - 1)
            {
                gxRedTotal += image[i + 1][j + 1].rgbtRed * gx[2][2];
                gxGreenTotal += image[i + 1][j + 1].rgbtGreen * gx[2][2];
                gxBlueTotal += image[i + 1][j + 1].rgbtBlue * gx[2][2];
                gyRedTotal += image[i + 1][j + 1].rgbtRed * gy[2][2];
                gyGreenTotal += image[i + 1][j + 1].rgbtGreen * gy[2][2];
                gyBlueTotal += image[i + 1][j + 1].rgbtBlue * gy[2][2];
            }
            if (i < height - 1 && j > 0)
            {
                gxRedTotal += image[i + 1][j - 1].rgbtRed * gx[2][0];
                gxGreenTotal += image[i + 1][j - 1].rgbtGreen * gx[2][0];
                gxBlueTotal += image[i + 1][j - 1].rgbtBlue * gx[2][0];
                gyRedTotal += image[i + 1][j - 1].rgbtRed * gy[2][0];
                gyGreenTotal += image[i + 1][j - 1].rgbtGreen * gy[2][0];
                gyBlueTotal += image[i + 1][j - 1].rgbtBlue * gy[2][0];
            }
            int totalRed = round(sqrt(gxRedTotal * gxRedTotal + gyRedTotal * gyRedTotal));
            int totalGreen = round(sqrt(gxGreenTotal * gxGreenTotal + gyGreenTotal * gyGreenTotal));
            int totalBlue = round(sqrt(gxBlueTotal * gxBlueTotal + gyBlueTotal * gyBlueTotal));
            temp[i][j].rgbtRed = totalRed > 255 ? 255 : totalRed;
            temp[i][j].rgbtGreen = totalGreen > 255 ? 255 : totalGreen;
            temp[i][j].rgbtBlue = totalBlue > 255 ? 255 : totalBlue;
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
