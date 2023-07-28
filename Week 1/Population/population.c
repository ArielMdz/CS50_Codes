/*Este codigo solicita un valor incial de una poblacion y un valor final esperado en la poblacion muere 1/4 del total
cada a;o pero nace 1/3 del total de la poblacion teniendo un crecimiento exponecia respecto al tiempo, en base a esto
se calcula el minimo de a;os requerido para llegar a la poblacion final
La poblacion inical no puede ser menor a 9*/

#include <cs50.h>
#include <stdio.h>

int initialPopulationSize = 0, finalPopulationSize = 0, actualPopulation, years;

int main(void)
{
    do
    {
        printf("Ingresa el tamaño de poblacion inicial: ");
        scanf("%u", &initialPopulationSize);
        if(initialPopulationSize < 9){
            printf("El tamaño de la poblacion inicial debe ser mayor o igual a 9.\n");
        }
    }while (initialPopulationSize < 9);

    do
    {
        printf("Ingresa el tamaño de poblacion final: ");
        scanf("%u", &finalPopulationSize);
        if(finalPopulationSize <= initialPopulationSize){
            printf("El tamaño de la pobalcion final no puede ser menor a la poblacion inicia.\n");
        }
    }while (finalPopulationSize <= initialPopulationSize);

    actualPopulation = initialPopulationSize;
    while(actualPopulation < finalPopulationSize){
        years++;
        actualPopulation = actualPopulation + (actualPopulation/3) - (actualPopulation/4);
    }

    printf("Iniciando con una poblacion de %u necesitamos por lo menos %u años\npara alcanza una poblacion de %u", initialPopulationSize, years, finalPopulationSize);

    printf("\n\nPoblacion inicial: %u\nPoblacion Final: %u\nAños: %u\n", initialPopulationSize, finalPopulationSize, years);
}