#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    char text[100];
    printf("Message: ");
    scanf("%[^\n]", text);

    int i = 0, bit[8];
    while (text[i] != '\0')
    {
        bit[0] = text[i];
        for (int j = 1; j < BITS_IN_BYTE; j++)
        {
            bit[j] = bit[j - 1] / 2;
        }
        for (int j = 7; j >= 0; j--)
        {
            print_bulb(bit[j] % 2);
        }
        printf("\n");
        i++;
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
