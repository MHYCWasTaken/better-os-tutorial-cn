---
layout: post
title: 03. boot_sect_memory_org.asm
nav_order: 99
parent: 03-引导内存
---
```nasm
[org 0x7c00]
mov ah, 0x0e

; 方式1
; 打印the_secret的内存地址，错误
mov al, "1"
int 0x10
mov al, the_secret
int 0x10

; 方式2
; 我们添加了offset偏移'0x7c00'所以这个现在正确
mov al, "2"
int 0x10
mov al, [the_secret]
int 0x10

; 方式3
; 我们添加了offset偏移'0x7c00'所以这个现在错误
mov al, "3"
int 0x10
mov bx, the_secret
add bx, 0x7c00
mov al, [bx]
int 0x10

; 方式4
; 他仍然正确，因为他所输出的是一个给定的地址处内容
; 但是每次代码修改均需要重新计算地址
mov al, "4"
int 0x10
mov al, [0x7c2d]
int 0x10


jmp $

the_secret:
    db "X"

times 510-($-$$) db 0
dw 0xaa55

```