#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <stdio.h>
#include <cs50.h>
#include <unistd.h>

int main(int argc, string argv[])
{

char hash[14] = {0};
char salt[3] = {0};
int count1, count2, count3, count4;


    if (argc!=2 || strlen(argv[1]) < 13)
    {
        printf ("The program must be run with hash as parameter.\n");
        get_string ("Enter anything to quit.\n");
        exit (0);
    }

strcpy (hash, argv[1]);
strncpy (salt, hash, 2);

char pass[5] = {0};
char seed[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\0";

for (count1 = 0; count1 <= strlen(seed); count1++)
    {
        pass[0] = seed[count1];
        if (!strcmp(crypt(pass, salt), hash))
        {
            printf("Cracked!!!\nPassword:  %s", pass);
            break;
        }

        for (count2 = 0; count2 <= strlen(seed); count2++)
        {
            pass[1] = seed[count2];

            if (!strcmp(crypt(pass, salt), hash))
            {
            printf("Cracked!!!\nPassword:  %s", pass);
            break;
            }


            for (count3 = 0; count3 <= strlen(seed); count3++)
            {
                pass[2] = seed[count3];

                if (!strcmp(crypt (pass, salt), hash))
                {
                printf("Cracked!!!\nPassword:  %s", pass);
                break;
                }

                for (count4 = 0; count4 <= strlen(seed); count4++)
                {
                    pass[3] = seed[count4];

                    if (!strcmp(crypt (pass, salt), hash))
                    {
                    printf("Cracked!!!\nPassword:  %s", pass);
                    break;
                    }


                }
            }
        }

    }

return 0;

}
