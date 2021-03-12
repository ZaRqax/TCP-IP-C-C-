#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
//#include <pthread.h>

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define BAD_MESSAGE         -13
#define SUCCESS               0
#define CLOSE                -1

char message[] = "XXXXXXX\n";
char buff[1024];
char key[3];
unsigned int sz;

/*/////////////////////////////////////////////////////////
typedef struct someArgs_tag
{
   // char key_1[3];
    int res;
}someArgs_t;

void* check_key(void *args){
    someArgs_t *arg = (someArgs_t*) args;
    char *key_t;
    scanf("%s",&key_t);
   // if (key_t[ == NULL){
       // return SUCCESS;
   //      pthread_exit(0);
    //}

    if (key_t[0] == 'n'){
        arg->res = CLOSE;
    }
    pthread_exit(0);
//   return SUCCESS;
}
///////////////////////////////////////////////////////////*/

int main()
{
    int sock, listener,temp;
    struct sockaddr_in addr;
    ///////////////////////////////////////Threads//////////////////////////
  /*pthread_t thread;
    int status, status_addr;
    someArgs_t arguments;*/
    ///////////////////////////////////////////////////////////////////////
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);// от хоста  в сеть 
    addr.sin_addr.s_addr = htonl(INADDR_ANY);// unigned long 
    
    if (bind(listener, (struct sockaddr *) &addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }
    
    if (listen(listener, 1) == -1 ){//Функция устанавливает сокет в режим прослушивания ,указываем число установленых соединений для данного совекта
        perror(" listener");
      //  close(listener);
        exit(2);
    }
      sock = 0;
      temp =1;
    while(temp)
    {
         sz = sizeof(addr);
         sock = accept(listener, (struct sockaddr *) &addr, &sz );  //принятие соеденения
         if (sock < 1){
            temp = 0;
         } 

    while (1)
    {
        printf("%s", "Номер сокета: ");
        printf("%d\n", sock );

        sz = recv (sock, &key, 3  ,0); 
        printf("%s\n","Количество отправленых байт" );
        printf("%d\n", sz);
        printf("%s","reception  ");
        printf("%s\n", key);     
        if (key[0]== 'n'){
            printf("Stop \n");
            break;
        }   
        sz = send(sock, &key,3,0);
        printf("%d\n", sz);
	prifnt("d",sz);
       
    }
        close(sock);  
        scanf("%s",key);
        if (key[0] == 'n'){
            break;
        }


    }
        
    
    return 0;
}






 ///////////////////////////////////////////////////////////////////////////////////////////(void*) &arguments
     /*   status = pthread_create(&thread,NULL, check_key, (void*) &arguments);
            if (status != 0) {
                printf("main error: can't create thread, status = %d\n", status);
                exit(ERROR_CREATE_THREAD);
            }
        status = pthread_join(thread,(void**)&status_addr);
            if (status != SUCCESS) {
                printf("main error: can't join thread, status = %d\n", status);
                exit(ERROR_JOIN_THREAD);
            }
          temp = arguments.res;*/
//////////////////////////////////////////////////////////////////////////////////////////////
