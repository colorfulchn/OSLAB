#define __LIBRARY__
#include <unistd.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <errno.h>

static shm_ds shm_list[SHM_SIZE] = {{0,0,0}};

int sys_shmget(unsigned int key, size_t size)
{
	int i;
	unsigned long page;
  	if(size>PAGE_SIZE)/* 内存大小超过一页 */
  	{
      	printk("shmget: size %u cannot be greater than the page size %ud. \n", size, PAGE_SIZE);
      	return -ENOMEM;
 	 }
  	if(key==0)
  	{
      	printk("shmget: key cannot be 0.\n");
      	return -EINVAL;
 	 }	
 	 /* 若共享内存描述符已存在，直接返回索引 */
  	for(i=0; i<SHM_SIZE; i++)
  	{
      	if(shm_list[i].key == key)
          	return i;
  	}
	/* 获取空闲物理内存页面 */
	page = get_free_page();
	if(!page)
		return -ENOMEM;
	printk("shmget get memory's address is 0x%08x\n",page);
  	/* 找到一个未用的共享内存描述符初始化，并返回索引 */
  	for(i=0; i<SHM_SIZE; i++)
  	{
      	if(shm_list[i].key==0)
      	{
          	shm_list[i].key = key;
          	shm_list[i].size = size;
			shm_list[i].page = page;
          	return i;
      	}	
  	}
	return -1; /* 共享内存数量已满 */
}

void * sys_shmat(int shmid)
{
 	 unsigned long data_base, brk;
	/*判断 shmid 是否合法*/
 	 if(shmid < 0 || SHM_SIZE <= shmid || shm_list[shmid].page==0 || 	shm_list[shmid].key <= 0)
      	return (void *)-EINVAL;

  	data_base = get_base(current->ldt[2]);
  	printk("current's data_base = 0x%08x,new page = 0x%08x\n",data_base,shm_list[shmid].page);

  	brk = current->brk + data_base;
  	current->brk += PAGE_SIZE;
	/* 建立线性地址和物理地址的映射*/
  	if(put_page(shm_list[shmid].page, brk) == 0)
      	return (void *)-ENOMEM;

  	return (void *)(current->brk - PAGE_SIZE);
 }
/* sys_shmat另一种实现 */
void * sys_shmat(int shmid)
{
 	 /* 判断 shmid 是否合法 */
  	if (shmid < 0 || shmid >= SHM_SIZE || shm_list[shmid].key == 0) 
    	  return -EINVAL;
 	 /* 把物理页面映射到进程的虚拟空间 */
  	put_page(shm_list[shmid].page, current->brk + current->start_code); 
  	/* brk为代码段和数据段的总长度，修改总长度 */
  	current->brk += PAGE_SIZE;  
  	return (void*)(current->brk - PAGE_SIZE);
}
