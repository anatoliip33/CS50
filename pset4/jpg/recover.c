/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BLOCKSIZE 512

int main(int argc, char *agrv[])
{
	// open memory card
	FILE* card_file = fopen("card.raw", "r");
	
	// check if file exist
	if (card_file == NULL)
	{
		printf("Could not open file\n");
		return 1;		
	}
	
	uint8_t buf[512];
	
	// output file
	FILE *outerfile = NULL;
	
	// variable to name recover jpg files
	int name_count = 0;
	
	while(fread(buf, BLOCKSIZE, 1, card_file))
	{
		// check first four bytes for JPEG signature
		if (buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff
		&& (buf[3] == 0xe0 || buf[3] == 0xe1))
		{
			// if already exist, then close file
			if (outerfile != NULL)
			{
				fclose(outerfile);
			}
			
			char filename[8];
			
			sprintf(filename, "%03d.jpg", name_count);
			
			// new JPEG file for writing
			outerfile = fopen(filename, "w");
			
			name_count++;
		}
		
		if (outerfile != NULL)
		{
			fwrite(buf, BLOCKSIZE, 1, outerfile);
		}
	}
	
	if (outerfile != NULL)
	{
		fclose(outerfile);
	}
	
	fclose(card_file);
	
	return 0;
}
