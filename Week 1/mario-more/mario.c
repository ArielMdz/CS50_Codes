/*Este codigo se encarga de imprimir una escalera doble de mario teniendo entre ellas 2 espacios de separacion,
el tama;o recibido sera entre 1 y 8 repitiendo la pregunta en dado caso de otorgar un valor distinto*/

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
    while (height <= 0 || height > 8);

    /*El ciclo for funcionara respecto al la altura de la escalera, restara la varible i hasta
    que esta sea igual a 0 y deje de cumplir con la condicion*/
    for (int i = height; i != 0; i--)
    {
        /*Con el segundo ciclo recorreremos la posicion en la terminal e imprimiremos '#' para formar la escalera,
        mientras j sea mayor o igual que i - 1 y menores que el tama;o de la escalera se imprimiran '#', apartir de
        que j sea del tama;o de la la escalera o una mayor imprimira un espacio para la separacionde las escaleras,
        para el otro lado de la escalera se imprimira '#' siempre que j sea mayor al tama;o de la escalera + 1, cuando
        j sea identido a 2 * (height+1) se imprimira un '#' junto un salto de linea para terminar el escalon y un break
        para salir del ciclo*/
        for (int j = 0; j < 2 * (height + 1); j++)
        {
            if (j == 2 * (height + 1) - i)
            {
                printf("#\n");
                break;
            }
            else if ((j >= i - 1 && j < height) || (j > height + 1))
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }

    }
}