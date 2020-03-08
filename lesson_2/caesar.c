#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int cipher(int);

int main(int argc, string argv[])
{
    if (argv[1] && (atoi(argv[1]) > 0))
    {
        // Validate if it's a number
        // Validate if the number doesn't have whitespaces (PENDING)
        for (int i = 0; i < strlen(argv[1]); i++)
        int key = atoi(argv[1]);
        cipher(key);
    }
    else
    {
        printf("Usage: ./caesar key.\n");
    }
}

int cipher(int key)
{
    printf("this is cipher. Do stuff here\n");
    return 0;
}