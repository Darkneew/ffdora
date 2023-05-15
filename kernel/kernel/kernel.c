#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/tty.h>

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

void uinttostr (uint8_t n, bool dec)
{
	int chfr;
	int m;
	int j=0;
	int pui=1;
	m=n;
	if (dec){ 
		m=0;
		while (n>0)
		{
			chfr=n%10;
			terminal_putchar(chfr);
			m+=pui*chfr;
			pui=pui*8;
			n=n/10;
		}
	}
	while (m>0)
	{
		chfr=m%10;
		terminal_putchar(chfr);
		m=m/10;
		j+=1;
	}
	terminal_writestring("tic");
}

void liclavier(int m, int* de) //on va autoriser l'ecriture seulement si la touche à été relevée
{
	if (m==2 && de[m]==0){terminal_putchar('&'); de[m]=1;} else if (m==130 && de[m-128]==1){de[m-128]=0;}
	else if (m==3 && de[m]==0){terminal_putchar('é'); de[m]=1;} else if (m==131 && de[m-128]==1){de[m-128]=0;}
	else if (m==4 && de[m]==0){terminal_putchar('"'); de[m]=1;} else if (m==132 && de[m-128]==1){de[m-128]=0;}
	else if (m==5 && de[m]==0){terminal_putchar('\''); de[m]=1;} else if (m==133 && de[m-128]==1){de[m-128]=0;}
	else if (m==6 && de[m]==0){terminal_putchar('('); de[m]=1;} else if (m==134 && de[m-128]==1){de[m-128]=0;}
	else if (m==7 && de[m]==0){terminal_putchar('-'); de[m]=1;} else if (m==135 && de[m-128]==1){de[m-128]=0;}
	else if (m==8 && de[m]==0){terminal_putchar('è'); de[m]=1;} else if (m==136 && de[m-128]==1){de[m-128]=0;}
	else if (m==9 && de[m]==0){terminal_putchar('_'); de[m]=1;} else if (m==137 && de[m-128]==1){de[m-128]=0;}
	else if (m==10 && de[m]==0){terminal_putchar('ç'); de[m]=1;} else if (m==138 && de[m-128]==1){de[m-128]=0;}
	else if (m==11 && de[m]==0){terminal_putchar('à'); de[m]=1;} else if (m==139 && de[m-128]==1){de[m-128]=0;}
	else if (m==12 && de[m]==0){terminal_putchar(')'); de[m]=1;} else if (m==140 && de[m-128]==1){de[m-128]=0;}
	else if (m==13 && de[m]==0){terminal_putchar('='); de[m]=1;} else if (m==141 && de[m-128]==1){de[m-128]=0;}
	else if (m==14 && de[m]==0){terminal_delete(); de[m]=1;} else if (m==142 && de[m-128]==1){de[m-128]=0;}
	else if (m==15 && de[m]==0){terminal_writestring("   "); de[m]=1;} else if (m==143 && de[m-128]==1){de[m-128]=0;}
	else if (m==16 && de[m]==0){terminal_putchar('a'); de[m]=1;} else if (m==144 && de[m-128]==1){de[m-128]=0;}
	else if (m==17 && de[m]==0){terminal_putchar('z'); de[m]=1;} else if (m==145 && de[m-128]==1){de[m-128]=0;}
	else if (m==18 && de[m]==0){terminal_putchar('e'); de[m]=1;} else if (m==146 && de[m-128]==1){de[m-128]=0;}
	else if (m==19 && de[m]==0){terminal_putchar('r'); de[m]=1;} else if (m==147 && de[m-128]==1){de[m-128]=0;}
	else if (m==20 && de[m]==0){terminal_putchar('t'); de[m]=1;} else if (m==148 && de[m-128]==1){de[m-128]=0;}
	else if (m==21 && de[m]==0){terminal_putchar('y'); de[m]=1;} else if (m==149 && de[m-128]==1){de[m-128]=0;}
	else if (m==22 && de[m]==0){terminal_putchar('u'); de[m]=1;} else if (m==150 && de[m-128]==1){de[m-128]=0;}
	else if (m==23 && de[m]==0){terminal_putchar('i'); de[m]=1;} else if (m==151 && de[m-128]==1){de[m-128]=0;}
	else if (m==24 && de[m]==0){terminal_putchar('o'); de[m]=1;} else if (m==152 && de[m-128]==1){de[m-128]=0;}
	else if (m==25 && de[m]==0){terminal_putchar('p'); de[m]=1;} else if (m==153 && de[m-128]==1){de[m-128]=0;}
	else if (m==26 && de[m]==0){terminal_putchar('^'); de[m]=1;} else if (m==154 && de[m-128]==1){de[m-128]=0;}
	else if (m==27 && de[m]==0){terminal_putchar('$'); de[m]=1;} else if (m==155 && de[m-128]==1){de[m-128]=0;}
	else if (m==28 && de[m]==0){terminal_putchar('\n'); de[m]=1;} else if (m==156 && de[m-128]==1){de[m-128]=0;}
	//else if (m==29 && de[m]==0){terminal_putchar('9'); de[m]=1;} else if (m==157 && de[m-128]==1){de[m-128]=0;} c'est le ctrl
	else if (m==30 && de[m]==0){terminal_putchar('q'); de[m]=1;} else if (m==158 && de[m-128]==1){de[m-128]=0;}
	else if (m==31 && de[m]==0){terminal_putchar('s'); de[m]=1;} else if (m==159 && de[m-128]==1){de[m-128]=0;}
	else if (m==32 && de[m]==0){terminal_putchar('d'); de[m]=1;} else if (m==160 && de[m-128]==1){de[m-128]=0;}
	else if (m==33 && de[m]==0){terminal_putchar('f'); de[m]=1;} else if (m==161 && de[m-128]==1){de[m-128]=0;}
	else if (m==34 && de[m]==0){terminal_putchar('g'); de[m]=1;} else if (m==162 && de[m-128]==1){de[m-128]=0;}
	else if (m==35 && de[m]==0){terminal_putchar('h'); de[m]=1;} else if (m==163 && de[m-128]==1){de[m-128]=0;}
	else if (m==36 && de[m]==0){terminal_putchar('j'); de[m]=1;} else if (m==164 && de[m-128]==1){de[m-128]=0;}
	else if (m==37 && de[m]==0){terminal_putchar('k'); de[m]=1;} else if (m==165 && de[m-128]==1){de[m-128]=0;}
	else if (m==38 && de[m]==0){terminal_putchar('l'); de[m]=1;} else if (m==166 && de[m-128]==1){de[m-128]=0;}
	else if (m==39 && de[m]==0){terminal_putchar('m'); de[m]=1;} else if (m==167 && de[m-128]==1){de[m-128]=0;}
	else if (m==40 && de[m]==0){terminal_putchar('ù'); de[m]=1;} else if (m==168 && de[m-128]==1){de[m-128]=0;}
	else if (m==41 && de[m]==0){terminal_putchar('²'); de[m]=1;} else if (m==169 && de[m-128]==1){de[m-128]=0;}
	//else if (m==42 && de[m]==0){terminal_putchar(''); de[m]=1;} else if (m==170 && de[m-128]==1){de[m-128]=0;} c'est le L shift
	else if (m==43 && de[m]==0){terminal_putchar('*'); de[m]=1;} else if (m==171 && de[m-128]==1){de[m-128]=0;} //celle au dessus de enter
	else if (m==44 && de[m]==0){terminal_putchar('w'); de[m]=1;} else if (m==172 && de[m-128]==1){de[m-128]=0;}
	else if (m==45 && de[m]==0){terminal_putchar('x'); de[m]=1;} else if (m==173 && de[m-128]==1){de[m-128]=0;}
	else if (m==46 && de[m]==0){terminal_putchar('c'); de[m]=1;} else if (m==174 && de[m-128]==1){de[m-128]=0;}
	else if (m==47 && de[m]==0){terminal_putchar('v'); de[m]=1;} else if (m==175 && de[m-128]==1){de[m-128]=0;}
	else if (m==48 && de[m]==0){terminal_putchar('b'); de[m]=1;} else if (m==176 && de[m-128]==1){de[m-128]=0;}
	else if (m==49 && de[m]==0){terminal_putchar('n'); de[m]=1;} else if (m==177 && de[m-128]==1){de[m-128]=0;}
	else if (m==50 && de[m]==0){terminal_putchar(','); de[m]=1;} else if (m==178 && de[m-128]==1){de[m-128]=0;}
	else if (m==51 && de[m]==0){terminal_putchar(';'); de[m]=1;} else if (m==179 && de[m-128]==1){de[m-128]=0;}
	else if (m==52 && de[m]==0){terminal_putchar(':'); de[m]=1;} else if (m==180 && de[m-128]==1){de[m-128]=0;}
	else if (m==53 && de[m]==0){terminal_putchar('!'); de[m]=1;} else if (m==181 && de[m-128]==1){de[m-128]=0;}
	//else if (m==54 && de[m]==0){terminal_putchar(''); de[m]=1;} else if (m==182 && de[m-128]==1){de[m-128]=0;} c'est le R shift
	else if (m==55 && de[m]==0){terminal_putchar('*'); de[m]=1;} else if (m==183 && de[m-128]==1){de[m-128]=0;}//celle du pad
	//else if (m==56 && de[m]==0){terminal_putchar(''); de[m]=1;} else if (m==184 && de[m-128]==1){de[m-128]=0;} c'est le alt
	else if (m==57 && de[m]==0){terminal_putchar(' '); de[m]=1;} else if (m==185 && de[m-128]==1){de[m-128]=0;}
	//else if (m==58 && de[m]==0){terminal_putchar(''); de[m]=1;} else if (m==186 && de[m-128]==1){de[m-128]=0;} c'est le maj
}


void kernel_main(void) {
	terminal_initialize();
	printf("Welcome to the rift!\n");
	int de[60];
	uint8_t inter;
	int m;
	while (0<1) {
			inter=inb(0x060);
			m=inter;
			liclavier(m,de);
	}

}
