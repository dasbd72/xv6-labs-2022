// #include "types.h"
// #include "param.h"
// #include "defs.h"
// #include "proc.h"
// #include "spinlock.h"
// #include "sleeplock.h"
// #include "sysinfo.h"

#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "fs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "file.h"
#include "stat.h"
#include "proc.h"
#include "sysinfo.h"

uint64
sys_sysinfo(void)
{
  uint64 dst; // user pointer to struct sysinfo

  struct proc *p = myproc();
  struct sysinfo si;

  argaddr(0, &dst);

  si.freemem = kgetfreemem();
  si.nproc = getnumproc();
  if(copyout(p->pagetable, dst, (char *)&si, sizeof(si)) < 0)
    return -1;
  return 0;
}
