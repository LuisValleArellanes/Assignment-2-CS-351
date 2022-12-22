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

#define MAX_SIZE 100
int main(int argc, char* argv[MAX_SIZE]){

    //allocate shared memory
    int shmid = shm_open("/cpsc351sharedmem", O_CREAT | O_RDWR,0600);
    //get size of file
    FILE *f = fopen(argv[1], "r"); 
    if (f == NULL){
        fprintf(stderr, "Unable to find file!\n"); 
        exit(1);
    }
    fseek(f,0L,SEEK_END); 
    int fileSize = ftell(f); 
    printf("file size: %d\n", fileSize); 
    rewind(f);

    //set shared memory size
    ftruncate(shmid, fileSize); 
    //read file.txt and write the contents into shared memory segment 
    void* ptr = mmap(0, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);
    char buff[MAX_SIZE];
    fgets(buff, MAX_SIZE, f); 
    sprintf(ptr, buff, MAX_SIZE); 
    int pid = atoi(argv[2]);
    printf("pid = %d\n", pid); 

    //send signal to reciever
    kill(pid, SIGUSR1);
    fclose(f); 

    
    return 0; 
}