#include<stdio.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main(){
    int sd,nsd;
    struct sockaddr_in servaddr;
    char recvmsg[100],sendmsg[100];
    time_t ticks;
    sd=socket(AF_INET,SOCK_STREAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(1313);
    bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    listen(sd,10);
    printf("\nServer is running... Waiting for connections.\n");
    for(;;){
        nsd=accept(sd,(struct sockaddr*)NULL,NULL);
        if(fork()==0){
            close(sd);
            while(1){
                int n=recv(nsd,recvmsg,sizeof(recvmsg)-1,0);
                if(n<=0){
                    break;
                    }
                recvmsg[n]='\0';
                printf("\nReceived Message: %s",recvmsg);
                if(strncmp(recvmsg,"exit",4)==0){
                    break;
                    }
                ticks=time(NULL);
                snprintf(sendmsg,sizeof(sendmsg),"Server Time: %.24s\n",ctime(&ticks));
                send(nsd,sendmsg,strlen(sendmsg),0);
                }
            close(nsd);
            exit(0);
            }
        close(nsd);
        }
    return 0;
    }
