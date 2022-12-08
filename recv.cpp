#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>

// The name of the shared memory segment
#define SHARED_MEM_NAME "cpsc351sharedmem"

// The full path of the shared memory
#define FULL_SHARED_MEMORY_PATH "/dev/shm/cpsc351sharedmem"

// The name of the file where to save the received file
#define RECV_FILE_NAME "file__recv"

/**
 * Returns the size of the specified file
 * @param fileName - the name of the file
 * @return - the size of the specified or -1 if
 * the file information could not be retrieved
 */
int getFileSize(const char* fileName)
{
	
	// The buffer to store file information
	struct stat statBuff;
	
	// The file size
	int fileSize = -1;

	// Get the file information
	int status = stat(fileName, &statBuff);

	// Getting the size succeeded
	if(status == 0) 
	{
		// size of file is in member buffer.st_size;
		fileSize = statBuff.st_size;

	}
	// Something has gone wrong
	else
	{
		perror("stat");
	}
	
	return fileSize;
}

/**
 * The signal handler for the SIGUSR1 signal 
 * that will be executed when the process receives
 * the SIGUSR1 signal.  When this happens, the signal
 * is received, the process should get the size of the
 * shared memory (that according to the requirnments 
 * described in the assignment should be as big as the file,
 * receives the contents, and then saves them to a file
 * called file__recv
 * @param sigNum - the signal number
 */
void recvFile(int signNum)
{
	// The size of the shared memory
	int memSize = getFileSize(FULL_SHARED_MEMORY_PATH);
	
	// The buffer used to store the message copied
	// copied from the shared memory
	char buff[100];
	
	// The total number of bytes written
	int totalBytesWritten = 0;

	// The number of bytes written 
	int bytesWritten = 0;
	
	// The shared memory pointer;
	void* sharedMemPtr = NULL;
	
	// Open the file for writing
	int fd = open(RECV_FILE_NAME, O_CREAT | O_TRUNC | O_WRONLY);
	
	// Make sure the file was opened
	if(fd < 0)
	{
		perror("open");
		exit(1);
	}


	// TODO: Get the shared memory ID of the shared
	// memory segment allocated by the sender.
	// Get the pointer to the shared memory.
	// Copy the contents of the shared memory
	// into the file whose name is defined by the
	// macro RECV_FILE_NAME
	// NOTE: You will need to get the size of the
	// shared memory to be able to do this.  You
	// can use the getFileSize() function provided
	// above.  The path of the file abstracting
	// the shared memory is defined by the
	// FULL_SHARED_MEMORY_PATH macro above.
	
	// TODO: Close the file
	// TODO: Deallocate the shared memory	
	shm_unlink(SHARED_MEM_NAME);

}


int main(int argc, char** argv)
{	
	// TODO: Install the signal handler
	// for signal SIGUSR1 such that whenever
	// a process receives signal SIGUSR1, the
	// the receive function is called as a signal
	// handler
	
	// Wait forever until a signal arrives
	while(true)
	{
		sleep(1);
	}
			
	return 0;
}
