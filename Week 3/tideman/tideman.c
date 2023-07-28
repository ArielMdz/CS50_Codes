/*Este programa simula un sistema de votancion utilizando las elecciones de Tideman, el programa recibe a los candidatos como
argumento por comando de linea al llamar el programa, solicita el numero de votantes y procede a solicitar la eleccion de cada
votante en orden y al finalizar con el metodo de tideman seleccion al ganador*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
char* candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, char* name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, char* argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count;
    printf("Number of voters: ");
    scanf("%i", &voter_count);

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            char name[20];
            printf("Rank %i: ", j + 1);
            scanf("%s", name);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

/*Esta funcion resive el ranking del candidato para el votante, el nombre del candidato y un array con los ranks
si no coincide en nombre del candidato no concide con los candidatos disponibles devuelve un true, si el candidato
coincide guarda al candidadato en el array ranks en su respectiva posicion rank*/
bool vote(int rank, char* name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

/*Esta funcion compara la posicion de los candidatos segun el ranks que le da cada votante comparando uno
contra uno cada candidato sumando uno a la matriz preferences en la poscion del ganador.
Ejemplo:
Candidatos: a b c       Votantes: 2
Votante 1:              Votante 2:
Rank 1: a               Rank 1: c
Rank 2: b               Rank 2: a
Rank 3: c               Rank 3: b
Resultado 1:            Resutado 2:
  0 1 1                   0 2 1
  0 0 1                   0 0 1
  0 0 0                   1 1 0  */
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j){
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }
    return;
}

/*Esta funcion crea todos los pares posibles y guarda en un structur al ganador y perdedor
en caso de existir empate no se considera como un par mas*/
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;

            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    /*
    printf("pairs: %i\n", pair_count);

    for (int i = 0; i < pair_count; i++)
    {
        printf("%s - %s\n", candidates[pairs[i].winner], candidates[pairs[i].loser]);
    }
    */
    return;
}

/*Esta funcion realiza un reacomo de los pares dejando como primera opcion a los que ganaron por una candidad de votos mayor
y colocando a lo ultimo a las parejas con una menor diferencia de votos*/
void sort_pairs(void)
{
    pair temp;                                          //Se crea una estructura temporal para realizar el movimiento de datos
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1 ; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
    /*
    for (int i = 0; i < pair_count; i++)
    {
        printf("%s -- %s\n", candidates[pairs[i].winner], candidates[pairs[i].loser]);
    }
    */
    return;
}

/*Esta funcion utiliza los pares ganadores ordenados de mayor a menor ventaja, crea "flechas" que apunten a su perdedor colacondo
un true(1) en una matriz, pero cuida no crear ciclos, manteniendo asi una unica fuente la cual sera el candidato ganador.*/
void lock_pairs(void)
{
    int repeat, check;
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;                 //Coloca ganador y perdedor con 1 y 0 en la matriz correspondiente a su poscion
        locked[pairs[i].loser][pairs[i].winner] = false;
        check = pairs[i].winner;                                        /*Guarda al ganador para verificar si hay "flechas" que lo apunten, esto se
                                                                        hace revisando si existen unos en su columna de la matriz*/
        do
        {
            repeat = 0;                                                 //inicializamos la varaible repeat para no cumplir la condicion del while
            if (pairs[i].loser == check)                                //Verfico que la columna a revisar no sea la misma que del perdedor de este par
            {                                                           //En caso de ser la misma significa que se crea un ciclo por lo que se rechaza esta "flecha"
                locked[pairs[i].winner][pairs[i].loser] = false;        //Se regresa la "flecha" a 0 para ser ignorada y no crar ciclos
                break;                                                  //Se termina el ciclo while para verficar la siguiente pareja
            }
            /*Se verifica la columna del ganador en busca de "flechas"(1), en caso de encontrarla sustituimos check por j para realizar
            verificar la nueva coumna cuidando asi que no exista un trazado de "flechas" ciclicas*/
            for (int j = 0; j < candidate_count; j++)
            {
                if (locked[j][check] == true)                           //Verificamos la columna del ganador en busca de "flechas"(1)
                {
                    repeat = 1;                                         //definimos variable para repetir el ciclo while
                    check = j;                                          //Cambiamos columana a revisar ahora revisarndo la del nuevo ganador
                    break;                                              //Salimos del ciclo for
                }
            }
        }
        while (repeat == 1);
    }
    /*
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
           printf("%i ", locked[i][j]);
        }
        printf("\n");
    }
    */
    return;
}

/*Esta funcion revisa las columnas de las matriz loocked que guarda las "flechas" en busca de la fuente
la cual sera definida como ganadora, la funte no posee flechas hacia ella por lo que toda su columna debe
estar en 0's*/
void print_winner(void)
{
    int count, validation;
    for (int i = 0; i < candidate_count; i++)
    {
        count = 0;
        validation = 0;
        for (int j = 0; j < candidate_count; j++)
        {
           if (locked[j][i] == true)
           {
                count++;
                break;
           }
           if (locked[i][j] == true)
           {
                validation++;
           }
        }
        if (count == 0 && validation > 0){
            printf("%s\n", candidates[i]);
            break;
        }
    }
    return;
}