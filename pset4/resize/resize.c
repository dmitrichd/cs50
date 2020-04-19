// Resizes a BMP file with a factor of 0.01 to 100.0

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4 || atof(argv[1]) < 0.0 || atof(argv[1]) > 100.0)
    {
        fprintf(stderr, "Usage: resize resize_factor_(1.0-100.0) infile outfile\n");
        return 1;
    }

    //round the resize to two digits after point
    float resize = floor(atof(argv[1]) * 100 + 0.5) / 100;
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);


    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //get padding for infile
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //create a 2D array to store infile
    RGBTRIPLE in_arr[abs(bi.biHeight)][bi.biWidth];

    //copy the infile into array
    for (int i = 0; i < abs(bi.biHeight); i++)
    {
        for (int j = 0; j < bi.biWidth; j++)
        {

            RGBTRIPLE triple;
            fread (&triple, sizeof(RGBTRIPLE), 1, inptr);
            in_arr[i][j] = triple;
        }
        //skeep padding
        fseek (inptr, padding, SEEK_CUR);
    }

    //refresh outfile headers
    bi.biWidth = resize * bi.biWidth;
    bi.biHeight = resize * bi.biHeight;

    //get patting for outfile
    padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //refresh more headers
    bi.biSizeImage = (sizeof (RGBTRIPLE) * bi.biWidth + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + bf.bfOffBits;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //write an array to outfile
    for (int i = 0; i < abs(bi.biHeight); i++)
    {

        for (int j = 0; j < bi.biWidth; j++)
        {

            RGBTRIPLE triple;
            //taking pixels depending on resize factor
            triple = in_arr[(int) (i/resize)][(int) (j/resize)];
            fwrite(&triple, sizeof (RGBTRIPLE), 1, outptr);
        }

        for (int z = 0; z < padding; z++)
        fputc(0x00, outptr);

    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
