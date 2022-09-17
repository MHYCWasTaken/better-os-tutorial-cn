---
layout: post
title: 06. boot_sect_segmentation.asm
nav_order: 99
parent: 06-引导段
---

```nasm
mov ah, 0x0e ; tty

mov al, [the_secret]
int 0x10 ; 因为没有位移0x7c00，所以这个会输出乱码（见03-引导内存）

mov bx, 0x7c0 ; 段寄存器地址自动左移4位，即2^4倍，十六进制即0x7c00
mov ds, bx
; ds存了数据，所以内存将偏移0x7c00
mov al, [the_secret]
int 0x10

mov al, [es:the_secret]
int 0x10 ; es现在是空的

mov bx, 0x7c0
mov es, bx
mov al, [es:the_secret]
int 0x10


jmp $

the_secret:
    db "X"

; 咒语
times 510 - ($-$$) db 0
dw 0xaa55
```