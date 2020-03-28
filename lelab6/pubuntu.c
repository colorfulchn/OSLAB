#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>

#define NUMBER 520 /*打出数字总数*/
#define BUFSIZE 10 /*缓冲区大小*/

sem_t   *empty, *full, *mutex;
int main()
{
    int  i,shmid;
    int *p;
    int  buf_in = 0; /*写入缓冲区位置*/
    /*打开信号量*/
	mutex = sem_open("mutex", O_CREAT|O_EXCL, 0644, 1);
	empty = sem_open("empty", O_CREAT|O_EXCL, 0644, BUFSIZE);
    full = sem_open("full", O_CREAT|O_EXCL, 0644, 0);
	/*创建共享内存*/
	shmid = shmget((key_t)1234, BUFSIZE, IPC_CREAT | IPC_EXCL | 0664); 
	printf("shmid:%d\n", shmid);
	if (shmid == -1)
    {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }
    p = (int *)shmat(shmid, NULL, 0);
	if (p == (void *)-1)
    {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }

    /*生产者进程*/
	printf("producer start.\n");
	fflush(stdout);
    for( i = 0 ; i < NUMBER; i++)
    {
        sem_wait(empty);
        sem_wait(mutex);
        p[buf_in] = i;
        buf_in = ( buf_in + 1)% BUFSIZE;
		printf("Producer: %d\n", buf_in);
		fflush(stdout);
        sem_post(mutex);
        sem_post(full);
    }
	printf("producer end.\n");
	fflush(stdout);
    /*释放信号量*/
    sem_unlink("full");
    sem_unlink("empty");
    sem_unlink("mutex");
    return 0;
}
