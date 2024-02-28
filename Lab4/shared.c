#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define N 3

int main() {
    freopen("matrix.txt","r",stdin);
    int row1,col1,row2,col2;

    scanf("%d %d %d %d",&row1, &col1, &row2, &col2);
    int i,j,k,pid,parentpid=getppid();
    double mat1[N][N], mat2[N][N];
    for(i=0; i<row1; i++){
        for(j=0; j<col1; j++){
            scanf("%lf",&mat1[i][j]);
        }
    }
    for(i=0; i<row2; i++){
        for(j=0; j<col2; j++){
            scanf("%lf",&mat2[i][j]);
        }
    }

    key_t key = ftok("matrix_multiplication", 65);
    int shmid = shmget(key, sizeof(double[N][N]), IPC_CREAT | 0666);

    double (*result)[N] = shmat(shmid, NULL, 0);

    for (int i = 0; i < N; i++) {
        printf("i: %d, pid: %d, ppid: %d \n", i, getpid(), getppid());
        int pid = fork();

        if (pid == 0) {
            for (int j = 0; j < N; j++) {
                result[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    result[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
            shmdt(result);
            exit(0);
        } else if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        wait(NULL);
    }

    printf("Result Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%lf\t", result[i][j]);
        }
        printf("\n");
    }

    shmdt(result);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}