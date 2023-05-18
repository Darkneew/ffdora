#include <stdint.h>

#include <kernel/io.h>
#include <kernel/x86.h>


void archinit(void) {
    init_gdt();
	asm("	movw $0x18, %%ax \n \
    		movw %%ax, %%ss \n \
			movl %0, %%esp"::"i" (KERN_STACK));
    init_idt();
    init_pic();
    asm("	movw $0x38, %ax; ltr %ax");	 
}

void reboot(void) {
    uint8_t good = 0x02;
    while ((good & 0x02) != 0)
        good = inb(0x64);
    outb(0x64, 0xFE);
}