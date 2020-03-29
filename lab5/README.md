# 挂载虚拟硬盘中修改文件
-----------------
+ 需要在hdc/usr/include下把unistd.h替换掉对应的文件，当然直接在挂载下进行修改也可以的。
+ 在hdc/usr/include/linux下sem.h
+ pc.c放在hdc/usr/root

# sys.h
-----------
+ 直接替换掉，或者添加extern和下面的文件。

# makefile of kernel
-------
+ 按照描述修改即可

# system_call.s
------------
+ 需要修改其中的72改为76。

# 在linux-0.11下进行的
-----------
```
gcc pc.c -o pc
./pc > 1.txt
sync
``` 

# 查看输出文件
-----------
```
sudo ./mount-hdc
sudo cp ./hdc/usr/root/1.txt ./
sudo chmod 777 1.txt
```
+ 这样就可以点开看了或者使用`cat 1.txt`