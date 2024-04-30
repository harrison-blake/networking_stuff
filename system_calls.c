#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT "3490"

int main(int argc, char *argv[])
{
	struct addrinfo hints, *servinfo, *p;
	int status;
	char ipstr[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	status = getaddrinfo(NULL, PORT, &hints, &servinfo);

	if(status != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 1;
	}

	for(p = servinfo;p != NULL; p = p->ai_next)
	{
	    void *addr;
		char *ipver;

	    if(p->ai_family == AF_INET)
	    {
	 	    struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
	 	    addr = &(ipv4->sin_addr);
	 	    ipver = "IPv4";
	 	}
	 	else
	 	{
	 		struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
	 		addr = &(ipv6->sin6_addr);
	 		ipver = "IPv6";
	 	}

        printf("%s: %s\n", ipver, inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr));
	}

	return 0;
}