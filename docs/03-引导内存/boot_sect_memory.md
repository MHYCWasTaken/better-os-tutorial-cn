---
layout: default
title: Lesson 03 - boot_sect_memory.asm
nav_order: 99
parent: Lesson 03
---
```nasm
mov ah, 0x0e

; 方式1
; 打印the_secret的内存地址，错误
mov al, "1"
int 0x10
mov al, the_secret
int 0x10

; 方式2
; 他打印的是the_secret的内容的内存地址,是正确的
; 但是，BIOS把引导扇区放在了0x7c00
; 所以对于本程序来说的相对内存地址并不正确
mov al, "2"
int 0x10
mov al, [the_secret]
int 0x10

; 方式3
; 将X的指针加0x7c00
; 将指针的内容解除引用
; 我们需要bx的帮助，因为mov al [ax]违法
; 寄存器不能用作同一命令的源和目标。 
; 结合lesson2中注解的图片理解这部分
mov al, "3"           ; al写一个"3"
int 0x10              ; 输出al —— “3”
mov bx, the_secret    ; bx写入一个the_secret的内存地址
add bx, 0x7c00        ; bx加上0x7c00
mov al, [bx]          ; al写入bx的内容
int 0x10

; 方式4
; 尝试一种更方便的方式，我们知道X存储在0x20位置
; 方法4这种很聪明，但没有效率，我们不想每次改动代码都重新计算标签偏移量
mov al, "4"
int 0x10
mov al, [0x7c2d]
int 0x10


jmp $ ; infinite loop

the_secret:
    ; 在奇妙咒语之前储存X
    ; 0x2d的位置
    db "X"

; 奇~妙咒语
times 510-($-$$) db 0
dw 0xaa55
```