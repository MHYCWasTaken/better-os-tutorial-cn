*Concepts you may want to Google beforehand: IRQs, PIC, polling*

**Goal: Finish the interrupts implementation and CPU timer**

When the CPU boots, the PIC maps IRQs 0-7 to INT 0x8-0xF and IRQs 8-15 to INT 0x70-0x77. This conflicts with the ISRs we programmed last lesson. Since we programmed ISRs 0-31,  it is standard to remap the IRQs to ISRs 32-47.

The PICs are communicated with via I/O ports (see lesson 15). The Master PIC has command 0x20 and data 0x21, while the slave has command 0xA0 and data 0xA1.

The code for remapping the PICs is weird and includes some masks, so check [this article](http://www.osdev.org/wiki/PIC) if you're curious. Otherwise, just look at `cpu/isr.c`, new code after we set the IDT gates for the ISRs. After that, we add the IDT gates for IRQs.

Now we jump to assembler, at `interrupt.asm`. The first task is to add global definitions for the IRQ symbols we just used in the C code.  Look at the end of the `global` statements.

Then, add the IRQ handlers. Same `interrupt.asm`, at the bottom. Notice how they jump to a new common stub: `irq_common_stub` (next step)

We then create this `irq_common_stub` which is very similar to the ISR one. It is located at the top of `interrupt.asm`, and it also defines a new `[extern irq_handler]`

Now back to C code, to write the `irq_handler()` in `isr.c`. It sends some EOIs to the PICs and calls the appropriate handler, which is stored in an array named `interrupt_handlers` and defined at the top of the file. The new structs are defined in `isr.h`. We will also use a simple function to register the interrupt handlers.

That was a lot of work, but now we can define our first IRQ handler!

There are no changes in `kernel.c`, so there is nothing new to run and see. Please move on to the next lesson to check those shiny new IRQs.


*您可能希望提前搜索的概念：IRQ、PIC、轮询*


**目标：完成中断实现和CPU计时器**


当CPU引导时，PIC将IRQs 0-7映射到INT 0x8-0xF，IRQs 8-15映射至INT 0x70-0x77。这与我们上一课编程的ISR冲突。由于我们对ISR0-31进行了编程，所以将IRQ重新映射到ISR32-47是标准的。


通过I/O端口与PIC通信（参见第15课）。主PIC具有命令0x20和数据0x21，而从PIC具有指令0xA0和数据0xA1。


重新映射PIC的代码很奇怪，并且包含一些掩码，所以请查看[本文](http://www.osdev.org/wiki/PIC)如果你好奇的话。否则，只需看看`cpu/isr。c`，为ISR设置IDT门后的新代码。之后，我们为IRQ添加IDT门。


现在我们跳到汇编程序，在`interrupt.asm`。第一个任务是为我们刚刚在C代码中使用的IRQ符号添加全局定义。看看“global”语句的结尾。


然后，添加IRQ处理程序。相同`interrupt。asm`，在底部。注意它们如何跳转到一个新的公共存根：`irq_common_stub`（下一步）


然后我们创建这个`irq_common_stub`，它与ISR非常相似。它位于“interrupt”的顶部。asm`，它还定义了一个新的`[extern irqhandler]`


现在回到C代码，在`isr.C`中编写`irq_handler（）`。它向PIC发送一些EOI并调用相应的处理程序，该处理程序存储在名为“interrupt_handlers”的数组中，并在文件顶部定义。新结构在“isr.h”中定义。我们还将使用一个简单的函数来注册中断处理程序。


这需要做很多工作，但现在我们可以定义第一个IRQ处理程序了！


`kernel中没有更改。c`，所以没有新的东西可以运行和查看。请继续下一课，检查那些闪亮的新IRQ。