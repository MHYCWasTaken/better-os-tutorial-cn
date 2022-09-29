*Concepts you may want to Google beforehand: C types and structs, include guards, type attributes: packed, extern, volatile, exceptions*

**Goal: Set up the Interrupt Descriptor Table to handle CPU interrupts**

This lesson and the following ones have been heavily inspired
by [JamesM's tutorial](https://web.archive.org/web/20160412174753/http://www.jamesmolloy.co.uk/tutorial_html/index.html)

Data types
----------

First, we will define some special data types in `cpu/types.h`, which will help us uncouple data structures for raw bytes from chars and ints. It has been carefully placed on the `cpu/` folder, where we will put machine-dependent code from now on. Yes, the boot code is specifically x86 and is still on `boot/`, but let's leave that alone for now.

Some of the already existing files have been changed to use the new `u8`, `u16` and `u32` data types.

From now on, our C header files will also have include guards.


Interrupts
----------

Interrupts are one of the main things that a kernel needs to  handle. We will implement it now, as soon as possible, to be able to receive keyboard input in future lessons.

Another examples of interrupts are: divisions by zero, out of bounds, invalid opcodes, page faults, etc.

Interrupts are handled on a vector, with entries which are similar to those of the GDT (lesson 9). However, instead of programming the IDT in assembly, we'll do it in C.

`cpu/idt.h` defines how an idt entry is stored `idt_gate` (there need to be 256 of them, even if null, or the CPU may panic) and the actual idt structure that the BIOS will load, `idt_register` which is just a memory address and a size, similar to the GDT register.

Finally, we define a couple variables to access those data structures from assembler code.

`cpu/idt.c` just fills in every struct with a handler.  As you can see, it is a matter of setting the struct values and calling the `lidt` assembler command.


ISRs
----

The Interrupt Service Routines run every time the CPU detects an  interrupt, which is usually fatal. 

We will write just enough code to handle them, print an error message, and halt the CPU.

On `cpu/isr.h` we define 32 of them, manually. They are declared as `extern` because they will be implemented in assembler, in `cpu/interrupt.asm`

Before jumping to the assembler code, check out `cpu/isr.c`. As you can see, we define a function to install all isrs at once and load the IDT, a list of error messages, and the high level handler, which kprints some information. You can customize `isr_handler` to print/do whatever you want.

Now to the low level which glues every `idt_gate` with its low-level and high-level handler. Open `cpu/interrupt.asm`. Here we define a common low level ISR code, which basically saves/restores the state and callsthe C code, and then the actual ISR assembler functions which are referencedon `cpu/isr.h`

Note how the `registers_t` struct is a representation of all the registers we pushed in `interrupt.asm`

That's basically it. Now we need to reference `cpu/interrupt.asm` from our Makefile, and make the kernel install the ISRs and launch one of them. Notice how the CPU doesn't halt even though it would be good practice to do it after some interrupts.


*你可能想提前搜索的概念：C类型和结构，包括保护，类型属性：packed，extern，volatile，exceptions*


**目标：设置中断描述符表以处理CPU中断**


这节课和下面的课受到了很大的启发

作者：[JamesM的教程](https://web.archive.org/web/20160412174753/http://www.jamesmolloy.co.uk/tutorial_html/index.html)


数据类型
----------

首先，我们将在 `cpu/types.h` 中定义一些特殊的数据类型 ，它将帮助我们从字符和int中分离出原始字节的数据结构。它已经被小心地放在了 `cpu/` 文件夹中，从现在开始，我们将把依赖于机器的代码放在那里。是的，引导代码是专门的x86，并且仍然在 `boot/` 上，但我们暂时不谈这个问题。

一些现有文件已更改为使用新的 `u8` 、 `u16` 和 `u32` 数据类型。

从现在起，我们的C头文件也将包含保护。



中断
----------


中断是内核需要处理的主要内容之一。我们现在将尽快实现它，以便在以后的课程中能够接收键盘输入。

中断的另一个例子是：被零除、越界、无效操作码、页面错误等。

中断在向量上处理，其条目与GDT的条目类似（第9课）。然而，我们将用C来代替在汇编中编程IDT。

`cpu/idt.h` 定义idt项的存储方式 `idt_gate` （需要256个，即使为空，否则CPU可能死机）以及BIOS将加载的实际idt结构 `idt_register` ，它只是内存地址和大小，类似于GDT寄存器。


最后，我们定义了两个变量来从汇编代码访问这些数据结构。


`cpu/idt.c` 只是用一个处理程序填充每个结构。正如您所看到的，这是一个设置struct值并调用 `lidt` 汇编命令的问题。



ISR
----

每次CPU检测到中断（通常是致命的）时，中断服务例程都会运行。

我们将编写足够的代码来处理它们，打印错误消息，并停止CPU。

打开 `cpu/isr.h` ,我们手动定义了其中的32个。它们被声明为“extern”，因为它们将在 `cpu/internrupt.asm` 中的汇编程序中实现


在跳转到汇编代码之前，请查看 `cpu/isr.c` 。如您所见，我们定义了一个函数来一次性安装所有isr，并加载IDT、错误消息列表和高级处理程序，后者打印一些信息。您可以自定义 `isr_handler` 以打印/执行任何您想要的操作。


现在是将每个 `idt_gate` 与其低级和高级处理程序粘合在一起的低级。打开 `cpu/interrup.asm` 。这里我们定义了一个通用的低级ISR代码，它基本上保存/恢复状态并调用C代码，然后是在 `cpu/ISR.h` 上引用的实际ISR汇编函数


请注意，`registers_t` 结构如何表示我们在 `interrupt.asm` 中推入的所有寄存器


基本上就是这样。现在我们需要引用 `cpu/interrup.asm` 从我们的Makefile，让内核安装ISR并启动其中一个。请注意CPU是如何不停止的，即使在一些中断之后这样做也是一种好的做法。