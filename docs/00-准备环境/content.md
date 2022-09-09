---
layout: default
title: Lesson 00 - Content
nav_order: 99
parent: Lesson 00
---

*开始之前你可能需要了解的概念：linux, mac, terminal, compiler, emulator, nasm, qemu*


>
>概念列表：
>- linux : 三大操作系统之一，开源免费，拥有极其多的分支
>- mac : 苹果电脑
>- terminal : 终端，是一个黑框框，运行一些指令后会打印日志，通常情况下终端会比图形化界面更加强大
>- compiler : 编译器，写的代码需要先编译成计算机可以识别的文件形式才能运行，当然也有解释性的语言，无需产生编译文件即可运行，例如Python
>- emulator : 想在电脑上玩FC游戏？使用Emulator吧！Emulator是一种虚拟机，但是一般运行较为古早的系统
>- nasm : 本项目过程中需要使用的编译器，负责编译  
>- qemu : 本项目中使用的Emulator  


## 目的：安装运行教程代码所需要的软件

我在一台 Mac 电脑上工作，但是 Linux 是一个更好的选择因为 Linux 一般都提供了你需要的标准工具。

在 Mac 上， [安装 Homebrew](http://brew.sh) 然后运行 `brew install qemu nasm`

如果你已经安装了 Xcode ，不要使用开发工具里面的 `nasm` ，大多数情况下，这个程序都没办法正常工作，我们会一直使用 `/usr/local/bin/nasm`

在有些系统上 qemu 分成好几个二进制文件，你可能会使用 `qemu-system-x86_64 binfile`


>
>如果你在Windows上使用，请随我来  
>*因为lincence的原因，我无法将配置好的环境上传，见谅*  
>分别前往 [nasm官网的下载列表](https://www.nasm.us/pub/nasm/releasebuilds/?C=M;O=D) 和 [qemu的官网下载列表](https://www.qemu.org/download/#windows) 获取安装包，尽可能选择32bit版本
>完成后安装，请将两个软件装到离工作区较近的地方  
>例如我将其分别安装至 `W:\os\NASM` 和 `W:\os\qemu-windows` 尽量不要出现嵌套文件夹  
>完成后文件结构应该像这样:  
>os  
>|  
>| NASM  
>| | VSrules  
>| | ldrdf.exe  
>| | ......  
>| | Unistall.exe  
>|  
>| qemu-windows  
>| | lib  
>| | share  
>| | ......  
>| | zlib1.dll  
>|  
>你已经完成了，编译和运行等内容将之后讲解  

