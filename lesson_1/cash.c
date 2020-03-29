// Implement, in cash.c at right, a program that first asks the user how much change is owed 
// And then prints the minimum number of coins with which that change can be made.

#include <math.h>
#include <stdio.h>
#include <cs50.h>

void change(void);

int main(void) 
{
    change();    
}

void change(void)
{
    const int penny = 1;
    const int nickel = 5;
    const int dime = 10;
    const int quarter = 25;
    int coins = 0;
    float input;
    do
    {
        input = get_float("Change owed: ");
    }
    while (input < 0);
    int fixed = round(input * 100);
    while (fixed > 0)
    {
        if (fixed / quarter > 0)
        {
            fixed -= quarter;
            coins++;
        }
        else if (fixed / dime > 0)
        {
            fixed -= dime;
            coins++;
        }
        else if (fixed / nickel > 0)
        {
            fixed -= nickel;
            coins++;
        }
        else if (fixed / penny > 0)
        {
            fixed -= penny;
            coins++;
        }
    }
    printf("%i\n", coins);
}

/*
const int penny = 1;
const int nickel = 5;
const int dime = 10;
const int quarter = 25;
*/
