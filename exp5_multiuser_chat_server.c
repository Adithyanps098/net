#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<stdint.h>
int clients[10];
int client_count=0;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
void *handle_client(void *sock_fd){
    int csd=(int)(intptr_t)sock_fd;
    char buffer[1024];
    int i,j,len;
    while((len=recv(csd,buffer,sizeof(buffer),0))>0){
        buffer[len]='\0';

        pthread_mutex_lock(&lock);
        for(i=0;i<client_count;i++){
            if(clients[i]!=csd){
                send(clients[i],buffer,strlen(buffer),0);
                }
            }
        pthread_mutex_unlock(&lock);
        }
    pthread_mutex_lock(&lock);
    printf("\nClient disconnected. Removing socket %d...\n",csd);

    for(i=0;i<client_count;i++){
        if(clients[i]==csd) {
            for(j=i;j<client_count-1;j++){
                clients[j]=clients[j+1];
                }
            client_count--;
            break;
            }
        }
    pthread_mutex_unlock(&lock);
    close(csd);
    return NULL;
    }
int main(){
    int sd,csd;
    struct sockaddr_in servaddr;
    pthread_t tid;
    sd=socket(AF_INET,SOCK_STREAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(8888);
    bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    listen(sd,5);
    printf("Server waiting for chatters...\n");
    while(1){
        csd=accept(sd,NULL,NULL);
        pthread_mutex_lock(&lock);
        if(client_count<10){
            clients[client_count++]=csd;
            pthread_create(&tid,NULL,handle_client,(void *)(intptr_t)csd);
            }
        else{
            printf("Server full. Connection rejected.\n");
            close(csd);
            }
        pthread_mutex_unlock(&lock);
        }
    return 0;
    }
