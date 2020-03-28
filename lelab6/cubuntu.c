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
	struct shmid_ds buf;
    int  i,shmid,data;
    int *p;
    int  buf_out = 0; /*从缓冲区读取位置*/
    /*打开信号量*/
	mutex = sem_open("mutex", 1);
	empty = sem_open("empty", BUFSIZE);
    full = sem_open("full", 0);
	/* 创建共享内存,标志符要与生产者相同*/
	shmid = shmget((key_t)1234, 0, 0); 
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

    for( i = 0; i < NUMBER; i++ )
    {
        sem_wait(full);
        sem_wait(mutex);
        data = p[buf_out];
        buf_out = (buf_out + 1) % BUFSIZE;
        sem_post(mutex);
        sem_post(empty);
        /*消费资源*/
        printf("consumer%d:  %d\n",getpid(),data);
        fflush(stdout);
    }
    printf("consumer end.\n");
    fflush(stdout);
    /*释放信号量*/
    sem_unlink("full");
    sem_unlink("empty");
    sem_unlink("mutex");
	shmctl(shmid, IPC_RMID, &buf);
    return 0;
}
