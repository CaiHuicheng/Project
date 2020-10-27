
/* getaddrinfo.c */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main()
{
	struct addrinfo hints, *res = NULL;
	int rc;
	
	memset(&hints, 0, sizeof(hints));
	/*����addrinfo�ṹ���и����� */
	hints.ai_flags = AI_CANONNAME;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	
	/*����getaddinfo����*/
	rc = getaddrinfo("localhost", NULL, &hints, &res);
	if (rc != 0) 
	{
		perror("getaddrinfo");
		exit(1);
	}
	else
	{
		printf("Host name is %s\n", res->ai_canonname);
	}
	exit(0);
}