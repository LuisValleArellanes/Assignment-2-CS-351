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


int main() {

  struct mq_attr attr;

  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = 4096;
  attr.mq_curmsgs = 0;

  mqd_t qid = mq_open("/cpsc351sharedmem", O_CREAT | O_RDWR, 0744, &attr);
  char buff[100];
  int retVal = mq_receive(qid, buff, 4096, NULL);


  return 0;

}
