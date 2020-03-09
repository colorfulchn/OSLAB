#include <string.h>
#include <errno.h>
#include <asm/segment.h>

char msg[24]；  /* 23个字符*/


/*functiom:首先，从用户态获得到agrv[1]的信息，并且拷贝在msg上
           其次，获得其长度
           最后return如果字符数字超过23则返回EINVAL*/
int sys_iam(const char* name)
{
    int i=0,len=0;
    char tmp[30];
    for(i=0;i<30;i++)
    {
        tmp[i]=get_fs_byte(name+i); /*在内核访问用户态*/
        if(tmp[i]=='\0') 
        {
            len=i;
            break;
        }
    }
    if(len>23)
    {
        return -(EINVAL);
    }
    strcmp(msg,tmp);
    return len;
}


/***
function:将msg拷贝到name指向的用户地址空间中,确保不会对name越界访存(name的大小由size说明)
return: 拷贝的字符数。如果size小于需要的空间,则返回“­-1”,并置errno为EINVAL。
****/
int sys_whoami(char* name, unsigned int size)
{
    int i,j=size,k;
    for(i=0;msg[i]!='\0';i++)
    if(i>=j)
    {
        return -(EINVAL);
    }


    for(k=0;k<j;k++)
    {
        put_fs_byte(msg[k],name+k);
        if(msg[k]=='\0')
        {
            break;
        }
    }
    return k;
}
