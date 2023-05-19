#ifndef _KERNEL_X86_H
#define _KERNEL_X86_H

#include <stdint.h>

#define IDTSIZE		0xFF	/* nombre max. de descripteurs dans la table */
#define GDTSIZE		0xFF	/* nombre max. de descripteurs dans la table */

#define IDTBASE		0x00000000	/* addr. physique ou doit resider la IDT */
#define GDTBASE		0x00000800	/* addr. physique ou doit resider la gdt */

#define INTGATE  0x8E00		/* utilise pour gerer les interruptions */
#define TRAPGATE 0xEF00		/* utilise pour faire des appels systemes */

struct gdtr {
    uint16_t limite;
    uint32_t base;
} /*__attribute__ ((packed))*/;

struct gdtdesc {
    uint16_t lim0_15;
    uint16_t base0_15;
    uint8_t base16_23;
    uint8_t acces;
    uint8_t lim16_19:4;
    uint8_t other:4;
    uint8_t base24_31;
} /*__attribute__ ((packed))*/;


struct tss {
	uint16_t previous_task, __previous_task_unused;
	uint32_t esp0;
	uint16_t ss0, __ss0_unused;
	uint32_t esp1;
	uint16_t ss1, __ss1_unused;
	uint32_t esp2;
	uint16_t ss2, __ss2_unused;
	uint32_t cr3;
	uint32_t eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
	uint16_t es, __es_unused;
	uint16_t cs, __cs_unused;
	uint16_t ss, __ss_unused;
	uint16_t ds, __ds_unused;
	uint16_t fs, __fs_unused;
	uint16_t gs, __gs_unused;
	uint16_t ldt_selector, __ldt_sel_unused;
	uint16_t debug_flag, io_map;
} /*__attribute__ ((packed))*/;

/* Descripteur de segment */
struct idtdesc {
	uint16_t offset0_15;
	uint16_t select;
	uint16_t type;
	uint16_t offset16_31;
} /*__attribute__ ((packed))*/;

/* Registre IDTR */
struct idtr {
	uint16_t limite;
	uint32_t base;
} /*__attribute__ ((packed))*/;


void do_syscalls(int num);
void isr_kbd_int(void);
void isr_default_int(int id);
void init_gdt_desc(uint32_t, uint32_t, uint8_t, uint8_t, struct gdtdesc *);
void init_gdt(void);
void init_idt_desc(uint16_t, uint32_t, uint16_t, struct idtdesc *);
void init_idt(void);
void init_pic(void);
extern struct tss default_tss;

#endif
