#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks;

    printf("Number of weeks taking CS50: ");
    scanf("%i", &weeks);

    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        printf("Week %i HW Hours: ", i);
        scanf("%i", &hours[i]);
    }

    char output;
    do
    {
        printf("Enter T for total hours, A for average hours per week: ");
        scanf("%c", &output);
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

float calc_hours(int hours[], int weeks, char output)
{
    float sumHours = 0.0;
    if (output == 'T')
    {
        for (int i = 0; i < weeks; i++)
        {
            sumHours += hours[i];
        }
    }
    else
    {
        for (int i = 0; i < weeks; i++)
        {
            sumHours += hours[i];
        }
        sumHours = sumHours / weeks;
    }

    return sumHours;
}