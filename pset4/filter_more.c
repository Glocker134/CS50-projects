// Implement the functions in helpers.c such that a user can apply grayscale, reflection, blur,
// or edge detection filters to their images.

#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Average between red, green, blue, and divided by 3. Each color channel will have the same avg value.
    // Round to the nearest integer!!

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            avg /= 3;
            image[i][j].rgbtRed = (int) round(avg);
            image[i][j].rgbtGreen = (int) round(avg);
            image[i][j].rgbtBlue = (int) round(avg);
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
    //
    // Corners:
    // if ((i == 0 && j == 0) || (i == 0 && j == width - 1) || (i == height - 1 && j == 0) || (i == height - 1 && j == width - 1)
    //
    // Sides:
    // if (i == 0 || i == height - 1 || j == 0 || j == width - 1)

    RGBTRIPLE auximage[height][width];
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            auximage[a][b] = image[a][b];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avgRed = 0;
            float avgGreen = 0;
            float avgBlue = 0;

            // Corners in general - 4 pixels total
            if ((i == 0 && j == 0) || (i == 0 && j == width - 1) || (i == height - 1 && j == 0) ||
                (i == height - 1 && j == width - 1))
            {
                // Specific corners
                // Top left
                if (i == 0 && j == 0)
                {
                    for (int k = i; k < i + 2; k++)
                    {
                        for (int m = j; m < j + 2; m++)
                        {
                            avgRed += auximage[k][m].rgbtRed;
                            avgGreen += auximage[k][m].rgbtGreen;
                            avgBlue += auximage[k][m].rgbtBlue;
                        }

                    }
                }

                // Top right
                else if (i == 0 && j == width - 1)
                {
                    for (int k = i; k < i + 2; k++)
                    {
                        for (int m = j - 1; m < width; m++)
                        {
                            avgRed += auximage[k][m].rgbtRed;
                            avgGreen += auximage[k][m].rgbtGreen;
                            avgBlue += auximage[k][m].rgbtBlue;
                        }

                    }
                }

                // Bottom left
                else if (i == height - 1 && j == 0)
                {
                    for (int k = i - 1; k < height; k++)
                    {
                        for (int m = j; m < j + 2; m++)
                        {
                            avgRed += auximage[k][m].rgbtRed;
                            avgGreen += auximage[k][m].rgbtGreen;
                            avgBlue += auximage[k][m].rgbtBlue;
                        }

                    }
                }

                // Bottom right
                else if (i == height - 1 && j == width - 1)
                {
                    for (int k = i - 1; k < height; k++)
                    {
                        for (int m = j - 1; m < width; m++)
                        {
                            avgRed += auximage[k][m].rgbtRed;
                            avgGreen += auximage[k][m].rgbtGreen;
                            avgBlue += auximage[k][m].rgbtBlue;
                        }
                    }
                }

                avgRed = round(avgRed / 4);
                avgGreen = round(avgGreen / 4);
                avgBlue = round(avgBlue / 4);
            }

            // Borders - 6 pixels total
            else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                // Top border
                if (i == 0)
                {
                    for (int k = i; k < i + 2; k++)
                    {
                        for (int m = j - 1; m < j + 2; m++)
                        {
                            avgRed += auximage[k][m].rgbtRed;
                            avgGreen += auximage[k][m].rgbtGreen;
                            avgBlue += auximage[k][m].rgbtBlue;
                        }

                    }
                }

                // Bottom border
                else if (i == height - 1)
                {
                    for (int k = i - 1; k < height; k++)
                    {
                        for (int m = j - 1; m < j + 2; m++)
                        {
                            avgRed += auximage[k][m].rgbtRed;
                            avgGreen += auximage[k][m].rgbtGreen;
                            avgBlue += auximage[k][m].rgbtBlue;
                        }

                    }
                }

                // Left border
                else if (j == 0)
                {
                    for (int k = i - 1; k < i + 2; k++)
                    {
                        for (int m = j; m < j + 2; m++)
                        {
                            avgRed += auximage[k][m].rgbtRed;
                            avgGreen += auximage[k][m].rgbtGreen;
                            avgBlue += auximage[k][m].rgbtBlue;
                        }

                    }
                }

                // Right border
                else if (j == width - 1)
                {
                    for (int k = i - 1; k < i + 2; k++)
                    {
                        for (int m = j - 1; m < width; m++)
                        {
                            avgRed += auximage[k][m].rgbtRed;
                            avgGreen += auximage[k][m].rgbtGreen;
                            avgBlue += auximage[k][m].rgbtBlue;
                        }

                    }
                }

                avgRed = round(avgRed / 6);
                avgGreen = round(avgGreen / 6);
                avgBlue = round(avgBlue / 6);
            }

            // The pixel is not part of the borders - 9 pixels total
            else
            {
                for (int k = i - 1; k < i + 2; k++)
                {
                    for (int m = j - 1; m < j + 2; m++)
                    {
                        avgRed += auximage[k][m].rgbtRed;
                        avgGreen += auximage[k][m].rgbtGreen;
                        avgBlue += auximage[k][m].rgbtBlue;
                    }

                }

                avgRed = round(avgRed / 9);
                avgGreen = round(avgGreen / 9);
                avgBlue = round(avgBlue / 9);

            }

            image[i][j].rgbtRed = (int) avgRed;
            image[i][j].rgbtGreen = (int) avgGreen;
            image[i][j].rgbtBlue = (int) avgBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Creating a copy of the image for math purposes
    RGBTRIPLE auximage[height + 2][width + 2];

    int gx_red, gx_green, gx_blue, gy_red, gy_green, gy_blue;

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int a = 0; a < height + 2; a++)
    {
        for (int b = 0; b < width + 2; b++)
        {
            // Adding a black border to the aux image
            if (a == 0 || b == 0 || a == height + 1 || b == width + 1)
            {
                auximage[a][b].rgbtRed = 0;
                auximage[a][b].rgbtGreen = 0;
                auximage[a][b].rgbtBlue = 0;
            }

            // Else fill with the original image data
            else
            {
                auximage[a][b] = image[a - 1][b - 1];
            }
        }
    }

    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {

            // Initializing Gx and Gy values
            gx_red = 0;
            gx_green = 0;
            gx_blue = 0;

            gy_red = 0;
            gy_green = 0;
            gy_blue = 0;

            for (int k = i - 1; k < i + 2; k++)
            {
                for (int m = j - 1; m < j + 2; m++)
                {
                    int k_key = i - k + 1;
                    int m_key = m - j + 1;

                    // Increasing the value of each Gx and Gy variable according to the pixel RGB value
                    // And their respective Gx/Gy multiplier

                    gx_red += auximage[k][m].rgbtRed * gx[k_key][m_key];
                    gx_green += auximage[k][m].rgbtGreen * gx[k_key][m_key];
                    gx_blue += auximage[k][m].rgbtBlue * gx[k_key][m_key];

                    gy_red += auximage[k][m].rgbtRed * gy[k_key][m_key];
                    gy_green += auximage[k][m].rgbtGreen * gy[k_key][m_key];
                    gy_blue += auximage[k][m].rgbtBlue * gy[k_key][m_key];
                }
            }

            // Calculating the theta of the red, green, and blue channels
            double thetaRed = pow(gx_red, 2.0) + pow(gy_red, 2.0);
            thetaRed = round(sqrt(thetaRed));
            if (thetaRed > 255)
            {
                thetaRed = 255;
            }

            double thetaGreen = pow(gx_green, 2.0) + pow(gy_green, 2.0);
            thetaGreen = round(sqrt(thetaGreen));
            if (thetaGreen > 255)
            {
                thetaGreen = 255;
            }

            double thetaBlue = pow(gx_blue, 2.0) + pow(gy_blue, 2.0);
            thetaBlue = round(sqrt(thetaBlue));
            if (thetaBlue > 255)
            {
                thetaBlue = 255;
            }

            // Updating the image
            image[i - 1][j - 1].rgbtRed = (int) thetaRed;
            image[i - 1][j - 1].rgbtGreen = (int) thetaGreen;
            image[i - 1][j - 1].rgbtBlue = (int) thetaBlue;
        }
    }

    return;
}