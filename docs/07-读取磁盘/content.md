---
layout: post
title: 07. Content
nav_order: 99
parent: 07-读取磁盘
---

*您可能需要事先搜索的概念：硬盘、柱面、磁头、扇区、进位*


**目标：让引导扇区从磁盘加载数据以引导内核**


512字节可放不下我们的系统，因此我们需要引导程序来运行放有内核的硬盘


谢天谢地，我们不需要手动操作硬盘磁头的旋转与否

BIOS提供了一套工具，我们可以直接使用，就和打印字符一样

为此，我们将‘al’设置为‘0x02’（以及其他有会用到的柱面，磁头，扇区的寄存器）并提升“int 0x13”`

您可以访问[此处的详细int 13h指南](http://stanislavs.org/helppc/int_13-2.html)

> 奥看来这是个类似文档的东西,告诉你调用时参数存在哪里以及返回什么  
> 这是传入
> > AH = 02  
> > AL = 要读的扇区	(1-128 dec.)   
> > CH = 磁道/柱面号码  (0-1023 dec., see below)    
> > CL = 扇区号码  (1-17 dec.)  
> > DH = 磁头  (0-15 dec.)  
> > DL = 驱动器号码 (0=A:, 1=2nd floppy, 80h=drive 0, 81h=drive 1)  
> > ES:BX = 缓存指针  
>
> 传出
>
> > 返回时:  
> > AH = 状态  (祥见 [INT 13,STATUS](https://stanislavs.org/helppc/int_13-1.html))  
> > AL = 读的扇区号码  
> > CF = 0 成功  
> >    = 1 错误  
>
> 还有一些小提示
>
> > - BIOS 磁盘读取应至少重试 3 次，并且控制器应在检测到错误时复位  
> > - 确保 ES:BX 不跨越 64K 段边界否则将发生 DMA 边界错误  
> > - 许多编程参考仅列出软盘寄存器值（这句没看懂）  
> > - 仅检查磁盘号的有效性  
> > - CX 中的参数根据柱面数而变化；  磁道/柱面编号是取自 CL 的 2 个高位和 CH 中的 8 位（轨道的低 8 位）的 10 位值：  
> > ```
> >|F|E|D|C|B|A|9|8|7|6|5-0|  CX  
> >·| | | | | | | | | | ↑-----	扇区号  
> >·| | | | | | | | ↑---------  高位 2 位磁道/柱面  
> >··↑------------------------  低位 8 位磁道/柱面号   
> > ```
> > - 见 [INT 13,A](https://stanislavs.org/helppc/int_13-a.html)


在本课中，我们将首次使用*进位*，这是一个额外的位，每个寄存器上都有，当操作溢出其容量时，该寄存器进行存储

```nasm
mov ax, 0xFFFF
add ax, 1  ; ax = 0x0000 and carry = 1
; 进行了一个加法的运算，但0xFFFF已经最大，在加一就会归零并将进位寄存器标记为1
```


进位不被直接访问，而是被其他操作员用作控制结构，

类似于“jc”（如果进位被设置，则跳转）


BIOS还将“al”设置为读取的扇区数，因此始终将其与预期数进行比较。



代码

----


打开并检查 `boot_sect_disk.asm` 对于完整的例程从磁盘读取。

`boot_sect_disk.asm` 为磁盘读取准备参数并调用 `disk_load` 。

注意，我们如何编写一些实际上不属于启动的额外数据

因为它在512位标记之外。


引导扇区实际上是扇区1（第一个扇区从1开始）

hdd 0的磁头0的柱面0。


因此，字节512之后的任何字节对应于hdd 0的磁头0的柱面0的扇区2


主例程将用样本数据填充它，然后让引导扇区

读代码吧。

**注意：如果不断出现错误，并且代码看起来很好，请确保qemu

正在从右驱动器启动，并相应地将驱动器设置为“dl”**

> 正确的输出应该是0xDADA和0xFACE


BIOS在调用引导加载程序之前将“dl”设置为驱动器号。然而

从硬盘启动时，我发现qemu存在一些问题。


有两个快速选项：


1.尝试标记 `-fda` ，例如，`qemu-fda boot_sect_main.bin` 将设置 `dl` 设置为 0x00，看起来工作的很好

2.显式使用标志 `-boot` ，例如 ` qemu boot_sect_main.bin -boot c` 会自动将“dl”设置为“0x80”，并允许引导加载程序读取数据

> 如果你遇到了这样的问题，那你只能自己解决了，我没能成功复现出这个问题