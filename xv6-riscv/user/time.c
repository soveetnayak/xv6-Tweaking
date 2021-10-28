 #include"kernel/types.h"
#include"kernel/stat.h"
#include"user/user.h"
#include"kernel/fcntl.h"

int main(int argc, char ** argv)
{
    int pid = fork();
    if(pid<0)
    {
        printf("fork error\n");
        exit(1);
    }
    else if(pid==0)
    {
        if(argc==1)
        {
            sleep(10);
            exit(1);
        }
        else
        {
            exec(argv[1],argv+1);
            exit(1);
        }
    }
    else
    {
        int wait_time, run_time;
        waitx(0,&wait_time,&run_time);
        printf("run_time:%d\n",run_time);
        printf("wait_time:%d\n",wait_time);

    }
    exit(0);
}