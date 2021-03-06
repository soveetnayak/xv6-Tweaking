#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  if (argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0; // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if (argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
sys_waitx(void)
{
  uint64 a0, a1,a2;
  uint run_time,wait_time;
  if (argaddr(0, &a0) < 0)
    return -1;
  if (argaddr(1, &a1) < 0)
    return -1;
  if (argaddr(2, &a2) < 0)
    return -1;

  int ret = waitx(a0,&wait_time,&run_time);

  struct proc* p = myproc();
  if(copyout(p->pagetable, a1, (char*)&wait_time, sizeof(uint)) < 0)
    return -1;
  if(copyout(p->pagetable, a2, (char*)&run_time, sizeof(uint)) < 0)
    return -1;
  
  return ret;
}

uint64
sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//Adding a new system call for the trace function
uint64
sys_trace() 
{
  int mask;

  if(argint(0, &mask) < 0)
    return -1;
  
  myproc()-> mask = mask;
  
  return 0;
}
