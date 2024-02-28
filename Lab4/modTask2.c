#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

#define CHILD_ID 0
int main(){
    freopen("matrix.txt","r",stdin);
    int row1,col1,row2,col2;

    scanf("%d %d %d %d",&row1, &col1, &row2, &col2);
    int mat1[row1][col1], mat2[row2][col2], result[row1][col2];
    int i,j,k,pid,parentpid=getppid();

    for(i=0; i<row1; i++){
        for(j=0; j<col1; j++){
            scanf("%d",&mat1[i][j]);
        }
    }
    for(i=0; i<row2; i++){
        for(j=0; j<col2; j++){
            scanf("%d",&mat2[i][j]);
        }
    }
    for(i=0; i<row1; i++){
        for(j=0; j<col2; j++){
            result[i][j]=0;
        }
    }
    printf("Multiplied matrix:\n");
    i=0;
    k = 0;
    while(i < row1){
        for(k=0; k<3; k++){
            // printf("i: %d k: %d parentProcessId: %d processId: %d\t",i,k,getppid(),getpid());
            if(pid=fork() == CHILD_ID){
                int temp = 0;
                for(j=0; j<3; j++){
                    temp += mat1[i][j] * mat2[j][k];
                }
                printf("%5d",temp);
                exit(0);
            }
            wait(NULL);
        }
        printf("\n");
        i++;
    }
    return 0;
}