// Receive the user's name and then print it on screen

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What is your name? ");
    printf("hello, %s\n", name);
}
