#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>
int main(){
    int sd,nsd,len,port=1234;
    char content[30],fname[30];
    struct sockaddr_in cliaddr,servaddr;
    FILE *fp;
    if((sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1){
        printf("\nError Socket Creation");
        return 0;
        }

    bzero((char *)&servaddr,sizeof(servaddr));
    printf("\nThe Port Address Is:%d\n",port);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(port);

    if(bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1){
        printf("\nError Binding\n");
        return 0;
        }
    len=sizeof(cliaddr);
    listen(sd,1);
    nsd=accept(sd,(struct sockaddr*)&cliaddr,&len);
    if(nsd==-1){
        printf("\nError Accepting Client:\n");
        return 0;
        }
    printf("\nClient Accepted\n");
    len=recv(nsd,fname,30,0);
    fname[len]='\0';
    fp=fopen(fname,"rb");
    if(fp==NULL){
        printf("\nFile Not Found\n");
        close(nsd);
        close(sd);
        return 0;
        }
    while((len=fread(content,1,30,fp))>0){
        send(nsd,content,len,0);
        }
    send(nsd,"EOF",4,0);
    printf("\nFile Transferred.\n");
    fclose(fp);
    close(nsd);
    close(sd);
    return 0;
    }
