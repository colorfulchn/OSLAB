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
![TSS](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=TSS%E7%BB%93%E6%9E%84&step_word=&hs=0&pn=17&spn=0&di=29510&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=3743557637%2C4192097557&os=2657222472%2C3264107325&simid=4104034306%2C529928587&adpicid=0&lpn=0&ln=667&fr=&fmq=1584692936812_R&fm=result&ic=&s=undefined&hd=&latest=&copyright=&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=11&oriquery=&objurl=http%3A%2F%2Fimg2020.cnblogs.com%2Fi-beta%2F1944278%2F202003%2F1944278-20200306084206795-1378113112.png&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3Bvgks52f_z%26e3Bv54AzdH3F3fzyxAzdH3FrAzdH3F8d9n800n_z%26e3Bip4s&gsm=12&rpstart=0&rpnum=0&islist=&querylist=&force=undefined)
+ TSS对于上下文切换的速度太慢，所以本次实验的目的也是加快速度。

# 关于PCB
-------------
+ 关于PCB，你需要去看一下linux0.11中sched.h中的struct task_struct，当然里面也有TSS结构的定义，可以对比TSS的图和其结构来理解。

# 关于这四个文件
-------------
+ 直接替换即可，在VSCODE中提供compare selected可以查看更改了哪些内容。
