/*Ese programa genera una version simple de la funcion atoi pero usando recursividad, recibe un caracter de valor
numerico postivo y lo convierte a un valor entero, no admmite decimales, signos ni caracteres no numericos*/

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(char *input);

int main(void)
{
    char input[10];
    printf("Enter a positive integer: ");
    scanf("%s", input);
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

/*Esta funcion se encarga de recibir un cadena y utilizando la recursividad convertir este valor
en entero para retornarlo por completo.
Ejemplo:
-Paso 1: Se envia una cadena "123\0" almacena  num = 3 como entero y acorta la cadena "12\0" para llamar de nuevo la funcion
-Paso 2: Recibe la cadena "12\0", almacena num = 2 como entero y acorta la cadena "1\0" para llamar de nuevo la funcion
-Paso 3: Recibe la cadena "1\0", almaena num = 1 como enteros y acorta la cadena "\0", al llegar a limite i = 1 la condicion no se cumpe y se rotorna num
-Paso 4: Regresa el valor retornado = 1, se multiplica por 10 y se suma al valor guardado en num una llamado anteriro que es = 2, retorna la suma num = 12
-Paso 5: Regresa el valor retornado = 12, se multiplica por 10 y se suma al valor guardado en num una llamado anteriro(en este caso el primer llamado) que
 es = 3, retorna la suma num = 123*/
int convert(char *input)
{
    int num = 0, i = 0;                         //Declaramos e inicializamos varibles
    while (input[i] != '\0')                    //Creamos un ciclo que se detenga hasta encontrar el final de la cadena
    {
        i++;                                    //Aumenta variable 'i'
    }

    num = input[i - 1] - '0';                   //Lee y la poscion anteriro correspondiente al ultimo digito y lo pasa a entero

    input[i - 1] = '\0';                        //Remplaza el ultimo numero por '\0' para acortar la cadena de caracteres
    if (i != 1)                                 //Ejecuta una condicion que asegure la recursividad solo para la cantidad de numeros
    {
        num += 10 * convert(input);             //Llama la funcion para recursividad y retorna el valor entero, se multiplica por 10 y se suma
    }

    return num;                                 //Retorna valor entero
}