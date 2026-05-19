#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<stdbool.h>
int main(){
    int csd,len;
    char sendmsg[30];
    struct sockaddr_in servaddr;

    csd=socket(AF_INET,SOCK_STREAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(33345);

    connect(csd,(struct sockaddr*)&servaddr,sizeof(servaddr));

    do{
        printf("\nEnter A Message:");
        fgets(sendmsg,sizeof(sendmsg),stdin);

        len=strlen(sendmsg);
        sendmsg[len-1]='\0';

        send(csd,sendmsg,strlen(sendmsg)+1,0);
        }
    while(strcmp(sendmsg,"exit")!=0);
    return 0;
    }
