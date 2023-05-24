#include <stdio.h>
#include <filesystem.h>

void help(void)
{
	printf("switch side - Change side color \n");
	printf("reboot - To enter a new lobby \n");
	printf("ff - Start a surrender vote \n");
	printf("loldle - Play loldle a game where you must find a random champ\n");
	printf("scoot - Enter text edit mode \n");
	printf("help - Print this \n");
	write_input_prefix();
}