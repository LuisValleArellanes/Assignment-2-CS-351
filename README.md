Certainly, here's your corrected README.md in a markdown-friendly format:

---

# Assignment-2-CS-351

## Overview

In this assignment, you will apply your knowledge of signals, POSIX shared memory, message passing, and pipes. You will implement three different multiprocess applications. Each application will comprise two processes that have a producer-consumer relationship. The first process, the sender, will read a user-specified file and transfer the file contents to the second process, the receiver. The receiver will receive the file contents and save them to another file.

The difference between the three applications is the inter-process communications (IPC) mechanism they use to transfer the file contents. The first application will use POSIX shared memory, the second will utilize POSIX message queues, and the third will use POSIX ordinary pipes to transfer the file data from the parent to the child. All applications will implement signal handlers for the various signals to ensure a graceful termination. Furthermore, the security issues related to the IPC will be explored, including the permissions of the shared memory objects.

The sections that follow outline the differences between the programs.

## Part I: Shared Memory

The sender and the receiver programs will work as follows:

### The Receiver:

1. The receiver shall be started before the sender. It shall be invoked as `./recv` from the command line.
2. When launched, it shall override the default signal handler function for the SIGUSR1 signal (the signal reserved for custom uses by user programs) with a function called `void recvFile(int sigNum)`. After doing so, the program shall go into a sleeping loop where it will sleep until a SIGUSR1 signal arrives.

Once the SIGUSR1 signal arrives, the program shall invoke the `recvFile` function. The function shall perform the following operations:

  a. Get the shared memory ID for the shared memory segment named `cpsc351sharedmem`. If the segment does not exist, the receiver exits with an error "Missing shared memory segment!". Otherwise, if the segment exists, the receiver continues to the next step.

  b. The receiver should assume that the shared memory segment in the previous step contains the data from a file that was put there by the sender. The receiver shall then get the size of the shared memory segment, read the data from the entire memory segment, and write the read data to a file called `file_recv`.

  c. Finally, the receiver shall deallocate the shared memory segment and exit.

### The Sender:

1. The sender shall be started as `./sender <file name> <ID of the receiver process>`. For example, `./sender file.txt 1245`. The first argument represents the name of the file to send and the second represents the process ID of the receiver process. Please note: you can always get the process id of the receiver process using the `pidof` command. E.g., `pidof recv`. Of course, this assumes that the receiver is already running.

2. The sender shall then allocate a shared memory segment named `cpsc351sharedmem` with permissions of 0600. This is done to ensure that only the processes running with the UID of the current user can access the shared memory contents - important security consideration to ensure that processes from other users cannot spy on the current user through shared memory.

3. The sender shall then get the size of the file whose name was provided in the command line, set the size of the shared memory to the size of the file, and shall then read the contents of the file and write them to the shared memory segment.

4. Finally, the sender program shall send the SIGUSR1 signal to the receiver program that the sender will assume is running. The sender can do this by invoking the `kill()` system call used for

