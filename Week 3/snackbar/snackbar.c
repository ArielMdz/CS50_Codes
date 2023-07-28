// Practice using structs
// Practice writing a linear search function

/**
 * Beach Burger Shack has the following 10 items on their menu
 * Burger: $9.5
 * Vegan Burger: $11
 * Hot Dog: $5
 * Cheese Dog: $7
 * Fries: $5
 * Cheese Fries: $6
 * Cold Pressed Juice: $7
 * Cold Brew: $3
 * Water: $2
 * Soda: $2
*/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

// Number of menu items
// Adjust this value (10) to number of items input below
#define NUM_ITEMS 10

// Menu itmes have item name and price
typedef struct
{
    char *item;
    float price;
}
menu_item;

// Array of menu items
menu_item menu[NUM_ITEMS];

// Add items to menu
void add_items(void);

// Calculate total cost
float get_cost(char *item);

int main(void)
{
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i]. price);
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        int validation = 0;
        char item[20];
        printf("Enter a food item: ");
        validation = scanf("%[^\n]", item);
        getchar();

        if (validation == 0)
        {
            printf("\n");
            break;
        }

        total += get_cost(item);
        printf("%.2f\n", total);
    }

    printf("Your total cost is: $%.2f\n", total);
}

// Add at least the first for items to the menu array
void add_items(void)
{
    menu[0].item = "Burger";
    menu[0].price = 9.5;

    menu[1].item = "Vegan Burger";
    menu[1].price = 11;

    menu[2].item = "Hot Dog";
    menu[2].price = 5;

    menu[3].item = "Cheese Dog";
    menu[3].price = 7;

    menu[4].item = "Fries";
    menu[4].price = 5;

    menu[5].item = "Cheese Fries";
    menu[5].price = 6;

    menu[6].item = "Cold Pressed Juice";
    menu[6].price = 7;

    menu[7].item = "Cold Brew";
    menu[7].price = 3;

    menu[8].item = "Water";
    menu[8].price = 2;

    menu[9].item = "Soda";
    menu[9].price = 2;
    printf("%c", menu[9].item[0]);

    return;
}

// Search through the menu array to find an item's cost
float get_cost(char *item)
{
    if (item[0] >= 'a' && item[0] <= 'z')
    {
        item[0] = item[0] - 32;
    }

    float price = 0.0;
    int n;
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        n = 0;
        for (int j = 0; j < strlen(item); j++)
        {
            if (menu[i].item[j] == item[j] || menu[i].item[j] == item[j] - 32 || menu[i].item[j] - 32 == item[j])
            {
                n++;
            }
            else
            {
                break;
            }
        }
        if (strlen(menu[i].item) == n)
        {
            price = menu[i].price;
            break;
        }
    }
    return price;
}
