#include <stdint.h>
#include <stdbool.h>
#include <kernel/io.h>
#include <kernel/tty.h>
#include "vga.h"

bool is_cursor_active = true;
bool is_cursor_enabled = true;

void update_cursor()
{
    if (!is_cursor_active) return;
    if (!is_cursor_enabled) return;
	uint16_t pos = get_terminal_column() + VGA_WIDTH * get_terminal_row();
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void activate_cursor () {
    is_cursor_active = true;
    update_cursor();
}


bool cursor_is_active() {
    return is_cursor_active;
}

void deactivate_cursor () {
    is_cursor_active = false;
}

void enable_cursor()
{
    is_cursor_enabled = true;
	outb(0x3D5, (inb(0x3D5) & 0xC0) | 0);
    update_cursor();
}

void disable_cursor()
{
    is_cursor_enabled = false;
	outb(0x3D5, 0x20);
}