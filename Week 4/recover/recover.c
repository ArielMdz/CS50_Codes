/*Este Programa se encarga de recuperar imagenes de una memoria, analiza los datos del archivo y si encuentra los primeros bytes
representativos de un archivo JPG crea un archivo y comienza a guardar los datos, cuando encuentra una nueva imagen cierra el archivo
anterior y abre uno nuevo para almacenar otra imagen, considerando que los archivos de tipo FAT estan inicializado con bloques de 512bytes
podemos analizar los datos en bloques.*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)                                                          //Se cuida de recibir un argumento, de no ser asi regresa error
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *fileIn = fopen(argv[1], "r");                                     //Se abre el archivo de lectura del cual seran recuperadas las imagenes

    if (fileIn == NULL)                                                     //Si el archivo no puede abrirse regresa un error
    {
        printf("Error de lectura de archivo\n");
        return 1;
    }

    FILE *fileOut = NULL;                                                   //Se crea un puntero FILE que se usara para abrir y cerrar los archivos

    unsigned char buffer[512];                                              //Se crea una variable de buffer que almacenara 512bytes(1 bloque)
    char filename[8];                                                       //Creamos variable que almacena el nombre del archivo jpg

    int jpeg = 0;

    while (fread(buffer, 512, 1, fileIn) == 1)                              //Creamos un ciclo que se ejecutara siempre y cuando se puedan seguir leyendo un bloque de datos completo
    {
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF)    //Verificamos los primero bytes del buffer para verifcar si encontramos una nueva imagen
        {
            if (fileOut != NULL)                                            //verficamos si existe un archivo abierto y de ser asi lo cerramos
            {
                fclose(fileOut);
            }
            sprintf(filename, "%03d.jpg", jpeg++);                          //Cambiamos el nombre del nuevo archivo

            fileOut = fopen(filename, "w");                                 //Creamos y abrimos un nuevo archivo en modo escritura "w"
        }

        if(fileOut != NULL)                                                 //Si existe un archivo abierto entonces guardamos el buffer de datos(bloque) en el
        {
            fwrite(buffer, 512, 1, fileOut);
        }
    }

    fclose(fileOut);                                                        //Cerramos ambos archivos y terminamo el programa
    fclose(fileIn);

    return 0;
}