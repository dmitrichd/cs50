#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define delay 200000000


int main()
{
    char string[25];
    int counter;


    do
    {
    printf("Enter Your Name:\n");
    scanf("%s", string);
    }
    while (strlen(string)<=0 || strlen(string)>=26);

    for (counter=0; counter<strlen(string); counter++)
    {
        printf("%c  ", string[counter]);

        for (int i=0; i<delay; i++)
        {

        }

    }

        printf("\n");
}