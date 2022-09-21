[org 0x7c00]
KERNEL_OFFSET equ 0x1000 ; 链接内核时使用的同一个

    mov [BOOT_DRIVE], dl ; 请记住，BIOS在引导时将引导驱动器设置为“dl”
    mov bp, 0x9000
    mov sp, bp

    mov bx, MSG_REAL_MODE 
    call print
    call print_nl

    call load_kernel ; 读取

    call switch_to_pm ; 禁用中断，加载GDT等等，最后跳到'BEGIN_PM'
    jmp $ ; 执行不到其实

%include "boot_sect_print.asm" ; lesson 5
%include "boot_sect_print_hex.asm" ; lesson 5
%include "boot_sect_disk.asm" ; lesson 7
%include "32bit-gdt.asm" ; lesson 9
%include "32bit-print.asm" ; lesson 8
%include "32bit-switch.asm" ; lesson 10

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print
    call print_nl

    mov bx, KERNEL_OFFSET ; 从磁盘读取并存储在0x1000中
    mov dh, 2
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm
    call KERNEL_OFFSET ; 控制权移交内核
    jmp $ ; 内核如果结束，在这里无限循环


BOOT_DRIVE db 0 ; 最好将其存储在内存中，因为“dl”可能会被覆盖
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE db "Landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

; 咒语
times 510 - ($-$$) db 0
dw 0xaa55
