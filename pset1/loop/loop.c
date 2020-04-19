#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height, spaces, dashes, lines;

    do
    {
        printf("Height:");
        scanf("%d", &height);
    }
    while (height <= 0 || height >= 23);

    for (lines = 0; lines < height; lines++){

        for (spaces = (height - (lines+2)); spaces >= 0; spaces--)

        {
            printf(" ");
        }

        for (dashes = 1; dashes <= (lines+1); dashes++)

        {
            printf("#");
        }
        printf("\n");
    }
    return 0;

}