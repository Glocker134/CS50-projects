#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int validate(string);
int cipher(int);

int main(int argc, string argv[])
{
    if (argc == 2 && validate(argv[1]))
    {
        int key = atoi(argv[1]);
        cipher(key);
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key.\n");
        return 1;
    }
}

int cipher(int key)
{
    string input = get_string("plaintext: ");

    if (key % 26 == 0)
    {
        printf("ciphertext: %s\n", input);
    }
    else
    {
        char output[strlen(input)];
        char aux;

        if (key > 26)
        {
            // Changing key to a value between 1 and 25:
            key = key % 26;
        }
        for (int i = 0; i < strlen(input); i++)
        {
            int caps = 0;

            // Checking if the character is a whitespace or punctuation character
            if (isalpha(input[i]))
            {
                aux = tolower(input[i]);
                // Checking if the original character is uppercase
                if (aux != input[i])
                {
                    caps = 1;
                }

                // Checking if the cipher goes beyond z
                if (aux + key > 122)
                {
                    int posAux = (aux + key - 26);
                    aux = posAux;
                }
                else
                {
                    aux += key;
                }

                // Reverting the caps check
                if (caps == 1)
                {
                    aux = toupper(aux);
                    output[i] = aux;
                }
                else
                {
                    output[i] = aux;
                }
            }
            else
            {
                output[i] = input[i];
            }
        }
        
        // Adding a null at the end of output
        output[strlen(input)] = '\0';
        printf("ciphertext: %s\n", output);
    }
    return 0;
}

int validate(string key)
{
    if (atoi(key) > 0)
    {
        for (int i = 0; i < strlen(key); i++)
        {
            if (!(isdigit(key[i])))
            {
                return 0;
            }
        }

        return 1;
    }
    else
    {
        return 0;
    }
}