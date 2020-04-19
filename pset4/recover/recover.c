// Recovers jpegs from raw data

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"
#define BUFFER 512

//globals

int filecounter = 0;
char filename[7];
long startfile = 0, endfile = 0;
BYTE *bigArr = NULL;
BYTE *buffer = NULL;


int findJpeg (BYTE *arr, long startposition){

    for (int i = startposition; i < sizeof(arr); i++)
    {
        if (((buffer[i] >> 4 & ((1 << 4) - 1))) == 111100000 &&
            buffer[i - 3] == 0xff && buffer[i - 2] == 0xd8 && buffer[i - 1] == 0xff)
            return i;
    }

    return 0;
}

void writeFile (BYTE *arr, long startpos, long endpos){

    sprintf(filename, "%03d.jpg", filecounter);
    FILE *outptr = fopen(filename, "w");
    if (outptr == NULL)
    {
        fprintf(stderr, "Could not create %s.\n", filename);
    }

    filecounter++;

    char *t_arr = malloc((endpos - startpos) * sizeof(BYTE));

    for (int i = startpos, j = 0; i <= endpos; i++, j++)
        t_arr[j] = arr[i];

    fwrite(&t_arr, sizeof(t_arr), 1, outptr);
    free(t_arr);
    fclose(outptr);

}


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover card.raw\n");
        return 1;
    }

    // open input file
    char *infile = argv[1];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    buffer = (BYTE*) malloc(BUFFER * sizeof(BYTE));
    bigArr = (BYTE*) malloc(BUFFER * sizeof(BYTE));

    //copy file to array
    int j = 0;
    while (fread(buffer, BUFFER, 1, inptr) == 1)
    {

        for(int i = 0; i < BUFFER; i++)
        {
            bigArr[j] = buffer[i];
            j++;
        }

        bigArr = realloc(bigArr, BUFFER * (j + 1) * sizeof(BYTE));

    }

    startfile = findJpeg(bigArr, 0);

    //main loop
    while (endfile < sizeof(bigArr))
    {

        endfile = findJpeg(bigArr, startfile);
        writeFile(bigArr, startfile, endfile);
        startfile = findJpeg(bigArr, endfile);

    }


    return 0;

}