---
layout: post
title: 17. Content
nav_order: 99
parent: 17-滚动
---

*你可能想提前搜索的概念：滚动*

[zip](https://mhyc.eu.org/better-os-tutorial-cn/docs/17-滚动/Lesson17.zip)

**目标：文本到达底部时滚动屏幕**


对于这个简短的课程，打开 `drivers/screen.c` 。注意，在“printchar”的底部有一个新的部分（第84行），它检查当前偏移量是否超过屏幕大小并滚动文本。


实际的滚动由一个新函数`memory_copy`处理。它是标准 `memcpy` 的一个更简单的版本，但为了避免名称空间冲突，我们对它进行了不同的命名，至少目前是这样。打开 `kernel/util.c` 。看看它的实现。


为了帮助可视化滚动，我们还将实现一个函数，将整数转换为文本`int_To_ascii`。同样，它是标准“itoa”的快速实现。请注意，对于有两位数或更多的整数，它们是反向打印的。这是有意的。在以后的课程中，我们将扩展我们的助手函数，但这不是现在的重点。


最后，打开`kernel/kernel.c`。最初，每条线都显示其线号。您可以在第14行设置一个断点来确认这一点。然后，下面的“kprint”命令会强制内核向下滚动。


本课结束了对os-dev的报道。pdf文档。从现在开始，我们将关注[OSDev wiki](http://wiki.osdev.org/Meaty_Skeleton)以及其他来源和示例。感谢布伦德尔教授提供的精彩文件！