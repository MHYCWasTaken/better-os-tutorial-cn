---
layout: post
title: 14. Content
nav_order: 99
parent: 14-休息一下
---


*您可能想提前搜索的概念：单片内核、微内核、调试器、gdb*


**目标：稍稍暂停并组织我们的代码。然后学习如何使用gdb调试内核**


也许您没有意识到，但您已经有了自己的内核

跑步


然而，它做得很少，只打印一个“X”。现在是时候停下来了

稍后，将代码组织到文件夹中，为将来的代码创建一个可伸缩的Makefile，

并考虑一个策略。


看看新的文件夹结构。大多数文件都有符号链接

因此，如果我们必须在某个时候改变它们

删除符号链接并创建新文件的更好方法。


此外，从现在起，我们将主要使用C来编码，我们将利用qemu的

能够打开到gdb的连接。首先，让我们安装一个交叉编译的`gdb`，因为

> 非常抱歉，我没能成功搭建gdb，如果可以，请自行研究，原文英文版附上  
> ~~debug功能暂时用不到罢。。。~~  
> 不过貌似和我编译gcc时使用i686有关系。。。  
> 不管怎样，到这里回头都有难度了  
> [本课zip(记得改makefile)(压缩的是未注解版本，因为就改了文件结构和makefile)](https://mhyc.eu.org/better-os-tutorial-cn/docs/14-休息一下/Lesson14.zip)

```sh
cd /tmp/src
curl -O http://ftp.rediris.es/mirror/GNU/gdb/gdb-7.8.tar.gz
tar xf gdb-7.8.tar.gz
mkdir gdb-build
cd gdb-build
export PREFIX="/usr/local/i386elfgcc"
export TARGET=i386-elf
../gdb-7.8/configure --target="$TARGET" --prefix="$PREFIX" --program-prefix=i386-elf-
make
make install
```

Check out the Makefile target `make debug`. This target uses builds `kernel.elf`, which
is an object file (not binary) with all the symbols we generated on the kernel, thanks to
the `-g` flag on gcc. Please examine it with `xxd` and you'll see some strings. Actually,
the correct way to examine the strings in an object file is by `strings kernel.elf`

We can take advantage of this cool qemu feature. Type `make debug` and, on the gdb shell:

- Set up a breakpoint in `kernel.c:main()`: `b main`
- Run the OS: `continue`
- Run two steps into the code: `next` then `next`. You will see that we are just about to set
  the 'X' on the screen, but it isn't there yet (check out the qemu screen)
- Let's see what's in the video memory: `print *video_memory`. There is the 'L' from "Landed in
  32-bit Protected Mode"
- Hmmm, let's make sure that `video_memory` points to the correct address: `print video_memory`
- `next` to put there our 'X'
- Let's make sure: `print *video_memory` and look at the qemu screen. It's definitely there.

Now is a good time to read some tutorial on `gdb` and learn super useful things like `info registers`
which will save us a lot of time in the future!


You may notice that, since this is a tutorial, we haven't yet discussed which kind
of kernel we will write. It will probably be a monolithic one since they are easier
to design and implement, and after all this is our first OS. Maybe in the future
we'll add a lesson "15-b" with a microkernel design. Who knows.