#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

char message[] = "Hello there!\n";
char buf1[sizeof(message)];
int fs, fr;
char key[3];

int main()
{
    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket");
        exit(1);
    }
    addr.sin_family = AF_INET; 
    addr.sin_port = htons(3425); // (Host TO Network Short)
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // Host TO Network Long

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2); 
    }

   while(1)
   {

	scanf("%s", &key);	

    if (key[0]== 'n'){
    	printf("%s\n",key ); 	
    	send(sock, key, 3 ,0);
    	break;
    }

    fs = send(sock,key,3 ,0);
    printf("%d\n", fs );
   
	fs = recv(sock,buf1,3,0);
	printf("%d\n", fs );
	printf("%s\n", buf1);
    }
    close(sock);
    return 0;
}