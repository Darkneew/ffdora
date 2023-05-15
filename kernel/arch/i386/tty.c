#include  <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
 
#include <kernel/tty.h>
 
#include "vga.h"
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
static const nbfct = 1;
 
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;
static char* currentlign;
static int delta;
 
void terminal_initialize(void) 
{
	clean();
	delta=0;
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
}

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
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_delete(void)
{
	if (terminal_column>0)
	{
		terminal_column+= -1;
		const size_t index = terminal_row * VGA_WIDTH + terminal_column;
		terminal_buffer[index] = vga_entry(' ', terminal_color);
		currentlign[terminal_column]=' ';
		
	}
	/* pour edit de texte et que le del remonte des ligne else
	{
		terminal_row+=-1;
		bool pasfin=true;
		for (int x=VGA_WIDTH-1; x>=0; x+=-1)
			{if (pasfin && terminal_buffer[terminal_row * VGA_WIDTH + x]!=vga_entry(' ', terminal_color)) {
				pasfin=false;
				terminal_column=x+1;
			}}
	}
	*/
}

void clean (){
	for (size_t x = 0; x < VGA_WIDTH; x++) {
			currentlign[x] = ' ';
		}
}

bool match(char* li, char* fc, int fclength)
{
	bool bonmatch=true;
	for (int x=0; x<VGA_WIDTH; x++)
	{
		if ((li[x]!=fc[x] && x<fclength)||(li[x]!=' ' && x>=fclength)){bonmatch=false;}
	}
	return (bonmatch);
}

void parse(char* l)
{
	if (match(l,"switch side",11)) {switch_side();}
	else{
		terminal_writestring("Unknown ability, please retry");
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT){
				terminal_reset();
			}}
	}

void switch_side()
{
	if (terminal_color == vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK)){
		terminal_color = vga_entry_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
	}
	else {terminal_color = vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);}
}

void apply (int i)
{
	if (i==1) {switch_side();}
}

void terminal_putchar(char c) 
{
	if (c=='\n') {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT){
				terminal_reset();
				}
		parse(currentlign);
		clean();
	}
	else {
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		currentlign[terminal_column-delta]=c;
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
		}
	}
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
