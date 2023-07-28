/*Este progrma se encarga de leer un archivo de audio wav y crear uno nuevo que se reproduzca al reves*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    FILE *fileIn = fopen(argv[1], "r");

    if (fileIn == NULL)
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, fileIn);

    if (check_format(header) == 0)
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }

    FILE *fileOut = fopen(argv[2], "w");

    if (fileOut != NULL)
    {
        fwrite(&header, sizeof(WAVHEADER), 1, fileOut);
    }

    int size = get_block_size(header);

    BYTE *buffer = malloc(size);

    fseek(fileIn, -size, SEEK_END);

    while (ftell(fileIn) >= sizeof(header))
    {
        fread(buffer, size, 1, fileIn);
        fwrite(buffer, size, 1, fileOut);
        if (fseek(fileIn, -2 * size, SEEK_CUR))
        {
            return 1;
        }
    }

    fclose(fileOut);
    fclose(fileIn);
    free(buffer);

    return 0;
}

/*Esta funcion verifica que el archivo leido sea de tipo WAVE*/
int check_format(WAVHEADER header)
{
    BYTE correctFormat[] = {'W', 'A', 'V', 'E'};

    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != correctFormat[i])
        {
            return 0;
        }
    }
    return 1;
}

/*Esta funcion calcula y regresa el tama;o del archivo de audio*/
int get_block_size(WAVHEADER header)
{
    int size = 0;

    size = (header.bitsPerSample * header.numChannels) / 8;

    return size;
}