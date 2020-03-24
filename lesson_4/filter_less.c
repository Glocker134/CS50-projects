#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Average between red, green, blue, and divided by 3. Each color channel will have the same avg value.
    // Round to the nearest integer!!

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue
    // sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    // sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    // If the value is higher than 255, default to white (all 255)
    // Round to the nearest integer!!

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            int sepiaGreen = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            int sepiaBlue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Move pixel from top left to top right and so on

    for (int i = 0; i < height; i++)
    {
        int j = 0;
        int k = width - 1;

        while (j < k && j != k)
        {
            // Saving values of right-side pixel in auxiliary variables
            int tempRed = image[i][k].rgbtRed;
            int tempGreen = image[i][k].rgbtGreen;
            int tempBlue = image[i][k].rgbtBlue;

            // Moving the left-side pixel to the right
            image[i][k].rgbtRed = image[i][j].rgbtRed;
            image[i][k].rgbtGreen = image[i][j].rgbtGreen;
            image[i][k].rgbtBlue = image[i][j].rgbtBlue;

            // Moving the stored right-side pixel to the left
            image[i][j].rgbtRed = tempRed;
            image[i][j].rgbtGreen = tempGreen;
            image[i][j].rgbtBlue = tempBlue;

            // Increasing counters
            j++;
            k--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // The box blur effect is based on averaging the color value of neighboring pixels.
    // Each pixel should be surrounded by up to 8 other pixels, aside corners and borders.
    //
    // So, for a 3x3 grid, the color value for pixel 5 would be the average of red, green, and blue
    // of all the pixels, so 1, 2, 3, 4, 5, 6, 7, 8, and 9. Yes, including the pixel itself.
    // In the case of 1, 3, 7, and 9, there are only 3 neighboring pixels plus itself for a total of 4.
    // In the case of 2, 4, 6, and 8, there are only 5 neighboring pixels plus itself for a total of 6.

    // Corners:
    // if ((i == 0 && j == 0) || (i == 0 && j == width - 1) || (i == height - 1 && j == 0) || (i == height - 1 && j == width - 1)

    // Sides:
    // if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
    return;
}
