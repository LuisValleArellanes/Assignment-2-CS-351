    void* ptr = mmap(0, shmSize, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);
