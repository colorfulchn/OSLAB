直接将本文件的三个文件替换掉boot里面的文件即可。

在给定的boch运行环境下。
点击MinGW32弹出命令窗口。用cd指令找到boot的路径下，
as86 -0 -a -o bootsect.o bootsect.s
    ld86 -0 -s -o bootsect bootsect.o
编译bootsect。
make BootImage 制作BootImage
之后点run。

在LAB1中。int 0x10 中的10号中断表示将#msg弹在屏幕上。
