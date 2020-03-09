要将iam.c和whoami.c挂到hdc里面的root下面
在terminal上的~/oslab下输入
sudo ./mounr-hdc进入后，可以在/oslab的图形界面上点击hdc进入将iam.c和whoami.c复制进去。也可以在termial上用
cp [选项] 源文件目录  目标目录进行 复制。
记得在该虚拟路径下顺便更改unist.h里面的  72 73。
之后
sudo umount hdc
************************************************************************
对于who.c要复制在kernel上。