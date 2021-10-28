#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
//user program time
int main(int argc, char *argv[]) {

    int a = fork();
    if(argc!=1){
        if (a == 0) {
            if(exec(argv[1], argv + 1)<0){
                printf(1,"Error in fork\n");
                exit();
            }
        } 
        else {
            int *wtime = (int *)malloc(sizeof(int)), *rtime = (int *)malloc(sizeof(int));
            int status = waitx(wtime, rtime);
            printf(1, "Run Time: %d, Waiting Time: %d, Returned: %d\n", *rtime, *wtime, status);
    }

    exit();

    }
    else{
        if (a == 0) {
            int b=1;
            for(int i=0;i<=1e7;i++){
                b+=2; //useless calculations, just to test waitx
            }
            exit();
            
        } 
        else {
            int *wtime = (int *)malloc(sizeof(int)), *rtime = (int *)malloc(sizeof(int));
            int status = waitx(wtime, rtime);
            printf(1, "Run Time: %d, Waiting Time: %d, Returned: %d\n", *rtime, *wtime, status);
        }
        exit();
    }


    exit();

}
