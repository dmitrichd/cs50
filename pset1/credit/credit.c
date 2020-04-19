#include <stdio.h>

int main(void)
{

long long cc;
long long tempcc=0;
int sum = 0;
int temp = 0;

    do

    {

    printf ("Enter your number:\n");
    scanf ("%lld", &cc);

    }

    while (cc < 0 || cc < 999999999999999 || cc > 9999999999999999);

tempcc = cc;

  while (tempcc >= 1)
    {
        temp = (((tempcc/10) % 10)) * 2;

            if (temp>9)
            {
                temp = ((temp % 10) + 1);
            }

        tempcc = tempcc/100;
        sum = temp + sum;
    }

    tempcc = cc;

    while (tempcc >=1)
    {
        temp = tempcc % 10;
        tempcc = tempcc/100;
        sum = temp + sum;
    }

printf ("Validation number: %i \n", sum);

    if ((sum % 10) == 0 )
    {
        printf ("Your card number is valid!\n");

        if (((cc/1000000000000000) % 10) == 3)
        {
            printf ("Issued by Amex.\n");
        }

        else if (((cc/1000000000000000) % 10) == 4)
        {
            printf ("Issued by VISA.\n");
        }

        else if (((cc/1000000000000000) % 10) == 5)
        {
            printf ("Issued by Master Card.\n");
        }
         else
        {
             printf ("Unknown Bank.\n");
        }


    }

    else
    {
        printf ("Your card number is not valid!\n");
    }

}