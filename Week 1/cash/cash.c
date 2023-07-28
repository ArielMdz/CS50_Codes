#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int cents;
    int verification = 0;
    /*Inicia ciclo repetitvo para solicitar la cantidad de centavos, en caso de ingresar
    valores negativos o caracteres el ciclo se repetira constantemente hasta ingresar un valor valido*/
    do
    {
        printf("Ingrese cantidad de centavos: ");
        verification = scanf("%i", &cents);
        if(verification != 1){                              //Verifica si se le ingreso un valor entero, en caso de ingresarse un caracter ejecuta la condicion
            int c;
            while ((c = getchar()) != '\n' && c != EOF);       //Mantiene un ciclo para limpiar el buffer
        }
    }
    while(cents <= 0);
    return cents;
}

/*Esta funcion resive el numero de centavos, calcula el valor entero de monedas
de 25 centavos que se necesitan y regresa el valor*/
int calculate_quarters(int cents)
{
    int quarters = cents/25;
    //printf("\nquarters %i\n", quarters);
    return quarters;
}

/*Esta funcion resive el numero de centavos restante, calcula el valor entero de monedas
de 10 centavos que se necesitan y regresa el valor*/
int calculate_dimes(int cents)
{
    int dimes = cents/10;
    //printf("dimes    %i\n", dimes);
    return dimes;
}

/*Esta funcion resive el numero de centavos restante, calcula el valor entero de monedas
de 5 centavos que se necesitan y regresa el valor*/
int calculate_nickels(int cents)
{
    int nickels = cents/5;
    //printf("nickels  %i\n", nickels);
    return nickels;
}

/*Esta funcion resive el numero de centavos restante, calcula el valor entero de monedas
de 1 centavos que se necesitan y regresa el valor*/
int calculate_pennies(int cents)
{
    int pennies = cents/1;
    //printf("pennies  %i\n\n", pennies);
    return pennies;
}
