---
layout: post
title: 05. boot_sect_print_hex.asm
nav_order: 99
parent: 05-函数和字符串
---
```nasm
; 调用时参数存在了dx，我们取一下
; 方便讲解，假设dx = 0x1234
print_hex:
    pusha ; 记录

    mov cx, 0 ; 一个索引 (诶呀，四个寄存器都被用掉了呢)

; 策略：获取“dx”的最后一个字符，然后转换为ASCII
; 数字ASCII值：“0”（ASCII 0x30）到“9”（0x39），因此只需将0x30添加到字节N。
; 对于字母字符A-F:'A'（ASCII 0x41）到'F'（0x46），我们将添加0x40
; 然后，将ASCII字节移动到结果字符串上的正确位置
; > 这是原作者的话，我也没有理解，只好直译一下。。。
hex_loop:
    cmp cx, 4 ; loop 4 times
    je end
    
                    ; 1.将“dx”的最后一个字符转换为ascii
    mov ax, dx      ; mov ax、dx；我们将使用“ax”作为工作寄存器
    and ax, 0x000f  ; 0x1234->0x0004通过将前三个屏蔽为零
    add al, 0x30    ; 将0x30添加到N以将其转换为ASCII“N”
    cmp al, 0x39    ; 如果大于9，则添加额外的8以表示“A”到“F”
    jle step2
    add al, 7       ; 'A’是ASCII 65而不是58，因此65-58=7

step2:
    ; 2. 获取字符串的正确位置以放置ASCII字符
    ; bx <- 基址 + 字符串长度 - 字符索引
    mov bx, HEX_OUT + 5 ; 基址 + 长度
    sub bx, cx  ; 索引变量
    mov [bx], al ; 将“al”上的ASCII字符复制到“bx”指向的位置
    ror dx, 4 ; 0x1234 -> 0x4123 -> 0x3412 -> 0x2341 -> 0x1234

    add cx, 1   ; cx++，看来还是个for循环啊
    jmp hex_loop

end:
    ; 准备参数并调用函数bx
    mov bx, HEX_OUT
    call print

    popa
    ret

HEX_OUT:
    db '0x0000',0 ; 为新的字符串保留内存（这句我也没理解。。。）
```

很遗憾，这篇代码我并未完全理解，所以注解仅是简单的翻译  
如果你看懂了，欢迎交Issue