#ifndef _KERNEL_CURSOR_H
#define _KERNEL_CURSOR_H

#include <stdint.h>
#include <stdbool.h>

void activate_cursor();
void deactivate_cursor();
bool cursor_is_active();
void enable_cursor();
void disable_cursor();
void update_cursor();

#endif
