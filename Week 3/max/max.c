// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n, validation;
    do
    {
        printf("Number of elements: ");
        validation = scanf("%i", &n);
        if (validation != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        printf("Element %i: ", i);
        validation = scanf("%i", &arr[i]);
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }

    printf("The max value is %i.\n", max(arr, n));
}

// TODO: return the max value
int max(int array[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (array[i] > array[i + 1])
        {
            array[i + 1] = array[i];
        }
    }

    return array[n - 1];
}
