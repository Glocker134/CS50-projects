#include <cs50.h>
#include <stdio.h>

void draw(int n);

int main(void)
{
    int input;
    do 
    {
        input = get_int("Height: ");
    }
    while (input < 1 || input > 8);
    draw(input);
}

void draw(int n) 
{
    if (n == 1)
    {
        printf("#\n");
    }
    else 
    {
        int count = n - 1;
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < n; j++) 
            {
                if (j < count)
                { 
                    printf(" ");
                }
                else
                { 
                    printf("#");
                }
            }
            printf("\n");
            count--;
        }
    }
}
