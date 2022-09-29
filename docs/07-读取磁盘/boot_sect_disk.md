---
layout: post
title: 07. boot_sect_disk.asm
nav_order: 99
parent: 07-读取磁盘
---

```nasm
; load 'dh' sectors from drive 'dl' into ES:BX
disk_load:
    pusha ; 存个档先
    ; dx一会要存0x00，会覆盖掉之前需要的东西，所以我们存个档
    push dx

    mov ah, 0x02 ; 记得吗，dh不能直接赋值，我们需要ax的帮助
    mov al, dh   ; 读盘模式
    mov cl, 0x02 ; cl <- 扇区 (0x01 .. 0x11)
                 ; 0x01是我们的引导扇区，0x02是第一个“可用”扇区
    mov ch, 0x00 ; ch <- 柱面 (0x0 .. 0x3FF, 'cl'的高二位)
    ; dl<-驱动器编号。我们的调用者将其设置为参数并从BIOS中获取
    ; （0=软盘，1=软盘2，0x80=硬盘，0x81=硬盘2）
    mov dh, 0x00 ; dh <- 磁头 (0x0 .. 0xF)

    ; [es:bx] <- 指向将存储数据的缓冲区的指针 
    ; es:bx的意思是从es开始往后移动bx个位置，加个方括号就是指向那个地方的指针
    ; 调用者为我们设置它，它实际上是int 13h的标准位置
    int 0x13      ; BIOS 中断
    jc disk_error ; 如果错误（检测进位符）跳转到disk_error

    pop dx
    cmp al, dh    ; BIOS把al设置为读到的磁盘号码，对比我们需要读的，不一样就报个错
    jne sectors_error
    popa          ; 读档
    ret

; 报错的处理
disk_error:
    mov bx, DISK_ERROR
    call print
    call print_nl
    mov dh, ah ; ah = error code, dl = disk drive that dropped the error
    call print_hex ; check out the code at http://stanislavs.org/helppc/int_13-1.html
    jmp disk_loop

sectors_error:
    mov bx, SECTORS_ERROR
    call print

disk_loop:
    jmp $

DISK_ERROR: db "Disk read error", 0
SECTORS_ERROR: db "Incorrect number of sectors read", 0
```
