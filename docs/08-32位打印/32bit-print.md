---
layout: post
title: 08. 32bit_print.asm
nav_order: 99
parent: 08-32位打印
---
```nasm
[bits 32] ; 哟,真方便

; 定义常量
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f ; 每个字符的颜色

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY ; 还记得edx是什么吗？去lesson2的图片看看
    ; 因为我们在32位了，所以现在可以寻址到32位寄存器了，也就是e什么x

print_string_pm_loop:
    mov al, [ebx] ; [ebx] 是字符的地址
    ; 还记得一个字符占两个字节吗，这里只取了字符内容，舍去了颜色信息
    mov ah, WHITE_ON_BLACK
    ; 颜色统一黑白

    cmp al, 0 ; 查看是不是字符串结尾
    je print_string_pm_done

    mov [edx], ax ; 在显存中存储字符+属性
    add ebx, 1 ; 下一个字符
    add edx, 2 ; 下一个显存位置

    jmp print_string_pm_loop

print_string_pm_done:
    popa
    ret
```