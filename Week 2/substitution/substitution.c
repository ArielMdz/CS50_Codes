/*Este programa se encarga de recibir una palabra o frase y encriptarla utilizando un alfabeto desordenado
el programa solo sustituira las letras mantenendo simbolos y espacios igueles, ademas de que respetara
el uso de maysuculas y minusculas*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>

/*En la funcion principal recibe en linea de comandos el alfabeto competo de forma aleatoria, sin repetir
letras y procurando que no falte ninguna de las 26 letras, ademas debe ser escrito en un solo comando, ya
que no funcionara con mas o menso de un comando*/
int main(int argc, string argv[])
{
    /*En la primera parte se encarga de detectar errores, si no se recibe nada en linea de comando o recibe
    mas de un dato imprimira el modo de llamado del programa y regresara un error(return 1), debera recibir
    tambien los 26 caracteres del alfabeto si faltan o sobran caracteres lo imprimira y retornara un error*/
    int size;
    if (argc == 2)
    {
        size = strlen(argv[1]);
        if (size != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    /*En esta seccion se revida todas las letras del alfabeto ingresados cuidando que ninguna letra
    se encuentra duplicada, en caso de repetirse regresara un error depues de imprimir un mensaje, de
    igual forma revisa que solo se ingresen letras*/
    for (int i = 0; i < size; i++)
    {
        if ((argv[1][i] >= 'A' && argv[1][i] <= 'Z') || (argv[1][i] >= 'a' && argv[1][i] <= 'z'))
        {
            for (int j = 0; j < size; j++)
            {
                //Se comparan que las letras no esten duplicadas distinguiendo entre mayusculas y minusculas
                if((argv[1][i] == argv[1][j] || argv[1][i] - 32 == argv[1][j] || argv[1][i] == argv[1][j] - 32) && i != j)
                {
                    printf("No se admiten caracteres dulpicados\n");
                    return 1;
                }
            }
        }
        else
        {
            printf("Los caracteres solo pueden ser letras\n");
            return 1;
        }
    }

    //Creo una variable char con 100 espacios y recibo la palabra a codificar
    char text[100];
    printf("plaintext:  ");
    scanf("%[^\n]", text);
    int i = 0;

    /*Durante este ciclo se realiza la sustitucion de cada letra evaluando todas las posibilidades
    considerando que solo se remplazan letras, que las letras mayusculas se deben rempazar por mayusculas
    y de la misma forma con la minusculas*/
    do
    {
        //Si el texto a codificar es en mayuscula
        if (text[i] >= 'A' && 'Z' >= text[i])
        {
            //Si la letra del alfabeto es mayucula
            if ((argv[1][text[i] - 'A']) >= 'A' && 'Z' >= (argv[1][text[i] - 'A']))     //Compara que la pocision de la letra a sustituir sea mayuscula
            {                                                                           //Ejemplo la letra 'A' al ser la primeara sera sustituida por la primera letra del alfabeto ingresado
                text[i] = argv[1][text[i] - 'A'];                                       //Se sustiuye directamente por a letra del alfabeto con la misma poscion
            }
            //Si la letra del alfabeto es minuscula
            else                                                                        //Si la letra no es mayuscula entonces la letra del alfabeto es minuscula
            {                                                                           //En este caso al ser minuscula debe ser cambiada por la misma letra del alfabeto pero en mayuscula
                text[i] = (argv[1][text[i] - 'A']) - 32;                                //Utilizamos la misma letra a sustituir restando 32 posiciones que en ascii representa la mayuscula
            }
        }
        //Si el texto a codificar es en minuscula
        else if (text[i] >= 'a' && 'z' >= text[i])
        {
            //Si la letra del alfabeto es minuscula
            if ((argv[1][text[i] - 'a']) >= 'a' && 'z' >= (argv[1][text[i] - 'a']))     //Compara que la pocision de la letra a sustituir sea minuscula
            {                                                                           //Ejemplo la letra 'a' al ser la primeara sera sustituida por la primera letra del alfabeto ingresado
                text[i] = argv[1][text[i] - 'a'];                                       //Se sustiuye directamente por a letra del alfabeto con la misma poscion
            }
            //Si la letra del alfabeto es mayuscula
            else                                                                        //Si la letra no es minuscula entonces la letra del alfabeto es mayuscula
            {                                                                           //En este caso al ser mayuscula debe ser cambiada por la misma letra del alfabeto pero en minuscula
                text[i] = (argv[1][text[i] - 'a']) + 32;                                //Utilizamos la misma letra a sustituir sumando 32 posiciones que en ascii representa la minuscula
            }
        }
        i++;
    }
    while (text[i] != '\0');                                                            //El ciclo termina al finalizar la cadena de caracteres

    //Se imprime el resultado de la palabra encriptada y retorna 0
    printf("ciphertext:  %s\n", text);

    return 0;
}