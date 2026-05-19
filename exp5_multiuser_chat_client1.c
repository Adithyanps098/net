#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>
void *receive_msg(void *sock_fd){
    int sd=*((int *)sock_fd);
    char buffer[1024];
    int len;

    while((len=recv(sd,buffer,sizeof(buffer),0))>0){
        buffer[len]='\0';
        printf("\r\e[KReceived Message: %s\n> ",buffer);
        printf("Enter Message: ");
        fflush(stdout);
        }
    return NULL;
    }
int main(){
    int sd;
    struct sockaddr_in servaddr;
    char message[1024];
    sd=socket(AF_INET,SOCK_STREAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(8888);
    servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    pthread_t tid;
    pthread_create(&tid,NULL,receive_msg,&sd);
    while(1){
        printf("\n\nEnter Message: ");
        fgets(message,1024,stdin);
        message[strcspn(message,"\n")]=0;
        if(strcmp(message,"exit")==0){
            printf("\nDisconnecting from server...\n\n");
            char leave_msg[]="User has left the chat.";
            send(sd,leave_msg,strlen(leave_msg),0);
            break;
            }
        send(sd,message,strlen(message),0);
        }
    close(sd);
    return 0;
    }
