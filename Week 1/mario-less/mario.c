/*Este codigo recibe el tama;o que debera tener una escalera, siendo el limite de 1 a 8
y la imprimira en la teminal*/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        printf("Dame el tamaño de la escalera: ");
        scanf("%u", &height);
    }
    while (height<=0 || height>8);

    /*El ciclo for funcionara respecto al la altura de la escalera, restara la varible i hasta
    que esta sea igual a 0 y deje de cumplir con la condicion*/
    for (int i = height; i != 0; i--)
    {
        /*Con el segundo ciclo recorreremos la posicion en la terminal e imprimiremos '#' para formar la escalera,
        mientras j sea menor que i se imprimiran espacios vacios, una ves sea igual o mayor imprimira '#', al i ir disminuyendo
        cada vez se imprimiran mas '#' formando asi la escalera, al final de cada ciclo for j se imprimira un salto de linea*/
        for (int j = 1; j <= height; j++)
        {
            if (j < i)
            {
               printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}