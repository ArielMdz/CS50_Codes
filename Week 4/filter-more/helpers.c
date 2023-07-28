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
                    if (((i + k) >= 0 && (i + k) < (height)) && ((j + l) >= 0 && (j + l) < (width)))
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

/*Esta funcion recibe la estructura de datos de una imagen y sus tama;os y con esto se encarga de detectar los bordes en
una imagen, esto lo hace verificando si los pixeles de los lados son muy diferentes, el valor del nuevo pixel se realiza
elevando al cuadrado 2 sumas ponderadas, sumandolas y sacando su raiz cudrada, siempre cuidando el limite de cada pixel,
este valor se guarda dentro en una estructura temporal y una vez calculados todos los pixeles son remplazados en la imagen
original.*/
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    float Gxred, Gxgreen, Gxblue, Gyred, Gygreen, Gyblue;
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Gxred = Gxgreen = Gxblue = Gyred = Gygreen = Gyblue = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (((i + k) >= 0 && (i + k) <= (height - 1)) && ((j + l) >= 0 && (j + l) <= (width - 1)))
                    {
                        Gxred += Gx[k + 1][l + 1] * image[i + k][j + l].rgbtRed;
                        Gxgreen += Gx[k + 1][l + 1] * image[i + k][j + l].rgbtGreen;
                        Gxblue += Gx[k + 1][l + 1] * image[i + k][j + l].rgbtBlue;

                        Gyred += Gy[k + 1][l + 1] * image[i + k][j + l].rgbtRed;
                        Gygreen += Gy[k + 1][l + 1] * image[i + k][j + l].rgbtGreen;
                        Gyblue += Gy[k + 1][l + 1] * image[i + k][j + l].rgbtBlue;
                    }
                }
            }

            temp[i][j].rgbtRed = (sqrt((pow(Gxred, 2) + pow(Gyred, 2))) > 255) ? 255 : round(sqrt((pow(Gxred, 2) + pow(Gyred, 2))));
            temp[i][j].rgbtGreen = (sqrt((pow(Gxgreen, 2) + pow(Gygreen, 2))) > 255) ? 255 : round(sqrt((pow(Gxgreen, 2) + pow(Gygreen, 2))));
            temp[i][j].rgbtBlue = (sqrt((pow(Gxblue, 2) + pow(Gyblue, 2))) > 255) ? 255 : round(sqrt((pow(Gxblue, 2) + pow(Gyblue, 2))));

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
