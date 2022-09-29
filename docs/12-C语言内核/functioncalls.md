---
layout: post
title: 12. functionscalls.c
nav_order: 99
parent: 12-C语言内核
---
```c
void caller() {
    my_func(0xdede);
}

int my_func(int arg) {
    return arg;
}
```