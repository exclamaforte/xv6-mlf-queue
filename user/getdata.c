#include "user.h"
#include "pstat.h"
#include "spinlock.h"
#define NUMITER 100

typedef struct datum {
  struct pstat info;
  struct int time;
} datum;

int main () {
  int i;
  datum data[NUMITER];
  spinlock datalock;
  initlock(&datalock, "data");

  for (i = 0; i < NUMITER; i++) {
    acquire(&datalock)
    getpinfo(&(data[i].info));
    data[i] = uptime();
    release(&datalock);
    sleep(10);
  }
  int df;

  df = open("data.csv");
  
  int j;
  for(i = 0; i < NUMITER; i++) {
    for(j = 0; j < NPROC; j++) {
      printf("")
    }
  }
}
