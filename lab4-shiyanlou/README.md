# 关于内核栈
--------------------
![内核栈](https://pic3.zhimg.com/v2-72f6b2eb12c3bdd705192b45330e8772_b.jpg)
+ 1、这里说一下，我的理解，用户栈和内核栈通过SS SP EFLAGS CS IP这些内核高地址的信息来连接，这些东西来连接。
+ 2、系统在创建一个新进程的时候，会在一个4KB一页上创建该进程的一系列东西，低地址部分连接PCB，所以在该实验中4096也就是4K，也就是一页的大小，PCB+4k也就是内核栈空栈时的栈顶。
+ 3、栈帧，栈帧是每一个进程中的每个函数自己信息的保存，在内核栈中，由于我们用switch_to传出了pnext和LDT的一些信息，在本次实验中，调用者栈帧的参数1是pnext，参数2是LDT的的信息。
+ 4、每一个进程的内核栈都是唯一的。

# 关于栈帧
 ---------------
![栈帧](https://img-blog.csdnimg.cn/20200105142509246.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xhb3NodXl1ZGFvaG91,size_16,color_FFFFFF,t_70)

# 关于TSS
------------
![TSS](https://img-blog.csdn.net/20170701171801683?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvY2hlbjE1NDA1MjQwMTU=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)
+ TSS对于上下文切换的速度太慢，所以本次实验的目的也是加快速度。

# 关于PCB
-------------
+ 关于PCB，你需要去看一下linux0.11中sched.h中的struct task_struct，当然里面也有TSS结构的定义，可以对比TSS的图和其结构来理解。

# 关于这四个文件
-------------
+ 直接替换即可，在VSCODE中提供compare selected可以查看更改了哪些内容。

关于上述内容，如有侵权，联系我，必删。
