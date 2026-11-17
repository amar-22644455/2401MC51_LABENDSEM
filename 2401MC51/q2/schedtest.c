#include "types.h"
#include "stat.h"
#include "user.h"

void
work(int id, int pr, int loops)
{
  volatile int x = 0;
  int i;
  set_priority(getpid(), pr);
  printf(1, "P%d (pid %d, prio %d) start\n", id, getpid(), pr);
  for(i = 0; i < loops; i++) x++;
  printf(1, "P%d (pid %d, prio %d) done\n", id, getpid(), pr);
}

int
main(void)
{
  int i;
  printf(1, "Parent priority is being set to 1\n\n");
  printf(1, "Priority Scheduling\n");
  printf(1, "Parent is Forking 3 procs with priorities 5,10,20 \n\n");
  work(0, 1, 30000000);
  if(fork() == 0){ work(1, 5, 30000000); exit(); }
  if(fork() == 0){ work(2, 10, 30000000); exit(); }
  if(fork() == 0){ work(3, 15, 30000000); exit(); }
  wait(); wait(); wait(); 
  printf(1, "\n=== Expected 'done' order: P0,P1,P2,P3 (priority order) ===\n");
  printf(1, "=== schedtest done ===\n");
  exit();
}
