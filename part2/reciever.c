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
struct mq_attr attr;
  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = 4096;
  attr.mq_curmsgs = 0;

  mqd_t mid = mq_open("/cpsc351mqueue", O_CREAT | O_RDWR, 0744, &attr);

  char buff[4096];
  int retval;
  FILE *f = fopen("file_recv.txt", "w");
  while(retval = mq_receive(mid,buff, 4096, NULL) > 0){
    fprintf(f, "%s", buff);
  }
  if (retval == 0){
    fclose(f);
    unlink("/cpsc351queue");
    exit(1);
  }

  return 0;
}
