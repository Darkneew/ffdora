#include <stdbool.h>
#include <stddef.h>
#include <kernel/tty.h>

bool match(char* li, char* fc, size_t fclength)
{
	bool bonmatch = true;
	for (size_t x=0; x<get_width(); x++)
	{
		if ((li[x]!=fc[x] && x<fclength)||(li[x]!=' ' && x>=fclength)) bonmatch = false;
	}
	return bonmatch;
}