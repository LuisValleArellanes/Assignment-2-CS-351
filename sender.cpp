#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <mqueue.h>
#include <unistd.h>
#include <signal.h>

#define MSQ_NAME "/cpsc351queue"


int main(int argc, char** argv)
{	

	// The file size
	int fileSize = -1;

	// The buffer used to store the message copied
	// copied from the shared memory
	char buff[4096];

	// The variable to hold the message queue ID
	int msqid = -1;

	// The total number of bytes written
	int totalBytesRead = 0;

	// The number of bytes 
	int bytesRead = 0;

	// Whether we are done reading	
	bool finishedReading = false;
	
	// TODO: Define a data structure
	// of type mq_attr to specify a
	// queue that can hold up to 10
	// messages with the maximum message
	// size being 4096 bytes
	
	// Sanity checks -- make sure the user has provided a file
	if(argc < 2)
	{
		fprintf(stderr, "USAGE: %s <FILE NAME>\n", argv[0]);
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
	
	
	// TODO: Gain access to the message queue
	// whose name is defined by the macro
	// MSQ_NAME macro above. We assume that
	// the receiver has allocated the message queue.

	
	//TODO: Loop below attempts to read the 
	// file 4096 bytes at a time.
	// Modify the loop as necessary to send
	// each chunk of data read as message
	// through the message queue. You can use
	// 1 for the priority of the message.

	// Keep writing until all data has been written
	while((totalBytesRead < fileSize) && !finishedReading)
	{
		// Read from file to the shared memory
		bytesRead = read(fd, buff, 4096);

		// Something went wrong
		if(bytesRead < 0)
		{
			perror("read");
			exit(1);
		}
		// We are at the end of file
		else if(bytesRead == 0)
		{
			// We are at the end of file
			finishedReading = true;		
		}
		
		
		totalBytesRead += bytesRead;
	}
	
	// TODO: Send a message with size of 0
	// to the receiver to tell it that the
	// transmission is done
		
	fprintf(stderr, "Sent a total of %d bytes\n", totalBytesRead);
	
	// TODO: Close the file		
	
	return 0;
}
