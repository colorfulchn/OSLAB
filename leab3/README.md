#关于exit、fork、printk、sched
 
 +直接将三个文件替换到kernel里的文件即可.
 +若是想要对比在哪插入了N,J,R,W,E可以用[VSCODE](https://code.visualstudio.com) 进行compare selected进行对比。
------

#关于main
  
  +替换掉init里面的main文件。
>  在linux下 ，main文件是void main。在windows下，main是start，注意这个不同，不然会在编译的时候提示head.o有问题

-------
#关于process
  
  +建议把process.c放在hdc/usr/root里面，这样可以直接在boch下直接编译，即输入
    ``` shell
    gcc process.c -o process
    ./process
    ```
   +当然不要忘记在编译运行之后将文件同步到里面。
   ```shell
   sync
   ```
   +运行完上述以后，可以在在hdc/var下看到process.log，最好复制出来，我这边复制到oslab下，并且将stat_log.py一起放再oslab下。
       之后再oslab下的路径下，输入
     ```shell
     ./stat_log.py  ./process.log
      ```
    具体情况，该py文件会统计，（当然你也可以自己搞）。
    

    
