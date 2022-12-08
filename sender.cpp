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

#define SHARED_MEM_NAME "cpsc351sharedmem"


/**
 * Returns the size of the specified file
 * @param fileName - the name of the file
 * @return - the size of the specified or -1 if
 * the file information could not be retrieved
 */
int getFileSize(char* fileName)
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

int main(int argc, char** argv)
{	

	// The file size
	int fileSize = -1;

	// The variable to hold the shared memory id
	int shmid = -1;

	// The total number of bytes written
	int totalBytesRead = 0;

	// The number of bytes 
	int bytesRead = 0;

	// Whether we are done reading	
	bool finishedReading = false;

	// The shared memory pointer;
	void* sharedMemPtr = NULL;

	// Sanity checks -- make sure the user has provided a file
	if(argc < 3)
	{
		fprintf(stderr, "USAGE: %s <FILE NAME> <PID OF THE RECEIVER PROCESS>\n");
		exit(1);
	}

	// Open the file for reading
	int fd = open(argv[1], O_RDONLY);
	
	// Make sure the file was opened
	if(fd < 0)
	{
		perror("open");
		exit(1);
	}
	
	// Get the file size
	fileSize = getFileSize(argv[1]);
	
	// The file does not exist	
	if(fileSize < 0)
	{
		fprintf(stderr, "The file %s does not exist\n", argv[1]);
	}
	
	// Convert the process id to an integer
	int recvPid = atoi(argv[2]);
	
	// TODO: Create shared memory
	// Make the shared memory segment as large
	// as the file	
	// @return - on error, will return MAP_FAILED
	// Copy the file contents into shared memory
		

	// TODO: Send SIGUSR1 signal to the receiver
	// to tell it that the data is ready in memory
	
	return 0;
}
