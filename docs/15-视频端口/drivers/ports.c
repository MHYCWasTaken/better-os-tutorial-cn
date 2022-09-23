// 文件冒红光，因为你使用的编辑器并不支持内联asm语法，这是正常的

/* 从指定端口读取字节 */
unsigned char port_byte_in (unsigned short port) {
    unsigned char result;
    /* 内联汇编语法
     * !! 注意如何从NASM切换源寄存器和目标寄存器 !!
     *
     * ' "=a" (result) '; set '=' the C variable '(result)' to the value of register e'a'x
     * '"d" (port)': map the C variable '(port)' into e'd'x register
     *
     * 输入和输出用冒号分隔
     */
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out (unsigned short port, unsigned char data) {

/* Notice how here both registers are mapped to C variables and
* nothing is returned, thus, no equals '=' in the asm syntax
* However we see a comma since there are two variables in the input area
* and none in the 'return' area
*/

/*注意这里两个寄存器是如何映射到C变量和
*没有返回任何内容，因此，在asm语法中没有等于“=”的内容
*然而，我们看到一个逗号，因为输入区域中有两个变量
*“return”区域中没有
*/ 
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short port_word_in (unsigned short port) {
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out (unsigned short port, unsigned short data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}
