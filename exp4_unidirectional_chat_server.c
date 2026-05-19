#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<stdbool.h>
int main(){
    int sd,nsd,clilen;
    char recvmsg[30];
    struct sockaddr_in cliaddr,servaddr;

    sd=socket(AF_INET,SOCK_STREAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(33345);

    bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    listen(sd,5);

    clilen=sizeof(cliaddr);
    nsd=accept(sd,(struct sockaddr*)&cliaddr,&clilen);

    do{
        printf("\nReceived Message:");
        recv(nsd,recvmsg,sizeof(recvmsg),0);
        printf("%s\n",recvmsg);
        }
    while(strcmp(recvmsg,"exit")!=0);
    return 0;
    }
