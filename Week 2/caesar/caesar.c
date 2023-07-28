/*Este programa codifica textos, recibe solo un argumento por linea de comandos el cual debe
ser numerico, de lo contrario regresara un error, dicho valor numerico sera el que recorra las
letras del abecedario para codificarlo, comoo ejemplo si el argumento es 1 entonces todas las
letras de la palabra seran desplazadas A -> B, B -> C ... Z -> A, las letras mayusculas y minusculas
son respetadas siendo remplazadas conservando esta caracteristica.*/

#include <stdio.h>
#include <stdlib.h>

void encrypt(int key);

/*La funcion principal se encarga de recibir los argumentos y evaluarlos para asegurarse que la cantidad de
argumentos y su contenido sea aceptable, de lo contrario regresara un error y retornara 1, en caso de ser
aceptables llamara a una funcion que codificara la palabra y retornara 0 al finalizar la ejecucion*/
int main(int argc, char* argv[])
{
    int key;
    if (argc == 2)
    {
        int i = 0;
        key = atoi(argv[1]);
        do
        {
            if (argv[1][i] > '9' || argv[1][i] < '0'){
                printf("Error: argument non-numeric key\n");
                return 1;
            }
            i++;
        }
        while (argv[1][i] != '\0');
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    encrypt(key);

    return 0;
}

/*Esta funcion recibe un una variable de valor entero que servira para codificar una palabra,
solicita la palabra o frase y posteriormente remplaza cada letra por una letra distinta segun el
valor entero dado respetando mayusculas o minusculas.*/
void encrypt(int key)
{
    char text[100];
    printf("plaintext:  ");
    scanf("%[^\n]", text);

    int i = 0, k;
    do
    {
        k = key;

        if (text[i] >= 'A' && 'Z' >= text[i] )          //Si la letra es mayuscula debera ejecutar esta funcion para ser remplazada por mayusculas
        {
            while ((k + text[i]) > 'Z')                 //Considerando ASCII el valor de la variable k suma a la pocision de la letra de la palabra y lo compara
            {                                           //en dado caso de superar el limite de 'Z' se restara 26 a k y se comparara de nuevo hasta que la suma
                k -= 26;                                //no logre superar a 'Z', es decir que el resultado este dentro de las letras mayusculas en ASCII
            }
            text[i] = text[i] + k;                      //La letra es remplazada por una letra recorrida una cantidad k en el alfabeto
        }
        else if (text[i] >= 'a' && 'z' >= text[i])      //Si la letra es minuscula se repite la logica esta vez utilizando letras minusculas
        {
            while ((k + text[i]) > 'z')
            {
                k -= 26;
            }
            text[i] = text[i] + k;
        }
        i++;
    }
    while(text[i] != '\0');                             //Una vez se llegue al final del arreglo el ciclo termina

    printf("ciphertext:  %s\n", text);                  //Imprime texto codificado
}