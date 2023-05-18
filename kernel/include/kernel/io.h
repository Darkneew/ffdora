#ifndef _KERNEL_IO_H
#define _KERNEL_IO_H

#include <stdint.h>

void outb(uint16_t port, uint8_t val);
void io_wait(int n);
uint8_t inb(uint16_t port);

#endif
