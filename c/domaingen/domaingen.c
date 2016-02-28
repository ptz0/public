/*
        domaingen
        by ptz0
        v 1.0
        dated 28/02/16
*/

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define TLD ".h1vesect.net"
#define LEN 24 // preferred length of generated domain w/o sizeof(TLD)

// domain generation based on DGA algo.
// takes year, month, day as args for algo.
char * generate_domain(unsigned long year, unsigned long month, unsigned long day) 
{
	char * domain = malloc(LEN + sizeof(TLD));
	for(unsigned short int i = 0; i < LEN; i++) 
	{
		year  = ((year ^ 8 * year) >> 11) ^ ((year & 0xFFFFFFF0) << 17);
		month = ((month ^ 4 * month) >> 25) ^ 16 * (month & 0xFFFFFFF8);
    		day   = ((day ^ (day << 13)) >> 19) ^ ((day & 0xFFFFFFFE) << 12);
    		domain[i] = (unsigned char)(((year ^ month ^ day) % 25) + 97);
  	}

  	strncpy(domain+LEN, TLD , sizeof(TLD));

  	domain[LEN + sizeof(TLD)] = '\0' ;

  	return domain;
}

int main(int argc, char **argv) 
{
	char * domain;
        time_t ctime = time(NULL);
        struct tm* ltime = localtime(&ctime);
        unsigned long year  = ltime->tm_year + 1900;
        unsigned long month  = ltime->tm_mon  + 1;
        unsigned long day    = ltime->tm_mday;

        printf("Time: %lu:%lu:%lu\n", year, month, day);

	// generate and print domain
        domain = generate_domain(year, month, day);
        printf("Domain: %s\n", domain);
	
	// check if malloc vars == NULL, if not call free()
	if(domain != NULL)
		free(domain);
  	return 0;
}

