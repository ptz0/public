/*
        hexdat
        by ptz0
        v 1.0
        dated 21/02/16
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void usage()
{
	printf("\n");
	printf("Usage: hexdat FILE\n");
	printf("\nDisplays file in hexadecimal format, in rows of 5");
	printf("\nAbsolute path required if file not in current working directory.\n");
	printf("\n");
}

int main(int argc, char **argv)
{
	char filepath[256];
	unsigned char hex[1024] = "";
	int each = 0;
	size_t bytes = 0;

	FILE *fp;

	if(argc < 2)
	{
		usage();
		exit(-1);
	}
	else
	{
		strcpy(filepath, argv[1]);		
	}

	printf("File: %s\n", filepath);
	
	fp = fopen(filepath, "r");
	
	if(fp == NULL)
	{
		printf("\nError trying to hex dat bitch, %s.\n", filepath);
		exit(-1);
	}

	int rc = 0;				// row count
	int hc = 0;				// hex count

	printf("\t");
	while ((bytes = fread ( &hex, 1, 1024, fp)) > 0) 
	{
        	for (each = 0; each < bytes; each++) 
		{	
			if(rc == 10)
			{
				printf("\n");
				rc = 0;
			}
			if(hc == 2)
			{
				printf("\t");
				hc = 0;
			}	
			printf("%x", hex[each]);
			hc++;
			rc++;
        	}
    	}

	fclose(fp);
	printf("\n");
	return 0;
}
