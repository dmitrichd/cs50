#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, string argv[])
{

int counter, loop;
string inputString, key;

    if (argc != 2 || strlen(argv[1])<5) //check if program runs with a parameter (one only) and if
    {                                     // a parameter is a string at least 5 symbols long
    printf ("This program needs one parameter for cypher key at least 5 symbols long!\n");
    printf ("Enter any key to exit...\n");
    scanf ("%i", &argc);
    exit(0);
    }

key = argv[1];
inputString = get_string ("Enter your string to encode:\n"); //getting input string
loop=0;

printf ("\nYour encoded string is:  \n");

    for (counter = 0; counter < strlen (inputString); counter++) //checking all letters in a string
    {


            if (isupper(inputString[counter]))                       //either uppercase
            printf("%c", (((inputString[counter] + key[loop]) - 65) % 26) + 65); // convert to upper
            else if (islower(inputString[counter]))                         //either lowercase
            printf("%c", (((inputString[counter] + key[loop]) - 97) % 26) + 97);  // to lower
            else
            printf ("%c", inputString[counter]); //leave anything else untouched

            if (loop < strlen (key))
            loop++;
            else
            loop = 0;

    }

printf ("\n");

}