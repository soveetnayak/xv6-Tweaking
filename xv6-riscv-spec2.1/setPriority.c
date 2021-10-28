
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
//user program set priority
int main(int argc, char * argv[])
{
    int priority,pid;

    if(argc!=3)
    {
        printf(2, "Invalid Number of Arguments");
        exit();
    }
    pid = atoi(argv[2]);
    priority = atoi(argv[1]);
    if(priority <= -1 || priority >= 101)
    {
        printf(2, "Invalid priority given. Try again\n");
        exit();
    }
    if(set_priority(priority,pid)==-1){
        printf(1,"Error in set_priority\n");

    }
    exit();
}