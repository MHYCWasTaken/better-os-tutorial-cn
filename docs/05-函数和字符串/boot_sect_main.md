---
layout: post
title: 05. boot_sect_main.asm
nav_order: 99
parent: 05-函数和字符串
---

```nasm
[org 0x7c00] ; offset偏移

; 主例程确保参数准备就绪，然后调用函数
mov bx, HELLO ; 想一想这里为什么不用加引号(直接告诉你，因为下面定义了)
call print ; 调用print函数

call print_nl ; 调用print_nl

mov bx, GOODBYE
call print

call print_nl

mov dx, 0x12fe
call print_hex

; 测试完了可以无限循环了
jmp $

; include不能少
%include "boot_sect_print.asm"
%include "boot_sect_print_hex.asm"


; 定义
HELLO:
    db 'Hello, World', 0

GOODBYE:
    db 'Goodbye', 0

; 咒语
times 510-($-$$) db 0
dw 0xaa55
```