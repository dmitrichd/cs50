#include <stdio.h>
#include <cs50.h>

# define  QUARTER 0.25
# define DIME 0.1        // Defining coins
# define NICKEL 0.05
# define PENNY 0.01

float change; //input value

int quarter;
int dime;      // counters for coins
int nickel;
int penny;


int main (void)

{

    do
    {
       change = get_float ("Enter due change:");
    }
    while (change<0.001 || change>1.0); //makes shure change exists (range between a penny and 99 pennies)


    for (quarter=0; (change-QUARTER)>=0; quarter++)
    {
        change = change - QUARTER;                    // counting quarters
    }

    for (dime=0; (change-DIME)>=0; dime++)
    {
        change = change - DIME;                        // counting dimes
    }

    for (nickel=0; (change-NICKEL)>=0; nickel++)
    {
        change = change - NICKEL;                       // counting nickels
    }

    for (penny=0; ((change+0.005)-PENNY)>=0; penny++)
    {
        change = change - PENNY;                        // counting pennies
    }


    printf ("Change consists of %i quarters, %i dimes, %i nickels, %i pennies.\n", quarter, dime, nickel, penny);
    printf ("All in all %i coins.\n", quarter+dime+nickel+penny);

}