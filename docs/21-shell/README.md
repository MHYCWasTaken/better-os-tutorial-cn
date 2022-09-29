
**Goal: Clean the code a bit and parse user input**

In this lesson we will do two things. First, we will clean up the code a bit, so it is ready for further lessons. During the previous ones I tried to put things in the most predictable places, but it is also a good exercise to know when the code base is growing and adapt it to current and further needs.


Code cleaning
-------------

First of all, we will quickly start to need more utility functions for handling strings and so on. In a regular OS, this is called the C library, or libc for short.

Right now we have a `utils.c` which we will split into `mem.c` and `string.c`, with their respective headers.

Second, we will create a new function `irq_install()` so that the kernel only needs to perform one call to initialize all the IRQs. That function is akin to `isr_install()` and placed on the same `irq.c`. While we're here, we will disable the `kprint()` on `timer_callback()` to avoid filling the screen with junk, now that we know that it works properly.

There is not a clear distinction between `cpu/` and `drivers/`. Keep in mind that I'm creating this tutorial while following many others, and each of them has a distinct folder structure. The only change we will do for now is to move `drivers/ports.*` into `cpu/` since it is clearly cpu-dependent code. `boot/` is also CPU-dependent code, but we will not mess with it until we implement the boot sequence for a different machine.

There are more switches for the `CFLAGS` on the `Makefile`, since we will now start creating higher-level functions for our C library and we don't want the compiler to include any external code if we make a mistake with a declaration. We also added some flags to turn warnings into errors, since an apparently minor mistake converting pointers can blow up later on. This also forced us to modify some misc pointer declarations in our code.

Finally, we'll add a macro to avoid warning-errors on unused parameters on `libc/function.h`

Keyboard characters
-------------------

How to access the typed characters, then?

- When a key is pressed, the callback gets the ASCII code via a new arrays which are defined at the beginning of `keyboard.c`
- The callback then appends that character to a buffer, `key_buffer`
- It is also printed on the screen
- When the OS wants to read user input, it calls `libc/io.c:readline()`

`keyboard.c` also parses backspace, by removing the last element of the key buffer, and deleting it from the screen, by calling  `screen.c:kprint_backspace()`. For this we needed to modify a bit `print_char()` to not advance the offset when printing a backspace


Responding to user input
------------------------

The keyboard callback checks for a newline, and then calls the kernel, telling it that the user has input something. Out final libc function is `strcmp()`, which compares two strings and returns 0 if they are equal. If the user inputs "END", we halt the CPU.

This is the most basic shell ever, but you should be proud, because we implemented it from scratch. Do you realize how cool this is?

If you want to, expand `kernel.c` to parse more stuff. In the future, when we have a filesystem, we will allow the user to run some basic commands.

**目标：稍微清理代码并解析用户输入**


在本课中，我们将做两件事。首先，我们将稍微清理代码，以便为进一步的课程做好准备。在前几次测试中，我试图把东西放在最容易预测的地方，但了解代码库何时增长并使其适应当前和未来的需求也是一个很好的练习。



代码清理

-------------


首先，我们将很快开始需要更多的实用函数来处理字符串等。在常规操作系统中，这称为C库，简称libc。


现在我们有一个`utils。我们将把它分成mem。c`和`string。c `，带有各自的标题。


其次，我们将创建一个新函数`irq_install（）`，这样内核只需执行一个调用即可初始化所有irq。该函数类似于“isr_install（）”，并放在同一个“irq.c”中。在这里，我们将禁用`timer_callback（）`上的`kprint（）`，以避免用垃圾填充屏幕，因为我们知道它可以正常工作。


`cpu/`和`drivers/`之间没有明确的区别。请记住，我在创建本教程的同时遵循了许多其他教程，并且每个教程都有一个不同的文件夹结构。我们现在要做的唯一更改是移动“驱动程序/端口.*`”因为它显然是依赖于cpu的代码`boot/`也是依赖CPU的代码，但在为不同的机器实现引导序列之前，我们不会弄乱它。


“Makefile”上的“CFLAGS”有更多开关，因为我们现在将开始为C库创建更高级的函数，并且如果我们在声明中出错，我们不希望编译器包含任何外部代码。我们还添加了一些标志来将警告转化为错误，因为转换指针时出现的一个明显的小错误可能会在以后爆发。这也迫使我们修改代码中的一些杂项指针声明。


最后，我们将添加一个宏，以避免`libc/function.h上未使用的参数出现警告错误`


键盘字符

-------------------


那么，如何访问键入的字符？


-当按下某个键时，回调函数通过在`keyboard.c开头定义的新数组获取ASCII代码`

-然后回调将该字符附加到缓冲区`key_buffer`

-它也打印在屏幕上

-当操作系统想要读取用户输入时，它调用`libc/io.c:readline（）`


`键盘。c`还解析退格，方法是删除键缓冲区的最后一个元素，并通过调用`screen.c:kprint_backspace（）`将其从屏幕上删除。为此，我们需要修改位“print_char（）”，以便在打印退格时不提前偏移量



响应用户输入

------------------------


键盘回调检查换行符，然后调用内核，告诉它用户输入了一些东西。输出的最后一个libc函数是`strcmp（）`，它比较两个字符串，如果相等，则返回0。如果用户输入“END”，我们将停止CPU。


这是有史以来最基本的shell，但您应该感到自豪，因为我们从头开始实现它。你知道这有多酷吗？


如果需要，请展开`kernel。c来解析更多内容。将来，当我们有文件系统时，我们将允许用户运行一些基本命令。