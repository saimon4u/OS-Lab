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
    while(i < row1){
        if(pid=fork() == CHILD_ID){
            printf("i: %d parentProcessId: %d processId: %d\t",i,getppid(),getpid());
            j=0;
            while(j < col1){
                k = 0;
                while(k < col2){
                    result[i][k] += mat1[i][j] * mat2[j][k];
                    k++;
                }
                j++;
            }
            for(int p=0; p<col2; p++){
                printf("%5d",result[i][p]);
            }
            printf("\n");  
            exit(0);
        }
        wait(NULL);
        i++;
    }
    return 0;
}