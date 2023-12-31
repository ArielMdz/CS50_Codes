#include "helpers.h"
#include <stdio.h>

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++){
            if (image[i][j].rgbtBlue == 0 && image[i][j].rgbtRed == 0 && image[i][j].rgbtGreen == 0)
            {
                image[i][j].rgbtRed = 0x5D;
                image[i][j].rgbtGreen = 0x2E;
                image[i][j].rgbtBlue = 0x86;
            }
        }
    }
}
