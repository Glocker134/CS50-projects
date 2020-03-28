#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// REMEMBER TO USE VALGRIND TO CHECK FOR LEAKS

#define MEM_BLOCK 512

typedef uint8_t BYTE;

// Prototypes
void memoryRead(char *card_file);

int main(int argc, char *argv[])
{
    if (argc == 2 && argv[1])
    {
        memoryRead(argv[1]);
        return 0;
    }
}


void memoryRead(char *card_file)
{
    BYTE buffer[MEM_BLOCK];
    FILE *img = NULL;
    char img_name[8];
    int img_num = 1;

    FILE *card = fopen(card_file, "r");
    if (card == NULL)
    {
        printf("Could not read file %s.\n", card_file);
        return;
    }
    else
    {
        while (fread(&buffer, MEM_BLOCK, 1, card) == 1)
        {
            fread(&buffer, MEM_BLOCK, 1, card);

            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                if (img == NULL)
                {
                    sprintf(img_name, "%03i.jpeg", img_num);
                    img = fopen(img_name, "w");
                }
                else
                {
                    fclose(img);
                    img_num++;
                    sprintf(img_name, "%03i.jpeg", img_num);
                    img = fopen(img_name, "w");
                }

                fwrite(buffer, MEM_BLOCK, 1, img);
            }
        }

        fclose(img);
    }

    fclose(card);
}