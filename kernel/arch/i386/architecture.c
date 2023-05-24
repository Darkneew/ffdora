#include <stdint.h>

#include <kernel/io.h>
#include <kernel/x86.h>

extern void end_init_arch();

void archinit(void) {
    init_gdt();
    init_idt();
    init_pic();
    //end_init_arch();
}

void reboot(void) {
    uint8_t good = 0x02;
    while ((good & 0x02) != 0)
        good = inb(0x64);
    outb(0x64, 0xFE);
}