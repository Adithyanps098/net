#include<stdio.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(){
    int sd,n;
    char sendmsg[100],recvmsg[101];
    struct sockaddr_in servaddr;
    if((sd=socket(AF_INET,SOCK_STREAM,0))<0){
        perror("\nSocket error");
        exit(1);
        }
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(1313);
    inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
    if(connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
        perror("\nConnect error");
        exit(1);
        }
    printf("\nConnected to Server. Type 'exit' to quit.\n");
    do{
        printf("\nEnter A Message: ");
        fgets(sendmsg, sizeof(sendmsg),stdin);

        send(sd,sendmsg,strlen(sendmsg),0);
        if(strncmp(sendmsg,"exit",4)==0){
            break;
            }
        n=recv(sd,recvmsg,100,0);
        if(n>0){
            recvmsg[n]='\0';
            printf("Received Message: %s",recvmsg);
            }
        }
    while(1);
    close(sd);
    return 0;
    }
