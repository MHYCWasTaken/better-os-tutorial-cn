---
layout: default
title: Lesson 04 - boot_sect_stack.asm
nav_order: 99
parent: Lesson 04
---
```nasm
mov ah, 0x0e ; tty mode

mov bp, 0x8000 ; 在离0x7c00很远的地方开一个栈，bp是栈底
mov sp, bp     ; 栈是空的，所以bp和sp在一起

push 'A'
push 'B'
push 'C'
; 很方便吧，谁能想到c++的STL这里居然已经封装好了呢
; (这个说法十分不严谨，请不要当真)

; 打印bp到bp-2位置（一个字符占两个byte）的内容，展示栈向下生长
; 这段代码打印A
mov al, [0x7ffe] ; 0x8000 - 2 等于 0x7ffe
int 0x10


; 打印bp不起作用，因为asm的栈的栈底没有数据
; 第一个数据（A）在0x7ffe
mov al, [0x8000]
int 0x10


; pop命令将栈顶向上移动一位，也就是取出一颗曼妥思
; 猜测：曼妥思并未被取出，只是被标记为了无用，看不见了
; 结合lesson1的寄存器图片，bx是一个16位的寄存器
; pop会将一个不知道什么的8位数据（有人知道欢迎issue告诉我）+pop出来的栈顶内容返回至指定位置，这里是bx
pop bx
mov al, bl
int 0x10 ; prints C

pop bx
mov al, bl
int 0x10 ; prints B

pop bx
mov al, bl
int 0x10 ; prints A

; 没pop出来的数据没有用了（这个例子中都pop出来了）
mov al, [0x8000]
int 0x10


jmp $
times 510-($-$$) db 0
dw 0xaa55
```
注意一点，asm语言此时只是帮助我们编写bin文件的脚本，直接运行的并不是asm文件，而是一个扇区大小的二进制文件