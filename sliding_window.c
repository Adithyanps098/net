#include<stdio.h>
int main(){
    int i,f,w,frames[50];
    printf("Enter Window Size:");
    scanf("%d",&w);
    printf("\nEnter No Of Frames To Transmit:");
    scanf("%d",&f);
    printf("\nEnter %d Frames:",f);
    for(i=1;i<=f;i++){
        scanf("%d",&frames[i]);
        }
    printf("\nWith Sliding Window Protocol, frames will be sent in the following manner(Assuming no corruption of frames)\n\n");
    printf("\nAfter sending %d frames at each stage, sender waits for acknowledgement sent by the receiver\n\n",w);
    for(i=1;i<=f;i++){
        if(i%w==0){
            printf("%d \n",frames[i]);
            printf("Acknowledgement of above frames sent is received by sender\n\n");
            }
        else{
            printf("%d ",frames[i]);
            }
        }
    if(f%w!=0){
        printf("\nAcknowledgement of above frames is received by sender\n");
        }
    return 0;
    }
