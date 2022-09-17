---
layout: post
title: 07. boot_sect_main.asm
nav_order: 99
parent: 07-读取磁盘
---

```nasm
[org 0x7c00]
    mov bp, 0x8000 ; 栈放在很远的地方
    mov sp, bp

    ; 准备参数，这是我们自己的disk_load函数
    mov bx, 0x9000 ; es:bx = 0x0000:0x9000 = 0x09000
    mov dh, 2 ; 要阅读两个扇区
    ; BIOS帮我们设置好了dl，他会默认是启动盘
    ; 如果运行不正确使用-fda参数： 'qemu -fda file.bin'
    call disk_load

    ; 召唤一下print_hex
    mov dx, [0x9000] ; 检索第一个加载的单词 （0xDADA）
    call print_hex

    ; 换行
    call print_nl

    ; 一个扇区512字节，所以地址加512就是下一个扇区
    mov dx, [0x9000 + 512] ; first word from second loaded sector, 0xface
    call print_hex

    jmp $

%include "boot_sect_print.asm"
%include "boot_sect_print_hex.asm"
; 这里使用的两个print程序是lesson5中的，可以复制过来
%include "boot_sect_disk.asm"

; 咒语
times 510 - ($-$$) db 0
dw 0xaa55

; 咒语那里填充了足够的0，所以接下来写的数据在第二第三扇区
times 256 dw 0xdada ; 第二扇区写入256个 0xDADA
times 256 dw 0xface ; 第三扇区写入256个 0xFACE
```