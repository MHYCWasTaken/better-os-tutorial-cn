---
layout: post
title: 06. Content
nav_order: 99
parent: 06-引导段
---

*开始之前你可能需要 Google 了解的概念：segmentation*

> segmentation : 段  
> 段是在程序中定义的用于包含数据，代码和堆栈的特定区域。  
> 在汇编编程中，程序需要访问存储器位置。 段内的所有存储器位置都相对于段的起始地址。 段开始于可被16或十六进制10整除的地址。因此，所有这些存储器地址中最右边的十六进制数字是0，通常不存储在段寄存器中。  
> 
> 段寄存器存储段的起始地址。 要获得段内数据或指令的确切位置，需要偏移值（或位移）。 为了引用段中的任何存储器位置，处理器将段寄存器中的段地址与位置的偏移值组合。   
> 来自iowiki
> 没太看懂？往下看

**目标: 学会使用 16 位实模式段编址内存**

如果你已经很熟悉实模式的段机制，可以直接跳过这个课程。

其实我们在课程 3 中已经使用过段寻址符号 `[org]` 。段意味着你可以通过使用偏移地址访问一个固定段中的数据。

这就是我们通常用的段寄存器： `cs`, `ds`, `ss` and `es`, 分别表示代码段，数据段，栈和其他（也就是，用户自定义）

请注意：  这些寄存器被处理器 *隐式* 的使用，因此你如果设置了这些寄存器。例如， `ds` 那么以后所有的数据地址都会以 `ds` 中的值为偏移基址。
[这里有更多信息](http://wiki.osdev.org/Segmentation)

而且，要计算真正的地址，我们不能简单将两个地址相加，而是需要 *组合它们* ： `segment << 4 + address`。例如，假设 `ds` 等于 `0x4d` 那么 `[0x20]` 实际上对应 `0x4d0 + 0x20 = 0x4f0`

这就是我们需要的基础理论，查阅代码并好好体会吧。

提示： 我们无法 `mov` 立即数到这些寄存器，只能通过通用寄存器对段寄存器赋值。

> 你看懂了吗？  
> 我看懂大概一点吧  
> cs ds ss es是段寄存器，等距分布在内存中，他们是处理器直接使用的（不用和你打报告）  
> 访问时使用特殊的计算方法计算地址  
> 没办法直接赋值，需要ax bx cx dx存上数据再给段寄存器  
> 数据存到ds可以代表org 数据