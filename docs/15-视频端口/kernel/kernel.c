#include "../drivers/ports.h"

void main() {
    /* 询问VGA的寄存器(0x3d4)获取指针位置 
       14 = high byte of cursor and 15 = low byte of cursor. */
    port_byte_out(0x3d4, 14); /* 请求字节14：光标位置的高位字节 */
    /* 返回存储在了0x3d5，读一下 */
    int position = port_byte_in(0x3d5);
    position = position << 8; /* 需要将两个拼起来，所以左移8位 */
    /*
      e.g. 高位请求到了0xab
      正确的位置是0xabcd
      再次请求得到0xcd
      需要先将0xab左移8位变成0xab00
      再加0xcd，即为0xabcd
    */

    port_byte_out(0x3d4, 15); /* 同样请求一次 */
    position += port_byte_in(0x3d5);

    /* VGA“单元格”由字符及其控制数据组成
     * 例如“黑底白字”、“白底红字”等     */
    int offset_from_vga = position * 2;
    
    /* 让我们在当前光标位置写下数据，我们已经知道如何做了 */ 
    char *vga = 0xb8000;
    vga[offset_from_vga] = 'X'; 
    vga[offset_from_vga+1] = 0x0f; /* 黑底白字 */
}
