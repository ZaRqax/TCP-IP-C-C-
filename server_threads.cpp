#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <netinet/in.h>
 #include <arpa/inet.h>


using namespace std;

void server();

//this PC - 10.0.1.132
//another PC - 10.0.1.139 
int main()
{
	sleep(4);
	int sock1; char msg[1024];
	int reuse = 1;
	thread th(server);
    struct sockaddr_in addr1;

    sock1 = socket(AF_INET, SOCK_STREAM, 0);
    if (sock1 < 0)
    {
        perror("socket");
        exit(1);
    }
    printf("%s\n", "bind client" );
    addr1.sin_family = AF_INET; 
    addr1.sin_port = htons(3425); // (Host TO Network Short)
    addr1.sin_addr.s_addr = inet_addr("127.0.0.1");//htonl(INADDR_LOOPBACK); // inet_addr("10.0.1.139");// htonl(INADDR_LOOPBACK); //inet_addr("10.0.1.190"); // Host TO Network Long //inet_addr
    printf("%s\n", "connect client" );
    if (connect(sock1, (struct sockaddr *)&addr1, sizeof(addr1)) < 0)
    {
        perror("connect");
        exit(2); 
    }
if (setsockopt(sock1, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0)
perror("setsockopt(SO_REUSEADDR) failed");
#ifdef SO_REUSEPORT
if (setsockopt(sock1, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse, sizeof(reuse)) < 0)
perror("setsockopt(SO_REUSEPORT) failed");
#endif
 printf("%s\n", "client connected" );
   while(1)
   {
    scanf("%s",msg);
    send(sock1,msg,sizeof(msg),0);
    if(msg[0]== '!'){break;
    }
    }

    close(sock1);

	th.join();



	// int n;
	// scanf("%d",&n);
	// thread th(do_work,n);
	// string s;
	// for(int i = 0 ; i< 5; i++){
	// 	scanf("%s",s);
	// 	printf("%s\n", s);
	// 	if (s == "!"){
	// 		break;
	// 	}
	// }
	


	
return 0;
}

void server(){

    int sock, listener,temp;
	char buff[1024]; unsigned int sz;
    struct sockaddr_in addr;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    int reusee = 1;
if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (const char*)&reusee, sizeof(reusee)) < 0)
perror("setsockopt(SO_REUSEADDR) failed");
#ifdef SO_REUSEPORT
if (setsockopt(listener, SOL_SOCKET, SO_REUSEPORT, (const char*)&reusee, sizeof(reusee)) < 0)
perror("setsockopt(SO_REUSEPORT) failed");
#endif
    if (listener < 0)
    {
        perror("socket");
        exit(1);
    }
    printf("%s\n", "Binding server \n");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);// от хоста  в сеть 
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");//inet_addr("10.0.1.132");//htonl(INADDR_ANY);    //htonl(INADDR_ANY);// unigned long 
    printf("%s\n", "bind server" );
    if (bind(listener, (struct sockaddr *) &addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }
    printf("%s\n", "start listener\n" );
    if (listen(listener, 1) == -1 ){//Функция устанавливает сокет в режим прослушивания ,указываем число установленых соединений для данного совекта
        perror(" listener");
      //  close(listener);
        exit(2);
    }
      sock = 0;
      temp =1;
    while(temp == 1){
         
         printf("%s\n", "start \n" );
         sz = sizeof(&addr);
         sock = accept(listener, (struct sockaddr *) &addr, &sz);  //принятие соеденения
int reuse = 1;
if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0)
perror("setsockopt(SO_REUSEADDR) failed");
#ifdef SO_REUSEPORT
if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse, sizeof(reuse)) < 0)
perror("setsockopt(SO_REUSEPORT) failed");
#endif
         printf("%s\n", "stop \n" );
         if (sock < 1){

            temp = 0;
         } 
        printf("%s", "Дескриптор сокета: ");
        printf("%d\n", sock );
         
    while (1)
    {
        sz = recv (sock, &buff , 1024 ,0); 
        printf("%s","Принято:  ");
        printf("%s\n", buff);     
        if (buff[0] == '!'){
            break;   
            temp =0;    
        }
      
    
      }
    }
        close(sock);  
       close(listener);


        
    
	// for(size_t i =0; i< n;i++){
	// 	cout << "ID of thread: "<< this_thread::get_id()<< " do_work " <<i <<endl;
	//     this_thread::sleep_for(chrono::milliseconds(1500)); 	 
	// }
}
	