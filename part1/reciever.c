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
using namespace std;


void recvFile(int sigNum){
    //get shared memory ID
    int shmid = shm_open("/cpsc351sharedmem", O_RDWR);

    //error check
    if (shmid < 0){
        fprintf(stderr, "Missing shared memory segment!\n");
        exit(1);
    }
    //get size of shared memory segment
    struct shmid_ds buf;
    shmctl(shmid, IPC_STAT,&buf);
    int shmSize = (int) buf.shm_segsz;


    //map shared memory segment to a ptr and copy its contents into a buffer
    void* ptr = mmap(0, shmSize, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);
    char buff[100];
    strncpy(buff, ptr, 100);

    //write to file_recv
    FILE *f = fopen("file_recv.txt", "w");
    if (f == NULL){
        fprintf(stderr, "error opening file!\n");
        exit(1);
    }
    //print buff to file_recv
    fprintf(f, "%s", buff);


    //deallocate shared memory
    fclose(f);
    unlink("/cpsc351sharedmem");
    exit(1);
}

void messageQueue() {

  mq_attr attr;

  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = 4096;
  attr.mq_curmsg = 0

  mqd_t qid = mq_open("/cpsc351sharedmem", O_CREAT | O_RDWR, 0744, &attr);
  int recvMQ = mq_receive(qid, char buff[100], 4096, NULL);


}

int main(){

    //override signal
    signal(SIGUSR1, recvFile);

    //sleep program intill signal is overridden
    while(1){
        pause();
        printf("signal recieved");
    }

    return 0;
}
