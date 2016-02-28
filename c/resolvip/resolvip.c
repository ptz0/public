/*
	resolveip
	by ptz0
	v 1.0
	dated 02/02/16
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#define __STDC_WANT_LIB_EXT1__ 1

char *target;
struct sockaddr_in *ipv4;

void usage()
{	
	printf("\nUsage: resolvip [TARGET]\n");
	printf("Resolves the specified hostname into an IPV4 address.\n");
	printf("If IPV6 is available, it will be displayed as well.\n\n");
}
int main(int argc, char **argv)
{
	if(argc == 1)
	{
		usage();
		return 1;
	}

	struct addrinfo hints, *res, *p;
   	int status;
	char ipstr[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
    	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) 
	{
        	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        	return 2;
    	}
	
	printf("IP addresses for %s:\n\n", argv[1]);

   	for(p = res;p != NULL; p = p->ai_next) 
	{
        	void *addr;
        	char *ipver;
	
	// get the pointer to the address itself,
        // different fields in IPv4 and IPv6:
        	if(p->ai_family == AF_INET) 
		{	// IPv4
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            		addr = &(ipv4->sin_addr);
            		ipver = "IPv4";
        	} 
		else
	 	{
			 // IPv6
            		struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            		addr = &(ipv6->sin6_addr);
            		ipver = "IPv6";
        	}	

	 	inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
       	 	printf("  %s: %s\n", ipver, ipstr);
    	}

    	freeaddrinfo(res); // free the linked list

	return 0;
}
