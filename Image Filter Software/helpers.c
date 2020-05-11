#include <math.h>
#include <stdlib.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Assign average of each pixel's RGB to each pixel
    BYTE avg[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg[i][j] = round(((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = avg[i][j];
            image[i][j].rgbtGreen = avg[i][j];
            image[i][j].rgbtRed = avg[i][j];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Shift pixels from Left to Right and vice-versa
    // Use a dynamically allocated temp RGB struct for this
    RGBTRIPLE *temp = malloc(sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int left = 0, right = width - 1; left < right; left++, right--)
        {
            *temp = image[i][left];
            image[i][left] = image[i][right];
            image[i][right] = *temp;
        }
    }
    // Free up dynamically allocated Temp from Heap
    free(temp);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Add values of surrounding pixels, then average to blur
    RGBTRIPLE blur[height][width];
    int blue, green, red;
    int count = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize temp RGB with Current pixel RGB
            // [i][j]: Current Pixel
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;
            red = image[i][j].rgbtRed;
            // Count variable is used to average at the end
            count = 1;

            // [i - 1]: Row above
            if (i - 1 >= 0)
            {
                // [i - 1][j - 1]: Top Left Pixel
                if (j - 1 >= 0)
                {
                    blue += image[i - 1][j - 1].rgbtBlue;
                    green += image[i - 1][j - 1].rgbtGreen;
                    red += image[i - 1][j - 1].rgbtRed;
                    count += 1;
                }
                // [i - 1][j]: Pixel above
                blue += image[i - 1][j].rgbtBlue;
                green += image[i - 1][j].rgbtGreen;
                red += image[i - 1][j].rgbtRed;
                count += 1;
                // [i - 1][j + 1]: Top Right Pixel
                if (j + 1 < width)
                {
                    blue += image[i - 1][j + 1].rgbtBlue;
                    green += image[i - 1][j + 1].rgbtGreen;
                    red += image[i - 1][j + 1].rgbtRed;
                    count += 1;
                }
            }

            // [i]: Current Row
            // [i][j - 1]: Left Pixel
            if (j - 1 >= 0)
            {
                blue += image[i][j - 1].rgbtBlue;
                green += image[i][j - 1].rgbtGreen;
                red += image[i][j - 1].rgbtRed;
                count += 1;
            }
            // [i][j + 1]: Right Pixel
            if (j + 1 < width)
            {
                blue += image[i][j + 1].rgbtBlue;
                green += image[i][j + 1].rgbtGreen;
                red += image[i][j + 1].rgbtRed;
                count += 1;
            }

            // [i + 1]: Row below
            if (i + 1 < height)
            {
                // [i + 1][j - 1]: Bottom Left Pixel
                if (j - 1 >= 0)
                {
                    blue += image[i + 1][j - 1].rgbtBlue;
                    green += image[i + 1][j - 1].rgbtGreen;
                    red += image[i + 1][j - 1].rgbtRed;
                    count += 1;
                }
                // [i + 1][j]: Pixel below
                blue += image[i + 1][j].rgbtBlue;
                green += image[i + 1][j].rgbtGreen;
                red += image[i + 1][j].rgbtRed;
                count += 1;
                // [i + 1][j + 1]: Bottom Right Pixel
                if (j + 1 < width)
                {
                    blue += image[i + 1][j + 1].rgbtBlue;
                    green += image[i + 1][j + 1].rgbtGreen;
                    red += image[i + 1][j + 1].rgbtRed;
                    count += 1;
                }
            }
            blur[i][j].rgbtBlue = round((float) blue / count);
            blur[i][j].rgbtGreen = round((float) green / count);
            blur[i][j].rgbtRed = round((float) red / count);
        }
    }

    // Copy 2D Struct Array "blur" to "image"
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = blur[i][j].rgbtBlue;
            image[i][j].rgbtGreen = blur[i][j].rgbtGreen;
            image[i][j].rgbtRed = blur[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edge[height][width];
    float GxBlue, GxGreen, GxRed;
    float GyBlue, GyGreen, GyRed;
    int *edgeBlue = malloc(sizeof(int));
    int *edgeGreen = malloc(sizeof(int));
    int *edgeRed = malloc(sizeof(int));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // PART 1: Calculate Gx and Gy for RGB in each pixel with the Sobel Kernels Gx, Gy

            // Initialize Gx<color> and Gy<color> to 0 for current pixel
            // [i][j]: Current pixel (Gx 0, Gy 0)
            GxBlue = 0.0;
            GxGreen = 0.0;
            GxRed = 0.0;
            GyBlue = 0.0;
            GyGreen = 0.0;
            GyRed = 0.0;

            // [i - 1]: Row above
            if (i - 1 >= 0)
            {
                // [i - 1][j - 1]: Top Left Pixel: (Gx  - 1, Gy  - 1)
                if (j - 1 >= 0)
                {
                    GxBlue += image[i - 1][j - 1].rgbtBlue *  - 1;
                    GxGreen += image[i - 1][j - 1].rgbtGreen *  - 1;
                    GxRed += image[i - 1][j - 1].rgbtRed *  - 1;
                    GyBlue += image[i - 1][j - 1].rgbtBlue *  - 1;
                    GyGreen += image[i - 1][j - 1].rgbtGreen *  - 1;
                    GyRed += image[i - 1][j - 1].rgbtRed *  - 1;
                }
                // [i - 1][j]: Pixel above (Gx 0, Gy -2)
                // Gx values are multiplied by 0
                GyBlue += image[i - 1][j].rgbtBlue * -2;
                GyGreen += image[i - 1][j].rgbtGreen * -2;
                GyRed += image[i - 1][j].rgbtRed * -2;
                // [i - 1][j + 1]: Top Right Pixel (Gx  + 1, Gy  - 1)
                if (j + 1 < width)
                {
                    GxBlue += image[i - 1][j + 1].rgbtBlue * 1;
                    GxGreen += image[i - 1][j + 1].rgbtGreen * 1;
                    GxRed += image[i - 1][j + 1].rgbtRed * 1;
                    GyBlue += image[i - 1][j + 1].rgbtBlue *  - 1;
                    GyGreen += image[i - 1][j + 1].rgbtGreen *  - 1;
                    GyRed += image[i - 1][j + 1].rgbtRed *  - 1;
                }
            }

            // [i]: Current Row
            // [i][j - 1]: Left Pixel: (Gx -2, Gy 0)
            if (j - 1 >= 0)
            {
                GxBlue += image[i][j - 1].rgbtBlue * -2;
                GxGreen += image[i][j - 1].rgbtGreen * -2;
                GxRed += image[i][j - 1].rgbtRed * -2;
                // Gy values are multiplied by 0
            }
            // [i][j + 1]: Right Pixel: (Gx +2, Gy 0)
            if (j + 1 < width)
            {
                GxBlue += image[i][j + 1].rgbtBlue * 2;
                GxGreen += image[i][j + 1].rgbtGreen * 2;
                GxRed += image[i][j + 1].rgbtRed * 2;
                // Gy values are multiplied by 0
            }

            // [i + 1]: Row below
            if (i + 1 < height)
            {
                // [i + 1][j - 1]: Bottom Left Pixel: (Gx  - 1,  + 1)
                if (j - 1 >= 0)
                {
                    GxBlue += image[i + 1][j - 1].rgbtBlue *  - 1;
                    GxGreen += image[i + 1][j - 1].rgbtGreen *  - 1;
                    GxRed += image[i + 1][j - 1].rgbtRed *  - 1;
                    GyBlue += image[i + 1][j - 1].rgbtBlue * 1;
                    GyGreen += image[i + 1][j - 1].rgbtGreen * 1;
                    GyRed += image[i + 1][j - 1].rgbtRed * 1;
                }
                // [i + 1][j]: Pixel below: (Gx 0, Gy 2)
                // Gx values are multiplied by 0
                GyBlue += image[i + 1][j].rgbtBlue * 2;
                GyGreen += image[i + 1][j].rgbtGreen * 2;
                GyRed += image[i + 1][j].rgbtRed * 2;
                // [i + 1][j + 1]: Bottom Right Pixel: (Gx 1, Gy 1)
                if (j + 1 < width)
                {
                    // All values are multiplied by 1
                    GxBlue += image[i + 1][j + 1].rgbtBlue;
                    GxGreen += image[i + 1][j + 1].rgbtGreen;
                    GxRed += image[i + 1][j + 1].rgbtRed;
                    GyBlue += image[i + 1][j + 1].rgbtBlue;
                    GyGreen += image[i + 1][j + 1].rgbtGreen;
                    GyRed += image[i + 1][j + 1].rgbtRed;
                }
            }

            // PART 2: Calculate each pixel with Sobel algorithm and copy to "edge"

            // Calculate edge using Gx and Gy
            *edgeBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));
            *edgeGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));
            *edgeRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));
            // Cap value at 255 for each R,G,B
            edge[i][j].rgbtBlue = (*edgeBlue < 255) ? *edgeBlue : 255;
            edge[i][j].rgbtGreen = (*edgeGreen < 255) ? *edgeGreen : 255;
            edge[i][j].rgbtRed = (*edgeRed < 255) ? *edgeRed : 255;
        }
    }
    // Free dynamic memory from heap
    free(edgeBlue);
    free(edgeGreen);
    free(edgeRed);

    // Copy "edge" to "image"
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = edge[i][j].rgbtBlue;
            image[i][j].rgbtGreen = edge[i][j].rgbtGreen;
            image[i][j].rgbtRed = edge[i][j].rgbtRed;
        }
    }
    return;
}
