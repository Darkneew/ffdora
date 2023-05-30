#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/x86.h>
#include <kernel/io.h>
#include <kernel/keyboard.h>

struct gdtdesc kgdt[GDTSIZE];		/* GDT */
struct tss default_tss;
struct gdtr kgdtr;				/* GDTR */
struct idtdesc kidt[IDTSIZE]; 		/* IDT table */
struct idtr kidtr; 				/* IDTR registry */		
uint32_t* stack_ptr=0;

extern void init_segments();

void schedule(){ }


void isr_schedule_int()
{
	static int tic = 0;
	static int sec = 0;
		tic++;
		if (tic % 100 == 0) {
		sec++;
		tic = 0;
	}
	schedule();
	outb(0x20,0x20);
	outb(0xA0,0x20);
}

void do_syscalls(int num){
	 uint32_t ret,ret1,ret2,ret3,ret4;
	 asm("mov %%ebx, %0": "=m"(ret):);
	 asm("mov %%ecx, %0": "=m"(ret1):);
	 asm("mov %%edx, %0": "=m"(ret2):);
	 asm("mov %%edi, %0": "=m"(ret3):);
	 asm("mov %%esi, %0": "=m"(ret4):);
	 asm("cli");
	 asm("mov %%ebp, %0": "=m"(stack_ptr):);

	 // syscall.call(num); to implement
	 asm("sti");
}



void isr_kbd_int(void)
{
	uint8_t i;
	static int lshift_enable;
	static int rshift_enable;
	static int alt_enable;
	static int ctrl_enable;
	do {
		i = inb(0x64);
	} while ((i & 0x01) == 0);
	

	i = inb(0x60);
	i--;

	if (i < 0x80) {		/* touche enfoncee */
		switch (i) {
		case 0x29:
			lshift_enable = 1;
			break;
		case 0x35:
			rshift_enable = 1;
			break;
		case 0x1C:
			ctrl_enable = 1;
			break;
		case 0x37:
			alt_enable = 1;
			break;
		default:
			if(alt_enable==1) terminal_putchar(kbdmap[i * 4 + 2]);
			else if(lshift_enable == 1 || rshift_enable == 1) terminal_putchar(kbdmap[i * 4 + 1]);
			else terminal_putchar(kbdmap[i * 4]);
            break;
		}
	} else {		/* touche relachee */
		i -= 0x80;
		switch (i) {
		case 0x29:
			lshift_enable = 0;
			break;
		case 0x35:
			rshift_enable = 0;
			break;
		case 0x1C:
			ctrl_enable = 0;
			break;
		case 0x37:
			alt_enable = 0;
			break;
		}
	}
	
		outb(0x20,0x20);
		outb(0xA0,0x20); 
}

void isr_GP_exc(void)
{
	printf("\n The ennemy has backdoored! Never leave an open nexus\n");
	asm("hlt");
}

void isr_PF_exc(void)
{
	printf("\n The ennemy has backdoored! Never leave an open nexus\n");
	asm("hlt");
}

void isr_default_int(int id)
{
	switch (id){
		case 1:
			isr_kbd_int();
			break;
			
			
		default:
			return;
		
	}
	
	outb(0x20,0x20);
	outb(0xA0,0x20);
}

extern void _asm_int_1();
extern void _asm_int_0();
extern void _asm_syscalls();
extern void _asm_exc_GP();
extern void _asm_exc_PF();
extern void _asm_schedule();
extern void _load_gdt();
extern void _load_idt();

void init_gdt_desc(uint32_t base, uint32_t limite, uint8_t acces, uint8_t other, struct gdtdesc *desc)
{
    desc->lim0_15 = (limite & 0xffff);
    desc->base0_15 = (base & 0xffff);
    desc->base16_23 = (base & 0xff0000) >> 16;
    desc->acces = acces;
    desc->lim16_19 = (limite & 0xf0000) >> 16;
    desc->other = (other & 0xf);
    desc->base24_31 = (base & 0xff000000) >> 24;
    return;
}

void init_gdt(void)
{
    default_tss.debug_flag = 0x00;
    default_tss.io_map = 0x00;
    default_tss.esp0 = 0x1FFF0;
    default_tss.ss0 = 0x18;

    /* initialize gdt segments */
    init_gdt_desc(0x0, 0x0, 0x0, 0x0, &kgdt[0]);
    init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, &kgdt[1]);    /* code */
    init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, &kgdt[2]);    /* data */
    init_gdt_desc(0x0, 0x0, 0x97, 0x0D, &kgdt[3]);        /* stack */

    init_gdt_desc(0x0, 0xFFFFF, 0xFF, 0x0D, &kgdt[4]);    /* ucode */
    init_gdt_desc(0x0, 0xFFFFF, 0xF3, 0x0D, &kgdt[5]);    /* udata */
    init_gdt_desc(0x0, 0x0, 0xF7, 0x0D, &kgdt[6]);        /* ustack */

	init_gdt_desc((uint32_t) & default_tss, 0x67, 0xE9, 0x00, &kgdt[7]);    /* descripteur de tss */

    /* initialize the gdtr structure */
    kgdtr.limite = GDTSIZE * 8;
    kgdtr.base = GDTBASE;

    /* copy the gdtr to its memory area */
    memcpy((char *) kgdtr.base, (char *) kgdt, kgdtr.limite);

    /* load the gdtr registry */
    _load_gdt();

    /* initiliaz the segments */
    //init_segments();
}

void init_idt_desc(uint16_t select, uint32_t offset, uint16_t type, struct idtdesc *desc)
{
	desc->offset0_15 = (offset & 0xffff);
	desc->select = select;
	desc->type = type;
	desc->offset16_31 = (offset & 0xffff0000) >> 16;
	return;
}

void init_idt(void)
{
	/* Init irq */
	int i;
	for (i = 0; i < IDTSIZE; i++) 
		init_idt_desc(0x08, (uint32_t)_asm_schedule, INTGATE, &kidt[i]);  
	
	/* Vectors  0 -> 31 are for exceptions */
	init_idt_desc(0x08, (uint32_t) _asm_exc_GP, INTGATE, &kidt[13]);		/* #GP */
	init_idt_desc(0x08, (uint32_t) _asm_exc_PF, INTGATE, &kidt[14]);     /* #PF */
	
	init_idt_desc(0x08, (uint32_t) _asm_schedule, INTGATE, &kidt[32]);
	init_idt_desc(0x08, (uint32_t) _asm_int_1, INTGATE, &kidt[33]);
	
	init_idt_desc(0x08, (uint32_t) _asm_syscalls, TRAPGATE, &kidt[48]);
	init_idt_desc(0x08, (uint32_t) _asm_syscalls, TRAPGATE, &kidt[128]); //48
	
	kidtr.limite = IDTSIZE * 8;
	kidtr.base = IDTBASE;
	
	
	/* Copy the IDT to the memory */
	memcpy((char *) kidtr.base, (char *) kidt, kidtr.limite);

	/* Load the IDTR registry */
	_load_idt();
}


void init_pic(void)
{
	/* Initialization of ICW1 */
	outb(0x20, 0x11);
	outb(0x80, 0);
	outb(0xA0, 0x11);
	outb(0x80, 0);

	/* Initialization of ICW2 */
	outb(0x21, 0x20);	/* start vector = 32 */
	outb(0x80, 0);
	outb(0xA1, 0x70);	/* start vector = 96 */
	outb(0x80, 0);

	/* Initialization of ICW3 */
	outb(0x21, 0x04);
	outb(0x80, 0);
	outb(0xA1, 0x02);
	outb(0x80, 0);

	/* Initialization of ICW4 */
	outb(0x21, 0x01);
	outb(0x80, 0);
	outb(0xA1, 0x01);
	outb(0x80, 0);

	/* mask interrupts */
	outb(0x21, 0x0);
	outb(0x80, 0);
	outb(0xA1, 0x0);
	outb(0x80, 0);
}
