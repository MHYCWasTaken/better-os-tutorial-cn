---
layout: default
title: Lesson 10 - 32bit-switch.asm
nav_order: 99
parent: Lesson 10
---
```nasm
[bits 16]
switch_to_pm:
    cli ; 1. 禁用中断
    lgdt [gdt_descriptor] ; 2. 加载GDT描述符
    mov eax, cr0
    or eax, 0x1 ; 3. 在cr0中设置32位模式
    mov cr0, eax
    jmp CODE_SEG:init_pm ; 4. 使用不同的分段进行跳远

[bits 32]
init_pm: ; 我们现在使用32位指令
    mov ax, DATA_SEG ; 5. 更新段寄存器 
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; 6. 在自由空间顶部更新堆栈
    mov esp, ebp

    call BEGIN_PM ; 7. 使用有用的代码调用知名标签
```