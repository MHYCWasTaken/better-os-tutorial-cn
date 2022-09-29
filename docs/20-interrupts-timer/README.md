*Concepts you may want to Google beforehand: CPU timer, keyboard interrupts, scancode*

**Goal: Implement our first IRQ handlers: the CPU timer and the keyboard**

Everything is now ready to test our hardware interrupts.

Timer
-----

The timer is easy to configure. First we'll declare an `init_timer()` on `cpu/timer.h` and implement it on `cpu/timer.c`. It is just a matter of computing the clock frequency and sending the bytes to the appropriate ports.

We will now fix `kernel/utils.c int_to_ascii()` to print the numbers in the correct order. For that, we need to implement `reverse()` and `strlen()`.

Finally, go back to the `kernel/kernel.c` and do two things. Enable interrupts again (very important!) and then initialize the timer interrupt.

Go `make run` and you'll see the clock ticking!


Keyboard
--------

The keyboard is even easier, with a drawback. The PIC does not send us the ASCII code for the pressed key, but the scancode for the key-down and the key-up events, so we will need to translate those.

Check out `drivers/keyboard.c` where there are two functions: the callback and the initialization which configures the interrupt callback. A new `keyboard.h` was created with the definitions.

`keyboard.c` also has a long table to translate scancodes to ASCII keys. For the time being, we will only implement a simple subset of the US keyboard. You can read more [about scancodes here](http://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html)

I don't know about you, but I'm thrilled! We are very close to building a simple shell.
In the next chapter, we will expand a little bit on keyboard input


*你可能想提前搜索的概念：CPU定时器、键盘中断、扫描码*


**目标：实现我们的第一个IRQ处理器：CPU定时器和键盘**


现在一切都准备好测试硬件中断了。


计时器

-----


定时器易于配置。首先，我们将在`cpu/timer上声明一个`init_timer（）`。h`并在`cpu/timer.c`上实现它。这只是一个计算时钟频率并将字节发送到适当端口的问题。


现在我们将修复`kernel/utils。c int_to_ascii（）`以正确的顺序打印数字。为此，我们需要实现`reverse（）`和`strlen（）`。


最后，回到`kernel/kernel。然后做两件事。再次启用中断（非常重要！）然后初始化定时器中断。


去跑步吧，你会看到时钟在滴答作响！



键盘

--------


键盘更简单，但有一个缺点。PIC不会向我们发送按下键的ASCII代码，而是发送向下键和向上键事件的扫描代码，因此我们需要翻译这些代码。


查看“驱动程序/键盘”。其中有两个函数：回调和配置中断回调的初始化。一个新的键盘。h`是用定义创建的。


`键盘。c`还有一个长表，用于将scancodes转换为ASCII键。目前，我们只实现美国键盘的一个简单子集。您可以在此处阅读更多[关于scancodes的信息](http://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html）


我不知道你的情况，但我很激动！我们非常接近于建造一个简单的外壳。

在下一章中，我们将对键盘输入进行一些扩展