#include <linux/sem.h>
#include <linux/sched.h>
#include <unistd.h>
#include <asm/segment.h>
#include <linux/tty.h>
#include <linux/kernel.h>
#include <linux/fdreg.h>
#include <asm/system.h>
#include <asm/io.h>

sem_t semtable[SEMTABLE_LEN];
int cnt=0;

sem_t *sys_sem_open(const char *name,unsigned int value)
{
    int i,j,max,target;
    int isexist=0;
    char msg[100];
    sem_t *p=NULL;
    for(i=0;i<100;i++)
    {
        msg[i]=get_fs_byte(name+i);
        if(msg[i]=='\0') 
        {
            max=i;
            break;
        }
    }

    if(max > SEM_NAME_LEN)
    return NULL;

    for(j=0;j<cnt;j++)
    {
        if( !strcmp(msg,semtable[j].name) )
        {
            isexist=1;
            target=j;
            break;
        }
    }

    if(isexist=0)
    {
        strcpy(semtable[cnt].name,msg);
        p=(sem_t*)(&semtable[cnt]);
        semtable[cnt].value = value;
        cnt++;
    }

    if(isexit=1)
    {
        p=(sem_t*)(&semtable[target]);
    }
    return p;
}


int sys_sem_wait(sem_t *sem)
{
    cli();
    while( sem->value <= 0 )        /*使得所有小于0的进程阻塞*/
        sleep_on(&(sem->queue));    
    sem->value--;             
    sti();
    return 0;
}

int sys_sem_post(sem_t *sem)
{
     cli();
    sem->value++;
    if( (sem->value) <= 1)    /*小于0阻塞，只有为1时才唤醒，保证一次仅唤醒一个进程*/
        wake_up(&(sem->queue));
    sti();
    return 0;
}

int sys_sem_unlink(const char *name)
{
    int i,j,max,target;
    int isexist=0;
    char msg[100];
    sem_t *p=NULL;
    for(i=0;i<100;i++)
    {
        msg[i]=get_fs_byte(name+i);
        if(msg[i]=='\0') 
        {
            max=i;
            break;
        }
    }

    if(max > SEM_NAME_LEN)
    return NULL;

    for(j=0;j<cnt;j++)
    {
        if( !strcmp(msg,semtable[j].name) )
        {
            isexist=1;
            target=j;
            break;
        }
    }

    if(isexist=0)
    {
        return -1
    }

    if(isexit=1)
    {
       int tmp=0;
        for(tmp=i;tmp<=cnt;tmp++)
        semtable[tmp]=semtable[tmp+1];
        cnt--;
        return 0;
    }
}