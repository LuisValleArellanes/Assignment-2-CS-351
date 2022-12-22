#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <string.h>
#include <mqueue.h>

int main(int argc, char *argv[]){

  FILE *f = fopen(argv[1], "r");

  struct mq_attr attr;
  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = 4096;
  attr.mq_curmsgs = 0;
  mqd_t mid = mq_open("/cpsc351mqueue",O_RDWR, 0744, &attr);

  if(mid < 0){
    fprintf(stderr, "unable to find message queue\n");
    exit(1);
  }

  char buff[4096];
  rewind(f);
  while(fgets(buff, 4096, f)!= NULL){
    mq_send(mid, buff, 4096,1);
  };
  mq_send(mid, NULL, 0, 2);
  fclose(f);


  return 0;
}
