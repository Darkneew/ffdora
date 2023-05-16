#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/tty.h>

char* currentlign;
bool surrv;
bool cff;
bool pars;
int actu;


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

void switch_side(void)
{
	if (get_terminal_color() == get_entry_color(11, 0)){
		terminal_setcolor(get_entry_color(12, 0));
	}
	else {terminal_setcolor(get_entry_color(11, 0));}
}

void bug(void)
{
	int j=6;
	int z=j/0;
	terminal_writestring(z);
}

void ff(void)
{
	surrv=true;
	terminal_writestring("surrender vote : [y/n]?");
}

void help(void)
{
	pars=false;
	terminal_writestring("switch side - change side color \n");
	terminal_writestring("glitch - a glitch causing rift to reset \n");
	terminal_writestring("ff - start a surrender vote \n");
	terminal_writestring("help - print this \n");
	pars=true;
}

void parse(char* l)
{	
	if (!surrv){
		if (match(l,"switch side",11)) {switch_side();}
		else{if (match(l,"glitch",6)){bug();}
		else{if (match(l,"help",4)){help();}
		else{if (match(l,"ff",2)){ff();}
		else{if (match(l,"  ",2)){terminal_writestring("pas normal");}
		else{
			pars=false;
			terminal_writestring("unknown spell, try again \n");
			pars=true;
		}}}}}
	}
	else {
		if (match(l,"y",1)){terminal_writestring("you surrendered"); cff=true;}
		else{pars=false; terminal_writestring("you refuse to surrender \n"); pars=true; surrv=false;}
	}
}


void liclavier(int m, int* de, char* clav, bool pars) //on va autoriser l'ecriture seulement si la touche à été relevée
{
	if (m<59 && de[m]==0) {
		switch (m)
		{
		case 4:
			terminal_putchar('"');
			currentlign[actu]='"';
			actu+=1;
			break;
		case 14:
			if (actu>0){
			terminal_delete();
			actu+=-1;
			currentlign[actu]=' ';}
			break;
		case 15:
			terminal_writestring("   ");
			currentlign[actu]=' ';
			currentlign[actu++]=' ';
			currentlign[actu++]=' ';
			actu+=1;
			break;
		case 28:
			terminal_putchar('\n');
			if (pars) {parse(currentlign);}
			clean();
			break;
		default:
			char c=clav[m]; 
			terminal_putchar(c);
			currentlign[actu]=c;
			actu+=1;
			break;
		}
		de[m]=1;
	}
	else {
		if (m>129 && de[m-128]==1){de[m-128]=0;}
	}
	
}


void kernel_main(void) {
	terminal_initialize();
	clean();
	pars=true;
	cff=false;
	surrv=false;
	int de[60];
	uint8_t inter;
	int m;
	char* clav= get_clavier();
	while ( !cff ) {
			inter=inb(0x060);
			m=inter;
			liclavier(m,de,clav,pars);
	}

}

