#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Changes the smiley to red, as it is currently black meaning all RGB values are set to 0.
            image[i][j].rgbtRed = 255;
        }
    }
}
