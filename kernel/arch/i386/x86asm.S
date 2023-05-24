.macro	SAVE_REGS 
	pushal 
	push %ds 
	push %es 
	push %fs 
	push %gs 
	push %ebx 
	mov $0x10, %bx 
	mov %bx, %ds 
	pop %ebx
.endm

.macro RESTORE_REGS 
	pop %gs
	pop %fs
	pop %es
	pop %ds
	popal
.endm

.global init_segments, end_init_arch

init_segments:
    movw $0x10, %ax
	movw %ax, %ds
    movw %ax, %es   
    movw %ax, %fs   
    movw %ax, %gs   
    movw %ax, %ss   
    ljmp $0x08, $next
    ret

next:  
    movw $0x18, %ax
    movw %ax, %ss
    movl $0x0009FFF0, %esp
    ret

end_init_arch:
    movw $0x38, %ax
    ltr %ax
    ret

.extern isr_default_int, do_syscalls, isr_schedule_int, isr_GP_exc, isr_PF_exc 
.global _asm_int_1, _asm_int_0, _asm_syscalls, _asm_exc_GP, _asm_exc_PF, _asm_schedule

_asm_int_1:
    SAVE_REGS
	push 1
    call isr_default_int 
    pop %eax
	mov $0x20, %al
	out %al, $0x20 
    RESTORE_REGS
    iret

_asm_int_0:
    SAVE_REGS
	push 0
    call isr_default_int 
    pop %eax
	mov $0x20, %al
	out %al, $0x20 
    RESTORE_REGS
    iret

_asm_syscalls:
    SAVE_REGS
    push %eax                
	call do_syscalls
	pop %eax
    cli
    sti
    RESTORE_REGS
    iret

_asm_exc_GP:
    SAVE_REGS
	call isr_GP_exc
	RESTORE_REGS
    add 4, %esp
    iret

_asm_exc_PF:
    SAVE_REGS
	call isr_PF_exc
	RESTORE_REGS
    add 4, %esp
    iret

_asm_schedule:
    SAVE_REGS
	call isr_schedule_int
	mov $0x20, %al 
	out %al, $0x20
	RESTORE_REGS
	iret

.extern kgdtr, kidtr
.global _load_gdt, _load_idt

_load_gdt:
    lgdtl (kgdtr)

_load_idt:
    lidtl (kidtr)