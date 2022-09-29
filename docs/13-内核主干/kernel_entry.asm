[bits 32]
[extern main] ; 定义调用点。必须与内核同名。c“main”函数
call main ; 调用C函数。链接器将知道它在内存中的位置
jmp $
