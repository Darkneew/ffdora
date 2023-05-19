#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/tty.h>


char* currentlign;
bool surrv;
bool cff;
bool pars;
int actu;
int cas;//ctrl alt shift
int loldlencours;
int rand;
bool scot;

void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

void io_wait(int n)
{
	for (int i =0; i<n; i++)
    	outb(0x80, 0);
}

uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

void clean (void){
	for (size_t x = 0; x < get_width(); x++) {
			currentlign[x] = ' ';
		}
	actu=0;
}

bool match(char* li, char* fc, size_t fclength)
{
	bool bonmatch=true;
	for (size_t x=0; x<get_width(); x++)
	{
		if ((li[x]!=fc[x] && x<fclength)||(li[x]!=' ' && x>=fclength)){bonmatch=false;}
	}
	return (bonmatch);
}

void write_input_prefix(void) {
	// à développer qd on aura un file system
	printf("> ");
}

void switch_side(void)
{
	if (get_terminal_color() == get_entry_color(11, 0)){
		terminal_setcolor(get_entry_color(12, 0));
	}
	else {terminal_setcolor(get_entry_color(11, 0));}
	write_input_prefix();
}

void glitch(void)
{
	int j=6;
	int z=j/0;
	printf((char*) z);
}

void ff(void)
{
	surrv=true;
	printf("surrender vote : [y/n]? ");
}

void help(void)
{
	pars=false;
	printf("switch side - Change side color \n");
	printf("glitch - A glitch causing rift to reset \n");
	printf("ff - Start a surrender vote \n");
	printf("loldle - Play loldle a game where you must find a random champ\n");
	printf("scoot - Enter text edit mode \n");
	printf("help - Print this \n");
	write_input_prefix();
	pars=true;
}

void loldle(char* guess){
	bool pastrouv=true;
	for (int i=0; i<161; i++){ //a dichotomiser pour opti
		if (match(guess,get_perso(i,0),strlen(get_perso(i,0))))
		{
			pastrouv=false;
			uint8_t col=get_terminal_color();
			for (int j=1; j<8;j++){
				if (get_perso(i,j)==get_perso(loldlencours,j)){
					terminal_setcolor(get_entry_color(10,0));
				}
				else {terminal_setcolor(get_entry_color(4,0));}
				printf(get_perso(i,j));
				printf(" ");
			}
			terminal_setcolor(col);
			printf("\n");
			if (i==loldlencours){printf("Congrats \n");loldlencours=161;pars=true;write_input_prefix();}
			else {printf("Enter a champion's name : ");}
		}
	}
	if (pastrouv){printf("Unknown champion, try again \n");printf("Enter a champion's name : ");}
}


void parse(char* l)
{	
	if (!surrv && !scot){
		if (match(l,"switch side",11)) {switch_side();}
		else if (match(l,"glitch",6)) glitch();
		else if (match(l,"help",4)) help();
		else if (match(l,"ff",2)) ff();
		else if (match(l,"  ",2)) write_input_prefix();
		else if (match(l,"loldle",6)) {loldlencours=rand; pars=false;printf("Enter a champion's name : ");}
		else if (match(l,"scoot",5)) {scot=true;}
		else {
			pars=false;
			printf("Unknown spell, try again \n");
			write_input_prefix();
			pars=true;
		}
	}
	else if (surrv){
		if (match(l,"y",1)){printf("You surrendered"); cff=true;}
		else{pars=false; printf("You refuse to surrender \n"); write_input_prefix(); pars=true; surrv=false;}
	}
	else if (scot){if (match(l,"quit",4)) {scot=false; write_input_prefix();}}
}


void liclavier(int m, int* de, char* clav, bool pars) //on va autoriser l'ecriture seulement si la touche à été relevée
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
			if (!scot){
				if (actu>0){
				terminal_delete(scot);
				actu+=-1;
				currentlign[actu]=' ';}
			}
			else {
				terminal_delete(scot);
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
			if (pars) {parse(currentlign);}
			else if (loldlencours!=161) {loldle(currentlign);}
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
				char c=clav[m+58]; 
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
	rand=(rand+1)%161;
}

void kernel_main(void) {
	terminal_initialize();
	clean();
	cas=0;
	rand=0;
	loldlencours=161;
	pars=true;
	cff=false;
	surrv=false;
	scot=false;
	int de[80];
	uint8_t inter;
	int m;
	char* clav= get_clavier();
	printf("Welcome to the rift!\n");
	write_input_prefix()
	while ( !cff ) {
			inter=inb(0x060);
			m=inter;
			liclavier(m,de,clav,pars);
	}

}

