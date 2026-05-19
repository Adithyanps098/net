#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>
int main(){
    int sd,len,port=1234;
    char content[30],fname[30];
    struct sockaddr_in servaddr;
    if((sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1){
        printf("\nError Socket Creation");
        return 0;
        }
    bzero((char *)&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(port);

    if(connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1){
        printf("\nError Connecting To Server\n");
        return 0;
        }
    printf("\nEnter Name Of File To Request:");
    scanf("%s",fname);

    send(sd,fname,strlen(fname),0);
    FILE *fp=fopen("received_file.txt","wb");
    if(fp==NULL){
        printf("\nError Creating File to store received data\n");
        close(sd);
        return 0;
        }
    while((len=recv(sd,content,30,0))>0){
        if(strcmp(content,"EOF")==0){
            break;
            }
        fwrite(content,1,len,fp);
        printf("%s",content);
        }
    printf("\nFile Received & Saved as 'received_file.txt'\n");
    fclose(fp);
    close(sd);
    return 0;
    }
