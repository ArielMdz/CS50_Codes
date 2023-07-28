/*Este programa solicita un un texto y lo evalua en un nivel o grado de dificultad,
al recibir el texto cuenta la cantidad de letras que contiene, utilizando los espacios
en blanco cuenta la cantidad de palabras y con '?', '!' y '.' cuenta las oraciones.
En base a esto realiza unos calculos con los cuales se define el grado y lo impirme*/

#include <cs50.h>
#include <stdio.h>

void gradeCalculate(int letter, int words, int sentences);
void count(int *letter, int *words, int *sentences);

int main(void)
{
    int letter = 0, sentences = 0, words = 1;

    count(&letter, &words, &sentences);

    gradeCalculate(letter, words, sentences);

    return 0;
}

/*Esta funcion recibe las punteros de las variable para contar letras, palabras y oraciones,
solicita el texto y procede a contar cada variable*/
void count(int *letter, int *words, int *sentences){

    char text[999];
    printf("Text: ");
    scanf("%[^\n]", text);

    int i = 0;
    do
    {
        if(text[i] == ' ')
        {
            *words += 1;
        }
        else if((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            *letter += 1;
        }
        else if(text[i] == '?' || text[i] == '!' || text[i] == '.')
        {
            *sentences += 1;
        }
        i++;
    }
    while (text[i] != '\0');
}

/*Esta funcion recibe la cantidad de letras, palabras y oraciones, realiza las ecuanciones correspondientes
para obtener el grado y lo imprime, en caso de ser igual o mayor a 16 imprimira "Grade 16+" y de ser menor
a 1 sera "Before Grade 1" delimitando asi los puntajes*/
void gradeCalculate(int letter, int words, int sentences){
    float L, S;
    L = (letter * 100.0) / words;
    S = (sentences * 100.0) / words;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %0.0f\n", index);
    }
}