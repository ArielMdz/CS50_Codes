/*Este codigo simula una version simple del juego scrabble, cada letra del alfabeto correspone a una puntuancion,
el programa se encarga de recibir 2 palabras correspondientes a 2 jugadores, las palabras se evaluaran sumando
los puntajes de cada letra y segun la palabra ganadora respondera diciendo quien es el ganador.*/

#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char player1[] = "Player 1: ";
char player2[] = "Player 2: ";

int compute_score(char word[], char text[]);


int main(void)
{
    char word1[100] = { };
    char word2[100] = { };

    int score1 = compute_score(word1, player1);
    int score2 = compute_score(word2, player2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie\n");
    }

    return 0;
}

int compute_score(char word[], char text[]){
    int size = 0, sumScore = 0;
    bool validation;

    do
    {
        validation = false;
        printf("%s", text);
        scanf("%s", word);
        size = strlen(word);
        for (int i = 0; i < size; i++)
        {
            if (word[i] >= 'A' && 'Z' >= word[i] )
            {
                sumScore += POINTS[word[i] - 'A'];
            }
            else if (word[i] >= 'a' && 'z' >= word[i])
            {
                sumScore += POINTS[word[i] - 'a'];
            }
        }
    }
    while (validation);

    return sumScore;
}