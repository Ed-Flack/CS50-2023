#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // User inputs the height the want, only takes between 1 and 8.
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Builds the mario 'pyramid'
    for (int i = 0; i < height; i++)
    {
        // Builds the first half of the mario 'pyramid'
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" "); // This aligns the bricks
        }
        for (int j = 0; j < height - (height - i - 1); j++)
        {
            printf("#"); // This is used to repersent the bricks
        }

        // The middle of the mario 'pyramid'
        printf("  ");

        // Builds the second half of the mario 'pyramid'
        for (int j = 0; j < height - (height - i - 1); j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
