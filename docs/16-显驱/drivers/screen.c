#include "screen.h"
#include "ports.h"

/* 使最后定义的函数可以被前面定义的函数调用 */
int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

/**********************************************************
 * Public Kernel API functions                            *
 **********************************************************/

/**
 * 在指定位置打印字符串
 * 如果行(row)和列(col)是负数，在光标位置打印
 */
void kprint_at(char *message, int col, int row) {
    /* 判定col和row是不是负数并将其设定为正确的值 */
    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else { // 如果col或row是负数
        offset = get_cursor_offset(); // 获取光标位置
        row = get_offset_row(offset); // 设定row为offset的row
        col = get_offset_col(offset); // 设定col
    }

    /* 循环打印 */
    int i = 0;
    while (message[i] != 0) {
        offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
        /* 计算下一个col和row */
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}
void kprint(char *message) {
    kprint_at(message, -1, -1);
}


/**********************************************************
 * Private kernel functions                               *
 **********************************************************/


/**
 * 内核的最内部打印功能，直接访问视频内存
 *
 * 如果“col”和“row”为负数，我们将在当前光标位置打印
 * 如果“attr”为零，则将使用“white on black”作为默认值
 * 返回下一个字符的偏移量
 * 将视频光标设置为返回的偏移量
 */
int print_char(char c, int col, int row, char attr) {
    unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;

    /* 错误控制：如果坐标不正确，则打印红色“E” */
    if (col >= MAX_COLS || row >= MAX_ROWS) {
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = RED_ON_WHITE;
        return get_offset(col, row);
    }

    int offset;
    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor_offset();

    if (c == '\n') {
        row = get_offset_row(offset);
        offset = get_offset(0, row+1);
    } else {
        vidmem[offset] = c;
        vidmem[offset+1] = attr;
        offset += 2;
    }
    set_cursor_offset(offset);
    return offset;
}

int get_cursor_offset() {
    /* Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; /* 每一个字符占两个字节 */
}

void set_cursor_offset(int offset) {
    /* 类似于get_cursor_offset，但我们不读取数据 */
    offset /= 2; // 计算位置，而舍弃颜色字节
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    char *screen = VIDEO_ADDRESS;

    for (i = 0; i < screen_size; i++) {
        screen[i*2] = ' ';
        screen[i*2+1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_offset(0, 0));
}


int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; }
