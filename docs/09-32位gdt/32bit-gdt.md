---
layout: post
title: 09. 32bit-gdt.asm
nav_order: 99
parent: 09-32位gdt
---
```nasm
gdt_start: ; 不要移除这些标签，计算大小和跳转要用到
    ; GDT以8位的null开始
    dd 0x0 ; 4 byte
    dd 0x0 ; 4 byte
    ; 也可以改为dw 0x0，等价

; 代码段的GDT。基数=0x00000000，长度=0xfffff
; 有关标志，请参阅os-dev.pdf文档，第36页
gdt_code: 
    dw 0xffff    ; 段长度 , bits 0-15
    dw 0x0       ; 段基址, bits 0-15
    db 0x0       ; 段基址, bits 16-23
    db 10011010b ; 标志 (8 bits)
    db 11001111b ; 标志 (4 bits) + 段长度, bits 16-19
    db 0x0       ; 段基址, bits 24-31

; GDT的数据段。基和长度与代码段相同
; 某些标志已更改，请再次参阅os-dev.pdf
gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

; GDT 描述符
gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; 大小（16位）, 总比真实大小小1
    dd gdt_start ; 地址（32位）

; 定义一些常量，之后使用
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
```