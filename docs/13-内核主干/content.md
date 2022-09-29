---
layout: post
title: 13. Content
nav_order: 99
parent: 13-内核主干
---
*你可能想提前谷歌的概念：内核、ELF格式、makefile*

> ELF文件格式 : Executable and Linkable Format, 可执行，可链接的文件格式
> makefile : make的配置文件，具体之后讲

**目标：创建一个简单的内核和一个能够引导它的引导扇区**


内核
----------


我们的C内核只会在屏幕左上角打印一个“X”。

着手并打开 `kernel.c` 。

您将注意到一个不执行任何操作的伪函数。该函数将强制我们创建一个内核入口例程，该例程不指向内核中的字节0x0，而是指向一个实际的标签，我们知道该标签会启动它。在我们的例子中，函数 `main()` 。

`i386-elf-gcc -ffreestanding -c kernel.c -o kernel.o`

该例程编码在 `kernel_entry.asm` 上。阅读本文，您将了解如何在程序集中使用 `[extern]` 声明。为了编译这个文件，我们将生成一个“elf”格式的文件，该文件将与“kernel.o”链接，而不是生成二进制文件`

`nasm kernel_entry.asm -f elf -o kernel_entry.o`

链接器
----------

链接器是一个非常强大的工具，我们才开始从中受益。

要将两个对象文件链接到单个二进制内核并解析标签引用，

运行：

`i386-elf-ld -o kernel.bin -Ttext 0x1000 kernel_entry.o kernel.o --oformat binary`

请注意，我们的内核将不是放在内存中的“0x0”位置，而是放在“0x1000”位置。bootsector也需要知道这个地址。


引导扇区
--------------


它与第10课中的非常相似。打开 `bootsect.asm` 并检查代码。

事实上，如果你把屏幕上用来打印信息的所有行都去掉，它就占了几十行。

编译: `nasm bootsect.asm -f bin -o bootsect.bin`


把所有这些放在一起
-----------------------


现在怎么办？我们有两个单独的文件用于引导扇区和内核？


我们不能把它们“链接”到一个文件中吗？是的，我们可以，而且很容易，

只需将它们连接起来：

`cat bootsect.bin kernel.bin > os-image.bin`

> cat是linux自带的链接器


跑
----


现在可以运行 `os-image.bin` 用qemu。


请记住，如果发现磁盘加载错误，可能需要使用磁盘编号或qemu参数（软盘=`0x0`，硬盘=`0x80`）。

我通常使用 `qemu-system-i386-fda os-image.bin`


您将看到四条消息：

- "Started in 16-bit Real Mode"
- "Loading kernel into memory"
- (左上角) "Landed in 32-bit Protected Mode"
- (左上角，覆盖上一条消息) "X"


恭喜



Makefile

--------


最后，我们将使用Makefile整理编译过程。打开`Makefile`

编写脚本并检查其内容。如果你不知道Makefile是什么，现在正是时候去谷歌学习，因为这将在未来节省我们很多时间。

> 真的非常的方便并且快捷，上述那么多条命令可以仅由一句代替：  
> ```sh
> make
> ```
> 具体的makefile可以去搜索学习 ~~（其实是我没看懂）~~  
> 删除所有构建的文件和中间文件可以运行 ```make clean```  
> 运行qemu使用 ```make run```  
> 唯一缺点是新建其他文件时均需要改动makefile
  

> 另，此之后的代码会打包并给出链接，因为我们的代码量越来越大，不是复制一两个文件能弄好的了
> [链接](https://mhyc.eu.org/better-os-tutorial-cn/docs/13-内核主干/Lesson13.zip)