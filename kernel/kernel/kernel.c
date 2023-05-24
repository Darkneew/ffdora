#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <cmd.h>
#include <filesystem.h>
#include <kernel/tty.h>
#include <kernel/architecture.h>
#include <kernel/io.h>

enum kernelstate {
	INPUT,
	LOLDLE,
	FF,
	SURRENDER_VOTE,
	SCOOT
};

enum kernelstate kstate;
char* currentlign;
int actu;
int cas;//ctrl alt shift
int rand;

void clean (void){
	for (size_t x = 0; x < get_width(); x++) {
			currentlign[x] = ' ';
		}
	actu=0;
}


void parse(char* l)
{	
	if (match(l,"switch side",11)) {switch_side();}
	else if (match(l,"help",4)) help();
	else if (match(l,"ff",2)) {ff(); kstate = SURRENDER_VOTE;}
	else if (match(l,"reboot",6)) reboot();
	else if (match(l,"loldle",6)) {init_loldle(rand); kstate = LOLDLE; }
	else if (match(l,"scoot",5)) {kstate = SCOOT;}
	else if (match(l,"  ",2)) write_input_prefix();
	else {
		printf("Unknown spell, try again \n");
		write_input_prefix();
	}
}

void scoot(char* l) {
	if (match(l,"quit",4)) {
		kstate = INPUT;
		write_input_prefix();
	}
}


void liclavier(int m, int* de, char* clav) //on va autoriser l'ecriture seulement si la touche à été relevée
{
	if (m<80 && de[m]==0) {
		switch (m) {
		case 4:
			if (cas==0){
				terminal_putchar('"');
				currentlign[actu]='"';
				}
			else { 
				terminal_putchar('3');
				currentlign[actu]='3';
				}
				actu+=1;
				break;
		case 14:
			if (kstate != SCOOT){
				if (actu>0){
				terminal_delete(false);
				actu+=-1;
				currentlign[actu]=' ';}
			}
			else {
				terminal_delete(true);
				if (actu>0){actu += -1;currentlign[actu]=' ';}
				else{actu=get_terminal_column();}
				}
			break;
		case 15:
			printf("   ");
			currentlign[actu]=' ';
			currentlign[actu++]=' ';
			currentlign[actu++]=' ';
			actu+=1;
			break;
		case 28:
			terminal_putchar('\n');
			if (kstate == INPUT) parse(currentlign);
			else if (kstate == SCOOT) scoot(currentlign);
			else if (kstate == LOLDLE) {if (loldle(currentlign)) kstate = INPUT;}
			else if (kstate == SURRENDER_VOTE) {if (surrender_vote(currentlign)) {kstate = FF;} else {kstate = INPUT;}}
			clean();
			break;
		case 42:
			cas=(cas/10)*10+1;
			break;
		case 54:
			cas=(cas/10)*10+1;
			break;
		case 75:
			if (actu>0){actu+=-1;set_terminal_column(get_terminal_column()-1);}
			break;
		case 77:
			{actu+=1;set_terminal_column(get_terminal_column()+1);}
			break;
		default:
			if (cas==0){
				char c=clav[m]; 
				terminal_putchar(c);
				currentlign[actu]=c;}
			else {
				char c=clav[m+88]; 
				terminal_putchar(c);
				currentlign[actu]=c;
			}
			actu+=1;
			break;
		}
		de[m]=1;
	}
	else {
		if (m>129 && de[m-128]==1){
			if (m==170 || m==182){cas=(cas/10)*10;}
			de[m-128]=0;}
	}
	rand=(rand+1)%9887;
}

void kernel_main(void) {
	terminal_initialize();
	clean();
	archinit();
	kstate = INPUT;
	cas=0;
	rand=0;
	int de[80];
	uint8_t inter;
	int m;
	char* clav= get_clavier();
	printf("Welcome to the rift!\n");
	write_input_prefix();
	while (kstate != FF) {
			inter=inb(0x060);
			m=inter;
			liclavier(m,de,clav);
	}

}
