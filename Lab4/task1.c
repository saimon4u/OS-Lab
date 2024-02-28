#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define CHILD_ID 0


int main(){
    int range,even=0,odd=0,from;
    printf("Enter the value of range: ");
    scanf("%d",&range);

    int processid=fork();

    if(processid == CHILD_ID){
        from = 1;
        while(from <= range){
            odd += from;
            from += 2;
        }
        printf("Sum of the odd numbers from 1 to range is : %d\n",odd);
    }
    else{
        from = 0;
        while(from <= range){
            even += from;
            from += 2;
        } 
        printf("Sum of the even numbers from 1 to range is n: %d\n",even);
    }
    return 0;
}