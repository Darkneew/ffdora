#include <stdbool.h>
#include <stdio.h>
#include <filesystem.h>
#include <string.h>

bool surrender_vote(char* l) {
	if (match(l,"y",1)) {
		printf("You surrendered: DEFEAT"); 
		return true;
	} else {
		printf("You refuse to surrender \n"); 
		write_input_prefix();
		return false; 
	}
}

void ff(void)
{
	printf("surrender vote : [y/n]? ");
}