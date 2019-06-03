#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <opensssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

SSL_load_error_strings();
ERR_load_BIO_strings();
OpenSSL_add_all_algorithms();

struct addrinfo addr_in, *res, *resp;

struct sockaddr_storage client;


int
main(int argc, char **argv)
{

	if(argc != 3) {
		printf("To few arguments: <source_ip> <portnum>\n");
		exit(-1);
	}
	
	void *src;	
	char str[INET6_ADDRSTRLEN],*buff;
	int cd,sd,client_size;
	
	memset(&addr_in, 0, sizeof(addr_in));
	addr_in.ai_family 	= AF_UNSPEC;
	addr_in.ai_socktype	= SOCK_STREAM;

	if(getaddrinfo( argv[1], argv[2], &addr_in, &res) != 0) {
		perror("getaddrinfo");
		exit(-1);
	}

	freeaddrinfo(res);
	
	for(resp = res; resp != NULL; resp = resp->ai_next) {
		if(resp->ai_family == AF_INET) {
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)resp->ai_addr;
			src = &(ipv4->sin_addr);
		}
		else {
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)resp->ai_addr;
			
		}
		
		inet_ntop(resp->ai_family,src,str,sizeof(str));

		printf("your IP Address is %s\n", str);
	}

	
	sd = socket(resp->ai_family, resp->ai_socktype, resp->ai_protocol);

	BIO & bio;
		
	SSL_CTX ctx = SSL_CTX_new(SSLv23_client_method());
	SSL ssl;

	if(! SSL_CTX_load_verify_loations(tx, "~/netstack/demoCA/modelCA_cert.pem",NULL))
	{	
		printf("Failed to load cert\n");
	}

	bio = BIO_new_ssl_connect(ctx);
	BIO_get_ssl(bio, & ssl);
	SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY); 
	
	
	
	bio = BIO_new_connect("0.0.0.0:port");
	if(bio == NULL)
	{
		printf("BIO_new_connect Failure\n");
		exit(-1);
	}

	if(BIO_do_connect(bio) <= 0)
	{
		printf("BIO_do_connect Failure\n");
		exit(-1);
	}

	char *buf;
	int len;
	buff = malloc(256 * sizeof(char));
	len = sizeof(buf);
	int x = BIO_read(bio,buf,len);
	if(x == 0)
	{
		printf("BIO_read Failure\n");
		exit(-1);


	}
	
	printf("%s\n",buf);	
	
	BIO_free_all(bio);


return 0;
}
	
