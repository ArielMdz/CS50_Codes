/*Este codigo esta basado en el juego worble, consiste en solicitar un argumento en linea de comando que debera
corresponder a un numero entre el 5 y 8, en caso de no ser asi regresara algun erros, si el argumento es valido
entonces el programa seleccionara una palabra al azar con el numero de letra dado por el argumeto, seguido se les
dara un numero de opotunidades para adivinar la palabra mostrando en verde las letras acertadas correctamente, en
amarillo las letras pertenecientes a la palabra pero mal colocadas y en rojo las letras que no corresponden a la
palabra, el programa termina al acertar todas las letras en su poscion o al finalizar los intentos*/

#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

// user-defined function prototypes
char* get_guess(int wordsizen);
int check_word(char* guess, int wordsize, int status[], char* choice);
void print_word(char* guess, int wordsize, int status[]);


int main(int argc, char* argv[])
{
    /*El programa principal se recibi el numero de argumetos teniendo que ser solo un argumetno recibido, de lo contrario
    imprimira la forma correcta de llamado y regresara un error, tambien verificara que el argumento sera aceptable, de lo contrario
    muestra los argumetnos aceptables y regresa error*/
    if (argc != 2)
    {
        printf("Usage: ./wordle wordsize\n");
        return 1;
    }

    int wordsize = 0;

    if (atoi(argv[1]) >= 5 && atoi(argv[1]) <= 8)
    {
        wordsize = atoi(argv[1]);
    }
    else
    {
        printf("Error: wordsize must be either 5, 6, 7, or 8\n");
        return 1;
    }

    // open correct file, each file has exactly LISTSIZE words
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    // load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // pseudorandomly select a word for this game
    srand(time(NULL));
    char* choice = options[rand() % LISTSIZE];

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // print greeting, using ANSI color codes to demonstrate
    printf(GREEN"This is WORDLE50"RESET"\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    // main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // obtain user's guess
        char* guess = get_guess(wordsize);

        // array to hold guess status, initially set to zero
        int status[wordsize];

        for (int j = 0; j < wordsize; j++)
        {
            status[j] = WRONG;
        }

        //Recibe el valor del puntaje obtenido
        int score = check_word(guess, wordsize, status, choice);

        printf("Guess %i: ", i + 1);

        // Print the guess
        print_word(guess, wordsize, status);

        /* compara si el puntaje obtenido es igual al maximo puntaje posible, si cumple entonces
        won se vuelve true y con un break se sale del ciclo para finalizar el juego, si la condicion no
        se cumple el ciclo continuara ejecutandose hasta alcanzar el numero de intentos*/
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }
    /*Si se adivino la palabra won == true y imprimira "You won!", en caso contrario, imprimira un mensaje
    que le diga al usuario cuál era la palabra objetivo, para que sepa que el juego fue honesto con él*/
    if (won)
    {
        printf("You won!\n");
    }
    else
    {
        printf("%s\n", choice);
    }
    // that's all folks!
    return 0;
}

/*la funcion get_guess recibe como paramentro el numero de letras que contendra la palabra, solicita al usuario una palabra
y retorna dicha palabra, en caso de que el usuario ingrese una palabra con un numero de letras distinta al asignado a un inicio
se repetira la solicitud hasta que ingrese una palabra aceptable*/
char* get_guess(int wordsize)
{
    int size = 0;
    /*asigno un tamaño de memoria para 20 caracteres, sizeof(char) representa el tamaño en bytes de un caracte
    se multiplica para establecer el tamaño de caracteres, malloc asigna memoria dinamica sin inicializar, recibe
    la cantidad de bytes a asignar y regresa un puntero void*, con (char*) convertimos el puntero void* a un
    puntero char.*/

    char* guess = (char*)malloc(sizeof(char) * 20);
    do
    {
        printf("Input a %i-letter word: ", wordsize);
        scanf("%s", guess);
        size = strlen(guess);
    }
    while (size != wordsize);
    return guess;
}

/*La funcion check_word recibe como parametros las palabras del usuario y la palabra a adivinar, la cadena de valores
enteros correspondiente a el puntaje de cada letra y el tamaño de la palabra, utilizando 2 for se compara cada una de
las letras de ambas palabras entre si, la letra y poscion coinciden entre palabras se le asigna un 2(EXACT) a esa posicion
usando la cadena status[], si la letra coinciden pero no esta bien poscionada solo se asignara un puntaje de 1(CLOSE), si
la letra no pertenece a la palabra entonces se mantendra el puntaje en 0(WRONG), al finalizar la comparacion de cada letra
esta ira sumandose a score y sera retornado*/
int check_word(char* guess, int wordsize, int status[], char* choice)
{
    int score = 0;

    for (int i = 0; i < wordsize; i++)
    {
        for (int j = 0; j < wordsize; j++)
        {
            if (guess[i] == choice[j] && i == j)
            {
                status[i] = EXACT;
                break;
            }
            else if (guess[i] == choice[j])
            {
                status[i] = CLOSE;
            }
        }
        score += status[i];
    }

    return score;
}

/*La funcion print_word recibe la palabra del usuario, el tamaño y el puntaje de cada letra, por medio de un for
revisa el puntaje de cada letra y imprime la letra con un fondo de color distinto segun corresponda a su puntaje:
-El puntaje EXACT sera color verde
-El puntaje CLOSE sera color amarillo
-El puntaje WRONG sera color rojo
*/
void print_word(char* guess, int wordsize, int status[])
{
    for (int i = 0; i < wordsize; i++)
    {
        if (status[i] == EXACT)
        {
            printf(GREEN"%c", guess[i]);
        }
        else if (status[i] == CLOSE)
        {
            printf(YELLOW"%c", guess[i]);
        }
        else
        {
            printf(RED"%c", guess[i]);
        }
    }
    printf(RESET"\n");
    return;
}
