/*Este codigo recibe argumentos por linea de comandos, la cantidad de argumentos recibidos
solo debe ser uno o regresara un error, el comando debe ser alguna palabra, el programa
remplazara algunas vocales de la palabra y seran remplazadas por numeros de la siguente forma:
a -> 6     e -> 3     i -> 1     o -> 0*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(char* text);

int main(int argc, string argv[])
{
    /*Esta condicion evalua la cantidad de argumentos recibidos el cual debe ser igual a 2, en caso
    de ser menor o mayor imprimira un mensaje de error y retornar 1*/
    if (argc == 1 || argc > 2)
    {
        printf("No ingresaste un argumento\n");
        return 1;
    }
    /*Si la cantidad de argumentos es correcta entonces llama a una funcion que se encargara de remplazar
    las letras determinadas de la palabra por sus numeros correspondientes, este regresara un string
    que sera impreso*/
    else
    {
        string text = replace(argv[1]);
        printf("%s\n", text);
    }


}

/*Esta funcion recibe una cadena de texto, se evaluara el tama;o de texto para ser analizado caracter por caracter
en un ciclo for, utilizando un switch case evaluaremos si el caso de las letras se cumple para ser remplazado por
un su determinado numero, la palabra modificada sera regresada por la funcion*/
string replace(char* text)
{
    int size;
    size = strlen(text);
    for (int i = 0; i < size; i++)
    {
        switch (text[i])
        {
            case 'a':
                text[i] = '6';
                break;

            case 'e':
                text[i] = '3';
                break;

            case 'i':
                text[i] = '1';
                break;

            case 'o':
                text[i] = '0';
                break;
        }
    }
    return text;
}
