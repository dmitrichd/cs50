// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4 || atoi(argv[1]) < 1 || atoi(argv[1]) > 100.0)
    {
        fprintf(stderr, "Usage: resize resize_factor_(1-100) infile outfile\n");
        return 1;
    }

    // remember filenames
    int resize = atoi(argv[1]);
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

    //saving infiles width & height
    int prevWidth = bi.biWidth;
    int prevHeight = abs(bi.biHeight);

    //changing headers
    bi.biWidth = resize * bi.biWidth;
    bi.biHeight = resize * bi.biHeight;

    // determine padding for scanlines
    int padding = (4 - (prevWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //changing other headers
    bi.biSizeImage = (sizeof (RGBTRIPLE) * bi.biWidth + newpadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + bf.bfOffBits;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //allocating memory for an array to store extra scanline
    RGBTRIPLE *t_triple = malloc (bi.biWidth * sizeof(RGBTRIPLE));

    if (!t_triple)
    {
        fprintf(stderr, "Could not allocate memory.\n");
        return 5;
    }

    // iterate over infile's scanlines
    for (int i = 0; i < prevHeight; i++)
    {
        //adding counter to fill in the array
        int p = 0;

        // iterate over pixels in scanline
        for (int j = 0; j < prevWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile and array
            for (int k = 1; k <= resize; k++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                t_triple[p] = triple;
                ++p;
            }
        }

        //adding padding after 1st scanline
        for (int z = 0; z < newpadding; z++)
        fputc(0x00, outptr);

        //adding one or more scanlines from array
        for (int v = 1; v < resize; v++)
        {   for (int s = 0; s < bi.biWidth; s++)
                fwrite(&t_triple[s], sizeof(RGBTRIPLE), 1, outptr);

            for (int z = 0; z < newpadding; z++)
            fputc(0x00, outptr);
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

    }

    //free memory for array
    free(t_triple);
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
