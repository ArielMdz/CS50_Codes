// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value
/*Para este codifo debia ser realizada la funcion half para que calculara el total a pagar de una cuenta
en base a los valores proportcionados los cuales son monto a pagar, porcetaje de impuesto y porcentaje de propina*/

#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

/*Esta funcion calcula y regresa el monto total a pagar, en base al monto debera ser sumado los impuestos
y en base al costo con impuestos a;adidos debera agregarse el porcentaje de propina*/
float half(float bill, float tax, int tip)
{
    float pay;
    pay = ((bill + (1 + tax/100)) * (tip + 100))/200;
    return pay;
}
