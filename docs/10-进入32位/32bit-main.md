---
layout: post
title: 10. 32bit-main.asm
nav_order: 99
parent: 10-进入32位
---
```nasm
[org 0x7c00] ; 偏移
    mov bp, 0x9000 ; 栈
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print ; 在BIOS信息（Boot from hard disk...）之后打印
    ; 哈哈，还是第五课

    call switch_to_pm
    jmp $ ; t这句其实执行不到

%include "boot_sect_print.asm" ; lesson 5
%include "32bit-gdt.asm" ; 来自第九课
%include "32bit-print.asm" ; 来自第八课
%include "32bit-switch.asm"

[bits 32]
BEGIN_PM: ; 32-bit-switch.asm中最后跳到了这儿
    mov ebx, MSG_PROT_MODE
    call print_string_pm ; 在屏幕左上角输出
    jmp $

MSG_REAL_MODE db "Started in 16-bit real mode", 0
MSG_PROT_MODE db "Loaded 32-bit protected mode", 0

; bootsector
times 510-($-$$) db 0
dw 0xaa55
```