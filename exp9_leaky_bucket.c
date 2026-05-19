#include<stdio.h>
int min(int x,int y){
    if(x<y){
        return x;
        }
    return y;
    }
int main(){
    int drop=0,mini,msec,cap,count=0,i,inp[25],process;
    printf("\nEnter Bucket Size:");
    scanf("%d",&cap);
    printf("\nEnter Output Rate:");
    scanf("%d",&process);
    printf("\nEnter no of sec you need to stimulate:");
    scanf("%d",&msec);
    for(i=0;i<msec;i++){
        printf("\nEnter size of packet entering at %d sec:",i+1);
        scanf("%d",&inp[i]);
        }
    printf("\nTime|\tPacket Received|\tPacket Send From Bucket|\tPacket Left In Bucket|\t\t\t           Packet Drop\n");
    for(i=0;i<msec;i++){
        count+=inp[i];
        if(count>cap){
            drop=count-cap;
            count=cap;
            }
        printf("%d",i+1);
        printf("\t%d",inp[i]);
        mini=min(count,process);
        printf("\t\t\t\t%d",mini);
        count=count-mini;
        printf("\t\t\t\t%d",count);
        printf("\t\t\t\t\t\t%d\n",drop);
        drop=0;
        }
    for(;count!=0;i++){
        if(count>cap){
            drop=count-cap;
            count=cap;
            }
        printf("%d\t0",i+1);
        mini=min(count,process);
        printf("\t\t\t\t%d",mini);
        count=count-mini;
        printf("\t\t\t\t%d",count);
        printf("\t\t\t\t\t\t%d\n",drop);
        }
    return 0;
    }
