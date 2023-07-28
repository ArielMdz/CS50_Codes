#include "helpers.h"
#include <math.h>

/*Esta funcion se encarga de transforma una imagen en escala de grises, recibe una estructura de datos de un imagen
y su tama;os, se revisa cada pixel, se suman sus valores RGB y se promedian para ser igualados y asi crear el gris*/
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gray = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;

            image[i][j].rgbtRed = round(gray);
            image[i][j].rgbtGreen = round(gray);
            image[i][j].rgbtBlue = round(gray);
        }
    }
    return;
}

/*Este funcion se encarga de aplicar un filtro sepia a una imagen, recibe una estructura de datos de una imagen y su
tama;o, revisamos cada pixel y aplicamos unas ecuanciones para alterar el valor de  cada color de pixel cuidando los
limites de cada color*/
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float originalRed, originalGreen, originalBlue, sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;
            sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);
            if (sepiaRed >= 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            if (sepiaGreen >= 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            if (sepiaBlue >= 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

/*Esta funcion se encarga de reflejar una imagen, recibe una estructura de datos de una imagen y su tama;o
con una estructura temportal hacemos un cambio de posicion de los pixeles del eje vertical para crear el reflejo*/
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

/*Esta funcion se encarga de difuminar una imagen, recibe una estructura de datos de una imagen y su tama;o,
los valores de cada pixel son sumados y promediados con los pixeles de su alrededor y el valor es guardado en
una estructura temporal del mismo tama;o y misma posiciones para seguir trabajando los calculos con los valores
originales, una vez que se obtuvieron todos los nuevos valores de cada pixel en la estructura temporal se pasan
a la imagen original para ser remplazados*/
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float divisor;
    int red, green, blue;
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            divisor = red = green = blue = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (((i + k) >= 0 && (i + k) <= (height - 1)) && ((j + l) >= 0 && (j + l) <= (width - 1)))
                    {
                        divisor++;
                        red += image[i + k][j + l].rgbtRed;
                        green += image[i + k][j + l].rgbtGreen;
                        blue += image[i + k][j + l].rgbtBlue;
                    }
                }
            }
            temp[i][j].rgbtRed = round(red / divisor);
            temp[i][j].rgbtGreen = round(green / divisor);
            temp[i][j].rgbtBlue = round(blue / divisor);
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
