#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: whodunit infile outfile.\n");
    }

    char *inFile = argv[1];
    char *outFile = argv[2];

    FILE *inPtr = fopen(inFile, "r");
    if (!inPtr)
    {
        fprintf(stderr, "Could not open %s.\n", inFile);
        return 2;
    }

    FILE *outPtr = fopen(outFile, "w");
    if (outPtr == 0)
    {
        fprintf(stderr, "Could not open %s.\n", outFile);
        fclose(inPtr);
        return 3;
    }

    BITMAPFILEHEADER bmpFh;
    fread(&bmpFh, sizeof(BITMAPFILEHEADER), 1, inPtr);

    BITMAPINFOHEADER bmpInf;
    fread(&bmpInf, sizeof(BITMAPINFOHEADER), 1, inPtr);

    if (bmpFh.bfType != 0x4d42 || bmpFh.bfOffBits != 54 || bmpInf.biSize != 40 ||
        bmpInf.biBitCount != 24 || bmpInf.biCompression != 0)
    {
        fclose(outPtr);
        fclose(inPtr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    fwrite(&bmpFh, sizeof(BITMAPFILEHEADER), 1, outPtr);

    fwrite(&bmpInf, sizeof(BITMAPINFOHEADER), 1, outPtr);


    int padding = (4 - (bmpInf.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; //WTF is THAT??????

    for (int i = 0, biHeight = abs(bmpInf.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bmpInf.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE rgbColor;

            // read RGB triple from infile
            fread(&rgbColor, sizeof(RGBTRIPLE), 1, inPtr);
            if (rgbColor.rgbtBlue == 0 && rgbColor.rgbtGreen == 0 && rgbColor.rgbtRed == 255)
            rgbColor.rgbtRed = 0;

            if (rgbColor.rgbtBlue == 255 && rgbColor.rgbtGreen == 255 && rgbColor.rgbtRed == 255)
            rgbColor.rgbtRed = 0; rgbColor.rgbtBlue = 0; rgbColor.rgbtGreen = 0;

            //if (rgbColor.rgbtBlue != 0 || rgbColor.rgbtGreen != 0 || rgbColor.rgbtRed != 0) // just for fun
            //rgbColor.rgbtRed = 150; rgbColor.rgbtBlue = 10; rgbColor.rgbtGreen = 250;       //playing with colors

            // write RGB triple to outfile
            fwrite(&rgbColor, sizeof(RGBTRIPLE), 1, outPtr);
        }
    }

    fseek(inPtr, padding, SEEK_CUR);

    fclose (inPtr);
    fclose (outPtr);


    return 0;
}