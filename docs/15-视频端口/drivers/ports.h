unsigned char port_byte_in (unsigned short port);
void port_byte_out (unsigned short port, unsigned char data);
unsigned short port_word_in (unsigned short port);
void port_word_out (unsigned short port, unsigned short data);
// 这个文件的用处是使kernel.c可以调用以上几个函数(来自ports.c)