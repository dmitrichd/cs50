#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, string argv[])
{

int shift, counter;
string inputString;

    if (argc != 2 || (atoi (argv[1]))<=0) //check if program runs with a parameter (one only) and if
    {                                     // a parameter is a positive decimal key
    printf ("This program needs one positive decimal parameter for cypher key!\n");
    printf ("Enter any key to exit...\n");
    scanf ("%i", &argc);
    exit(0);
    }

shift = atoi (argv[1]); // getting shift key from program parameter
inputString = get_string ("Enter your string to encode:\n"); //getting input string

printf ("Your encoded string is:  \n");

    for (counter = 0; counter < strlen (inputString); counter++) //checking all letters in a string
    {
        if (isupper(inputString[counter]))                       //either uppercase
        printf("%c", (((inputString[counter] + shift) - 65) % 26) + 65); // convert to upper
        else if (islower(inputString[counter]))                         //either lowercase
        printf("%c", (((inputString[counter] + shift) - 97) % 26) + 97);  // to lower
        else
        printf ("%c", inputString[counter]); //leave anything else untouched
    }

printf ("\n");

}