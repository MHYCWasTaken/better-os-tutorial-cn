---
layout: default
title: Lesson 05 - boot_sect_print.asm
nav_order: 99
parent: Lesson 05
---

```nasm
print:
    pusha ; 忘了这是什么？到本节的content里面看看（直接告诉你，记录全部寄存器状态以便之后恢复）

; keep this in mind:
; while (string[i] != 0) { print string[i]; i++ }

; the comparison for string end (null byte)
start:
    mov al, [bx] ; 去看看主函数调用的地方，调用之前是不是把字符串存到了bx？
    cmp al, 0    ; 字符串是空的就直接跳到done
    je done

    mov ah, 0x0e ; 熟悉的tty模式
    int 0x10     ; 打印

    add bx, 1 ; bx指针移动一位 = 看下一个字符
    jmp start ; 回到start处，看是不是有点递归的味道？

done:
    popa ; 看，这里恢复了寄存器
    ret  ; return回到了主函数



print_nl:
    pusha ; ~~存档~~
    
    mov ah, 0x0e ; tty
    mov al, 0x0a ; 一个换行符
    int 0x10
    mov al, 0x0d ; 回车符
    int 0x10
    
    popa ; ~~读档~~
    ret  ; ~~退出至主界面~~
```