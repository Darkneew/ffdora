#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

void terminal_initialize(void);
void terminal_reset(void);
void terminal_delete(bool scot);
void terminal_setcolor(uint8_t);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
char* get_clavier(void);
size_t get_terminal_row(void);
void set_terminal_row(size_t r);
void set_terminal_column(size_t r);
void set_terminal_buffer(size_t index, uint16_t col);
size_t get_terminal_column(void);
size_t get_height(void);
size_t get_width(void);
uint8_t get_terminal_color(void);
uint8_t get_entry_color(size_t fc,size_t  bc);

#endif
