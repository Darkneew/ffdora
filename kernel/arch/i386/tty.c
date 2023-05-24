#include  <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <kernel/cursor.h>
#include <kernel/tty.h>
 
#include "vga.h"
 
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_reset(void)
{
	for (size_t y = 0; y < VGA_HEIGHT-1; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = terminal_buffer[index+VGA_WIDTH];
		}
	}
	for (size_t x = 0; x < VGA_WIDTH; x++){
		terminal_buffer[(VGA_HEIGHT-1)*VGA_WIDTH + x] = vga_entry(' ', terminal_color);
	}
	terminal_row += -1;
	update_cursor();
}

char* get_clavier(void) {
	return("&&&&&'(-&_&&)=&&azertyuiop^$&&qsdfghjklm&&&*wxcvbn,;:!&*& &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&1234567890&+&&AZERTYUIOP&&&&QSDFGHJKLM%&&&WXCVBN?./&&*& &");
}

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	update_cursor();
}

void terminal_delete(bool scot)
{
	if (terminal_column>0)
	{
		terminal_column+= -1;
		const size_t index = terminal_row * VGA_WIDTH + terminal_column;
		terminal_buffer[index] = vga_entry(' ', terminal_color);
		
	}
	else if (scot)
	{
		terminal_row+=-1;
		bool pasfin=true;
		for (int x=VGA_WIDTH-1; x>=0; x+=-1)
			{if (pasfin && terminal_buffer[terminal_row * VGA_WIDTH + x]!=vga_entry(' ', terminal_color)) {
				pasfin=false;
				terminal_column=x+1;
			}}
	}
	update_cursor();
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) 
{
	if (c=='\n') {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT){
				terminal_reset();
				}
	}
	else {
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
		}
	}
	update_cursor();
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

size_t get_terminal_row(void){
	return(terminal_row);
}
void set_terminal_row(size_t r){
	terminal_row=r;
	update_cursor();
}

size_t get_terminal_column(void){
	return(terminal_column);
}
void set_terminal_column(size_t r){
	terminal_column=r;
	update_cursor();
}

void set_terminal_buffer(size_t index, uint16_t col){
	terminal_buffer[index]=col;
}

size_t get_height(void){
	return(VGA_HEIGHT);
}

size_t get_width(void){
	return(VGA_WIDTH);
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

uint8_t get_terminal_color(void){
	return(terminal_color);
}

uint8_t get_entry_color(size_t fc, size_t bc){
	return(vga_entry_color(fc,bc));
} 
