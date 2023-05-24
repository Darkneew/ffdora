#include <kernel/tty.h>
#include <filesystem.h>
#include <stdint.h>

void switch_side(void)
{
	if (get_terminal_color() == get_entry_color(11, 0)){
		terminal_setcolor(get_entry_color(12, 0));
	}
	else {terminal_setcolor(get_entry_color(11, 0));}
	write_input_prefix();
}