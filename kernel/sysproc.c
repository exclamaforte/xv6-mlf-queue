#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "pstat.h"
#include "sysfunc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_getpinfo(void)
{
  struct pstat * p;
  if (argptr(0, (void *)&p, sizeof(struct pstat)) < 0) {
    return -1;
  }
  int i;
  for (i = 0; i < NPROC; i++) {
    p->inuse[i] = ptable.proc[i].state == UNUSED;
    p->pid[i] = ptable.proc[i].pid;
    p->priority[i] = ptable.proc[i].priority;
    p->state[i] = ptable.proc[i].state;
    p->ticks[i][0] = 0;
    p->ticks[i][1] = 0;
    p->ticks[i][2] = 0;
    p->ticks[i][3] = 0;
    p->ticks[i][p->priority[i]] = ptable.proc[i].numTicks;
  }
  return 0;
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
