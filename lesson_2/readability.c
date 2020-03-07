#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    int wordCount = 0;
    int sentenceCount = 0;
    int letterCount = 0;
    int index;
    float letterAvg, sentenceAvg;
    char dotChar = '.';
    char questChar = '?';
    char exclChar = '!';

    string text = get_string("Text: ");

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letterCount++;
        }

        if (text[i] == dotChar || text[i] == questChar || text[i] == exclChar)
        {
            sentenceCount++;
        }

        if (isspace(text[i]) || iscntrl(text[i + 1]))
        {
            wordCount++;
        }
    }

    letterAvg = round(letterCount * 100) / wordCount;
    sentenceAvg = round(sentenceCount * 100) / wordCount;

    index = round((0.0588 * letterAvg) - (0.296 * sentenceAvg) - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}