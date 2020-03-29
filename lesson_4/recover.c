// Implement a program called recover that recovers JPEGs from a forensic image.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MEM_BLOCK 512

// Defining an unsigned integer of length 8-bits
typedef uint8_t BYTE;

// Prototypes
void memoryRead(char *card_file);

int main(int argc, char *argv[])
{
    // If a file was passed correctly via CLA
    if (argc == 2 && argv[1])
    {
        memoryRead(argv[1]);
        return 0;
    }

    // Either too many or no arguments were passed
    else if (argc != 2)
    {
        printf("Usage: ./recovery filename.ext\n");
        return 1;
    }
}

void memoryRead(char *card_file)
{
    // Declaring necessary variables
    BYTE buffer[MEM_BLOCK];
    FILE *img;
    char img_name[8];
    int img_num = 0;

    // Opening the card file
    FILE *card = fopen(card_file, "r");

    // If the file does not exist / bad argument received via command line
    if (card == NULL)
    {
        printf("Error - Could not read file %s\n", card_file);
        return;
    }

    // Finding the first jpg header
    while (buffer[0] != 0xff && buffer[1] != 0xd8 && buffer[2] != 0xff && (buffer[3] & 0xf0) != 0xe0)
    {
        fread(buffer, MEM_BLOCK, 1, card);
    }

    // Setting up the first image file
    sprintf(img_name, "%03i.jpg", img_num);
    img = fopen(img_name, "w");
    fwrite(buffer, MEM_BLOCK, 1, img);

    // Checking the card's content until EOF
    while (fread(buffer, MEM_BLOCK, 1, card) == 1)
    {
        // If another jpg header has been found, close the current img file,
        // Update img name by increasing img_num by one,
        // Open new img file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            fclose(img);
            img_num++;
            sprintf(img_name, "%03i.jpg", img_num);
            img = fopen(img_name, "w");
        }
        // Write the data in buffer to img
        fwrite(buffer, MEM_BLOCK, 1, img);
    }

    // Once the EOF has been found, close the currently open img file
    fclose(img);

    return;
}