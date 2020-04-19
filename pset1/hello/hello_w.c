#include <stdio.h>
#include <string.h>


int main (void)

{
    char s[50];
    FILE * input;
    input = fopen("input.txt", "w");
    printf("Hello World!!!\n");
    printf("Is it what you meant?\n");
    printf("Yes or No:");
    scanf("%s", s);
    if (strcmp(s, "Yes")==0)
    {
        fprintf(input, "Good!!!\n");
    }
    else
    {
        fprintf (input, "Oops...\n");
    }

    fscanf (input, "%s", s);

    if (strcmp(s, "Yes")==0)
    {
        printf("You made your  Hello World to file\n");
    }
    fclose(input);
    return 0;
}