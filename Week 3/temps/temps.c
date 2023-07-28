// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>


#define NUM_CITIES 10

typedef struct
{
    char *city;
    int temp;
}
avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(void);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

/*La funcion se encarga de comparar y reorganizar los datos de la estructura utilizando el algoritmo bubble sort*/
void sort_cities(void)
{
    avg_temp temp;                                          //Se crea una estructura temporal para realizar el movimiento de datos
    for (int i = 0; i < NUM_CITIES - 1; i++)
    {
        for (int j = 0; j < NUM_CITIES - i - 1; j++)        //Se crea los ciclos para hacer la comparacion usando el algoritmo bubble sort
        {
            /*Verifico si el primer dato de temperatuta es menor a el siguiente dato, en caso de ser asi ejecuto la condicion if que
            realiza el cambio de poscion de los datos entre sin esto con ayuda de una tercer estructura para no sobreescribir datos*/
            if (temps[j].temp < temps[j + 1].temp)
            {
                temp = temps[j];
                temps[j] = temps[j + 1];
                temps[j + 1] = temp;
            }
        }
    }
}
