---
layout: post
title: 02. Content
nav_order: 99
parent: 02-引导打印
---

*开始之前你可能需要 Google 了解的概念：interrupts, CPU
registers*

> interrupts : 中断 打断CPU执行的事件  
> CPU : 中央处理器  
> registers : 寄存器，CPU中的存储器  

**目的： 让之前的引导程序输出一些文本**

我们对之前的无限循环引导扇区做点改进，让它能够打印点东西在屏幕上。我们通过发出中断来完成这个功能。

在这个例子中我们将会向寄存器 `al` (`ax` 的低端部分) 写入 “hello” 单词的每个字符，把 `0x0e`
写入 `ah` (`ax` 的高端部分) 然后发出中断 `0x10`，这是视频服务的通用中断。

> ah是累加器ax的高8位（high），al是ax的低8位（low），ah和al均可以单独作为8位寄存器使用。  
> 可以理解为一个寄存器的一个部分
>
> 2022-9-9-19:12更新：  
> 转自 https://iowiki.com/assembly_programming/assembly_registers.html  
> 四个32位数据寄存器用于算术，逻辑和其他操作。 这些32位寄存器可以三种方式使用 -  
> - 作为完整的32位数据寄存器:EAX，EBX，ECX，EDX。 
> - 32位寄存器的下半部分可用作4个16位数据寄存器:AX，BX，CX和DX。 
> - 上述四个16位寄存器的低半部分和高半部分可用作8个8位数据寄存器:AH，AL，BH，BL，CH，CL，DH和DL。
> ![来自iowiki图片](../../assets/images/register1.jpg)  
> 这张图片非常清晰明白，看着他可以方便的理解之后一段时间内的许多原理

`0x0e` 写入 `ah` 告诉视频中断我们想要以 tty 模式显示 `al` 寄存器中的内容。

> tty ： 文本模式

我们只会设置 tty 模式一次尽管实际上我们不能保证 `ah` 中的内容是不变的。在我们的程序休眠的时候，其他的进程可能仍然在 CPU 上执行，也许它们没有正确的清空 `ah` 甚至遗留一些垃圾数据在里面。

在这个例子中，我们不需要考虑这个问题，因为我们的引导扇代码是唯一能够在 CPU 上执行的程序。

我们的新引导扇区代码看起来是这个样子：

```nasm
mov ah, 0x0e ; 进入tty模式
mov al, 'H'  ; mov a, b 表示从a处写一个b
int 0x10     ; tty模式下执行0x10代表树池这个字符
mov al, 'e'
int 0x10
mov al, 'l'
int 0x10
int 0x10     ; 我们输出的是al上的字符，而al未改变，所以依旧输出l
mov al, 'o'
int 0x10

jmp $        ; $代表当前地址，跳转至自己=无限循环
; 自己试一试，这个 jmp $ 去掉似乎并无影响

; 这样看$$应该是扇区开头的地址（猜测）
times 510 - ($-$$) db 0
; 咒语
dw 0xaa55 
```

>为了方便，你可以创建一个bat程序 `compile_and_run.bat` ：  
>```
>set s=%1
>echo %s%
>.\NASM\nasm.exe -f bin .\%s%.asm -o .\%s%.bin
>.\qemu-win\qemu-system-x86_64.exe .\%s%.bin
>```
>放置在 `W:\os` 里面  
>运行时右键开启控制台并执行 `.\compile_and_run.bat file_name`  
>file_name不加后缀名  

你可以使用 `xxd file.bin` 命令检查二进制数据

当然你已经知道我们的编译和运行步骤：

`nasm -fbin boot_sect_hello.asm -o boot_sect_hello.bin`

`qemu boot_sect_hello.bin`

现在你的启动引导程序会打印 'Hello' 然后停止在无限循环中。

> 那么这样来看asm语言似乎不是从上至下运行