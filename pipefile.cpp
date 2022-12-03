#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

// The name of the received file
#define RECV_FILE_NAME "file__recv"



// -------------------------------------------------
// The parent function
// @param writePipeEndFd - the write-end of the pipe
// @param readFileFd - the filedescriptor of the open
// file
// ---------------------------------------------------
void parent(const int& writePipeEndFd, const int& readFileFd)
{
	// the file read size
	#define READ_SIZE 4096
	
	// The number of bytes read from the file
	int bytesRead = -1;	
	
	// The buffer to hold the read data
	char buff[READ_SIZE];
	
	// Read until we reach the end of the file
	while(bytesRead != 0)
	{
		// TODO: Read at most 4096 bytes 
		// from the file represnted by
		// the readFileFd.  Write the
		// data read to the write end of
		// the pipe. Keep repeating until
		// the entire file read. 
	}
}

// --------------------------------------------------
// Performs the child function of receiving the file
// contents
// @param readPipeEndFd - the read end of the pipe
// @param writFileFd - the descriptor of the file
// where to write the contents
// --------------------------------------------------
void child(const int& readPipeEndFd, const int& writeFileFd)
{
	// Maximum read size
	#define READ_SIZE 4096

	// How many bytes were read from the pipe
	int bytesRead = -1;	
	
	// The buffer to hold the data read from the pipe
	char buff[READ_SIZE];
	
	// Keep reading until the the other process
	// closes its write end
	while(bytesRead != 0)
	{
		// TODO: Read at most 4096 bytes from the read end pipe
		// and write the data read to the file represented by
		// the writeFileFd descriptor.
		// Keep repeating until the parent closes its 
		// write end.
	}
}

int main(int argc, char** argv)
{

	// The pipe array
	int fd[2];
	
	// The child process ID
	pid_t pid;
	
	// The read buffer
	char readBuff[4096];
	
	// The write buffer
	char writeBuff[4096];
	
	// The descriptors for the input and output files
	int inFd = -1, outFd = -1;
	
	// Make sure the user provided the name of the file
	if(argc < 2)
	{
		fprintf(stderr, "%s <FILE NAME>\n", argv[0]);
		exit(1); 
	}

	// TODO: Create a pipe
	
	// TODO: Create a child process	
	
	// Sanity checks
	if(pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if(pid > 0) // Parent
	{
		// Open the input file
		inFd = open(argv[1], O_RDONLY);

		// Sanity checks
		if(inFd < 0)
		{
			perror("open");
			exit(1);
		}

		// TODO: Close the pipe end the parent does not use
			
		parent(fd[1], inFd);
		
		// TODO: Close the pipe end the parent no longer needs
		
		// TODO: Close the input file
	}
	else // Child
	{

		// Open the file where to save the contents
		outFd = open(RECV_FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		
		// Sanity checks
		if(outFd < 0)
		{
			perror("open");
			exit(1);
		}
		
		// TODO: Close pipe end the child does not need
		
		// Call the child function
		child(fd[0], outFd);
		
		// TODO: Close the no longer needed end of the pipe
		// TODO: Close the output file
	}
}
