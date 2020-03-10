#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int validate(string);
int substitution(string);
int indexOf(char);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        switch (validate(argv[1]))
        {
            // Key exists and it passes validation
            case 1:
                substitution(argv[1]);
                return 0;
                break;

            // Key exists, but doesn't have exactly 26 characters
            case 2:
                printf("Key must contain 26 characters.\n");
                return 1;
                break;

            // Key exists, but it contains non-alphabetic characters
            default:
                printf("Usage: ./substitution key.\n");
                return 1;
        }
    }
    else
    {
        // Key doesn't exist, or more than one argument was passed via command line
        printf("Usage: ./substitution key.\n");
        return 1;
    }
}

int substitution(string key)
{
    char lowKey[strlen(key)];

    for (int i = 0; i < strlen(key); i++)
    {
        lowKey[i] = tolower(key[i]);
    }

    string input = get_string("plaintext: ");
    char output[strlen(input)];
    char aux;
    int indexAux;

    for (int i = 0; i < strlen(input); i++)
    {
        int caps = 0;
        if (isalpha(input[i]))
        {
            aux = tolower(input[i]);
            if (aux != input[i])
            {
                caps = 1;
            }
            indexAux = indexOf(aux);
            aux = lowKey[indexAux];

            if (caps == 1)
            {
                aux = toupper(aux);
            }
            output[i] = aux;
        }
        else
        {
            output[i] = input[i];
        }


    }
    output[strlen(input)] = '\0';
    printf("ciphertext: %s\n", output);
    return 0;
}

int indexOf(char letter)
{
    string sample = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < strlen(sample); i++)
    {
        if (letter == sample[i])
        {
            return i;
        }
    }
    return -1;
}

int validate(string key)
{
    // If key has 26 characters to map for the substitution
    if (strlen(key) == 26)
    {
        for (int i = 0; i < strlen(key); i++)
        {
            // If the key contains non-alphabetic characters, return 0 for the switch
            if (!(isalpha(key[i])))
            {
                return 0;
            }

            else if (i < strlen(key) - 1)
            {
                // Checking for duplicate values in the key.
                // If one is found, return 0 for the switch
                for (int j = i + 1; j < strlen(key); j++)
                {
                    if (key[i] == key[j])
                    {
                        return 0;
                    }
                }
            }
        }
        // The key contains 26 alphabetic characters, return 1 for the switch
        return 1;
    }
    else
    {
        // The key doesn't have 26 characters, return 2 for the switch
        return 2;
    }
}