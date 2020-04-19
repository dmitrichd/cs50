// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{

    int atoi(); //declare char to integer
    int divident, divisor; // ints to assign duration
    //input = fraction;
    divident = atoi(&fraction[0]);
    divisor = atoi(&fraction[2]);

    return (8/divisor + (divident - 1)); // a formulae to convert everything to 8ths

}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{

    int octave, accid=0, sharpFlat=0, myNote; //compiler sweared accid was not assigned, and sharpFlat must be assigned, otherwise it could
    double frequency, shift;                    //give junk value



    if (strlen(note) == 2)    //if note is not accidental we get note and octave
    {
        octave = atoi(&note[1]);
        myNote = note[0];
    }

    else   //if note is accidental we get note and octave and accident
    {
        myNote= note[0];
        octave = atoi(&note[2]);
        accid = note[1];
    }


   switch (myNote) //assigning note values in hertz

   {    case 'A':
        shift = 440;
        break;
        case 'B':
        shift = 440.00 * pow (2.00, 2.00/12.00);
        break;
        case 'C':
        shift = 440.00 * pow (2.00, -9.00/12.00);
        break;
        case 'D':
        shift =  440.00 * pow (2.00, -7.00/12.00);
        break;
        case 'E':
        shift =  440.00 * pow (2.00, -5.00/12.00);
        break;
        case 'F':
        shift =  440.00 * pow (2.00, -4.00/12.00);
        break;
        case 'G':
        shift =  440.00 * pow (2.00, -2.00/12.00);
        break;
   }

    if (accid == '#') //getting accident #
    sharpFlat = 1;  //if # adding a semitone
    if (accid == 'b') //getting accident b
    sharpFlat = -1; //if b subtracting a semitone

    /* final formulae for frequency including note, octave and accident shifts
       pow(2, n/12) * 440, where n is a shift from A4
       Important to add .0 to numbers, because pow() takes only doubles, otherwise
       might work incorrectly, which was in my case
    */
    frequency = shift * pow(2.00, (sharpFlat + ((octave - 4.00) * 12.00))/12.00);

        // using round to get nearest integer value for frequency
    return round(frequency);

}

// Determines whether a string represents a rest
bool is_rest(string s)
{

   if (strcmp(s, "") == 0) // if string is empty (note missing) returns 1
   return 1;
   else
   return 0; //otherwise 0

}
