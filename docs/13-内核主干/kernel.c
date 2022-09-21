/* 这将迫使我们创建一个内核入口函数来代替jmp 0x00 */
void dummy_test_entrypoint() {
}

void main() {
    char* video_memory = (char*) 0xb8000;
    *video_memory = 'X';
}
