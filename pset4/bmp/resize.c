/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize infile outfile\n");
        return 1;
    }
    
    // remember zoom and check for proper value
    float zoom = atof(argv[1]);
    if (zoom <= 0.0 || zoom > 100.0)
    {
        printf("zoom, the resize factor, must satisfy 0 < zoom <= 100.\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
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
    
    // remember infile's width and height
    int current_width = bi.biWidth;
    int current_height = abs(bi.biHeight);
    
    // change width and height for outfile's
    bi.biWidth *= zoom;
    bi.biHeight *= zoom;
    
    // determine padding for scanlines in infile's
    int current_padding =  (4 - (current_width * sizeof(RGBTRIPLE)) % 4) % 4;
    // determine padding for scanlines in outfile's
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine sizes of the image and file in outfile's
    bi.biSizeImage = abs(bi.biHeight) * ((bi.biWidth * sizeof(RGBTRIPLE)) + padding);
    bf.bfSize = bi.biSizeImage + sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < current_height; i++)
    {
        // read each scanline zoom times
        for (int k = 0; k < zoom; k++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < current_width; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // write RGB triple to outfile, zoom times
                for (int n = 0; n < zoom; n++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
    
            // add padding to outfile's
            for (int l = 0; l < padding; l++)
            {
                fputc(0x00, outptr);
            }
            
            // return to the begining of scanline
            if (k < zoom - 1)
            {
                fseek(inptr, -current_width * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }
        
        // skip over padding, if any
        fseek(inptr, current_padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
