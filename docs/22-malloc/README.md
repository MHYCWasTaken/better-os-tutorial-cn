*Concepts you may want to Google beforehand: malloc*

> malloc : C中申请内存，与之相对的是free

**Goal: Implement a memory allocator**

We will add a kernel memory allocator to `libc/mem.c`. It is implemented as a simple pointer to free memory, which keeps growing.

The `kmalloc()` function can be used to request an aligned page, and it will also return the real, physical address, for later use.

We'll change the `kernel.c` leaving all the "shell" code there, Let's just try out the new `kmalloc()`, and check out that our first page starts at 0x10000 (as hardcoded on `mem.c`) and subsequent `kmalloc()`'s produce a new address which is aligned 4096 bytes or 0x1000 from the previous one.

Note that we added a new `strings.c:hex_to_ascii()` for nicer printing of hex numbers.

Another cosmetic modification is to rename `types.c` to  `type.c` for language consistency.

The rest of the files are unchanged from last lesson.

**目标：实现内存分配器**


我们将在`libc/mem.c`中添加一个内核内存分配器。它是作为一个指向空闲内存的简单指针实现的，空闲内存不断增长。


函数“kmalloc（）”可用于请求对齐的页面，它还将返回实际的物理地址，供以后使用。


我们将更改`kernel。c把所有的“shell”代码都放在那里，让我们试试新的`kmalloc（）`，看看我们的第一页是从0x10000开始的（硬编码在`mem.c`上），随后的`kmall（）`会产生一个新地址，它与前一个地址对齐4096字节或0x1000。


注意，我们添加了一个新的`strings。c： hex_to_ascii（）`更好地打印十六进制数字。


另一个修饰性修改是重命名`types。c`to`type。c表示语言一致性。


其余文件与上一课相同。