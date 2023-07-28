// Este programa se encarga de recibir un archivo de audio .wav y modificar su volumen

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

uint8_t header[HEADER_SIZE];

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);


    fread(&header, HEADER_SIZE, 1, input);              //Lee el encabezado del archivo .wav y lo guarda en la varaibel header

    fwrite(&header, HEADER_SIZE, 1, output);            //Copia el encabezado almacenada en header y lo escribe en el archivo nuevo de salida

    short int sample;
    while (fread(&sample, 2, 1, input) == 1)            //Leo cada 2 bytes del archivo que conteiene el audio original y lo guardo en sample
    {                                                   //Si el documento llega a su fin el ciclo termina
        sample *= factor;                               //Multiplico sample por el factor dado en el argumento
        fwrite(&sample, 2, 1, output);                  //Guardo en el archivo de salida la muestra ya modificada por factor
    }


    // TODO: Read samples from input file and write updated data to output file


    // Close files
    fclose(input);
    fclose(output);
}
