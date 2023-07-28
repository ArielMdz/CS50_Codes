#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int luhnsAlgorithm(int size, char *creditCard);
void typeCard(int n, int size, int startNum);

int main(void)
{
    char creditCard[16];                        //Declaramos una variable char que almacenara los numeros de la tarjeta
    int size = 0, character = 0;                //Declaramos e inicializamos algunas variables para la cantidad de numeros de la tarjeta y para la verificacion de el ingreso de datos correctos
    /*Se ejecuta un ciclo que solicitara el numero de una tarjeta, se guarda en una variable
    la cantidad de numeros(tama;o) que contiene la tarjeta, en caso de ingresar un dato no numerico
    o de que se ingresen mas de 16 numeros de tarjeta se volvera a repetir el ciclo hasta ingresar un numero correcto*/
    do
    {
        printf("Numero de Tarjeta: ");
        scanf("%s", creditCard);
        size = strlen(creditCard);
        for (int i = 0; i < size; i++)
        {
            character = creditCard[i] - '0';
            if (character < 0 || character > 9)
            {
                size = 17;
                break;
            }
        }
    }
    while (size > 16);

    int sum = luhnsAlgorithm(size, creditCard);

    int startNum = ((creditCard[0] - '0') * 10) + (creditCard[1] - '0');
    typeCard(sum, size, startNum);
}


/*Esta funcion utiliza el algoritmo de Luhn, este consiste en en verificar si una tarjeta es real en base a unas ecuaciones
donde el resultado de la suma debe termina en 0, este consiste en multiplicar por 2 cada 2 digitos de una tarjeta empezando
a partir del penultimo digito, en caso de que algun resultado supere o sea igual a 10, ejemplo: 12, debera separarse siendo
valores de 1 y 2, cada uno de estos resultados debera sumarse y acontinuacion sumar el resto de numeros de la tarjeta.*/
int luhnsAlgorithm(int size, char *creditCard)
{
    int sum = 0;
    for (int i = 1; i <= size; i++)                         //Se aplica un ciclo for que recorrera todos los numeros de la tajeta segun la cantidad de numero que contenga
    {
        if (size % 2 == 0)                                  //Si la cantidad de numero de la tarjeta es par se aplicara esta condicion
        {
            int num = creditCard[i-1] - '0';                //Se declara una variable y iniciliza con un numero de la tarjeta
            if (i % 2 != 0)                                 //Los numeros impares seran multiplicados por 2 y sumados a una variable
            {
                if ((num * 2) > 9)                          //Si el numero multiplicado es mayor a 9 se separa y se suma cada uno de forma independiente
                {
                    sum++;
                    sum += ((num * 2) - 10);
                }
                else
                {
                    sum += num * 2;
                }
            }
            else                                            //Los numeros pares seran simplemente agregados a la sumatoria
            {
                sum += num;
            }
        }

        /*Para el caso de que la cantidad de numeros de la tarjeta sea impar el proceso se repite pero esta vez multiplicando los numeros pares
        para despues sumarlos y simplemente sumando los numero impares de la tarjeta*/
        else
        {
            int num = creditCard[i-1] - '0';
            if (i % 2 == 0)
            {
                if ((num * 2) > 9)
                {
                    sum++;
                    sum += ((num * 2) - 10);
                }
                else
                {
                    sum += num * 2;
                }
            }
            else
            {
                sum += num;
            }
        }
    }
    return sum;
}


/*Esta funcion evalua si la tajeta es valida o no, si el numero resultante del algoritmo de Luhn no termina en 0 entoces
la tarjeta es invalida, si termina en 0 deberan evaluarse algunas condicones para detectar si es valida y a que pertence
-Las tarjetas Mastercard deben contener 16 digitos y deben empezar con los numero 51, 52, 53, 54 y 55
-Las tarjetas de American Express deben contener 15 digitos y comenzar con 34 o 37
-Las tarjetas Visa pueden contener entre 13 y 16 digitos y iniciar con el numero 4
Si esas condiciones no se cumplen la tarjeta sera invalida*/
void typeCard(int n, int size, int startNum)
{
    n = n - ((n / 10) * 10);

    if (n == 0)
    {
        if (size == 16 && startNum > 50 && startNum < 56)
        {
            printf("MASTERCARD\n");
        }
        else if (size == 15 && (startNum == 34 || startNum == 37))
        {
            printf("AMEX\n");
        }
        else if (size >= 13 && size <= 16 && (startNum / 10) == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else
    {
        printf("INVALID\n");
    }
}