// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>

bool valid(char* password);

int main(void)
{
    char password[20];
    printf("Enter your password: ");
    scanf("%s", password);

    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(char* password)
{
    bool mayus = false, minus = false, symbol = false, num = false;
    int i = 0;
    while(password[i] != '\0')
    {
        if (password[i] >= 'A' && password[i] <= 'Z')
        {
            mayus = true;
        }
        else if (password[i] >= 'a' && password[i] <= 'z')
        {
            minus = true;
        }
        else if (password[i] >= '0' && password[i] <= '9')
        {
            num = true;
        }
        else
        {
            symbol = true;
        }
        i++;
    }
    if (mayus && minus && num && symbol)
    {
        return true;
    }
    return false;
}
