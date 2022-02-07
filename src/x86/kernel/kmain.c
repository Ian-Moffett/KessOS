#include "interrupts/IDT.h"
#include "interrupts/exceptions.h"
#include "drivers/VGA/VGA.h"
#include "drivers/IO/IO.h"
#include "kshell/shellutils.h"

char* vga = (char*)0xB8000;

void panic(const char* const PANIC_MESSAGE) { 
    clearScreen(&vga, 0x4, 0xFE);
    kputs("***KERNEL PANIC***", &vga, 2);
    kputs(PANIC_MESSAGE, &vga, 1);
    __asm__ __volatile__("cli; hlt");
}


int main() {
    idt_install();
    set_idt_desc32(0x0, div_0_ex, TRAP_GATE_FLAGS);
    set_idt_desc32(0x4, overflow_ex, TRAP_GATE_FLAGS);
    set_idt_desc32(0x5, bre_ex, TRAP_GATE_FLAGS);
    set_idt_desc32(0x6, invld_opcode_ex, TRAP_GATE_FLAGS);
    set_idt_desc32(0x7, dev_na_ex, TRAP_GATE_FLAGS);
    set_idt_desc32(0x8, double_fault_ex, TRAP_GATE_FLAGS);
    set_idt_desc32(0x9, cso_ex, TRAP_GATE_FLAGS);
    set_idt_desc32(0xA, invld_tss_ex, TRAP_GATE_FLAGS);
    set_idt_desc32(0xB, seg_np_ex, TRAP_GATE_FLAGS);
    set_idt_desc32(0xC, ss_fault_ex, TRAP_GATE_FLAGS);
    set_idt_desc32(0xD, gp_fault_ex, TRAP_GATE_FLAGS);
    set_idt_desc32(0xE, page_fault_ex, TRAP_GATE_FLAGS);
    set_idt_desc32(0xF, float_ex, TRAP_GATE_FLAGS);
    set_idt_desc32(0x21, irq1_isr, INT_GATE_FLAGS);

    outportb(0x3D4, 0x0A);
    outportb(0x3D5, 0x20);

    outportb(0x21, 0xFF);
    outportb(0x21, inportb(0x21) ^ (1 << 1));

    __asm__ __volatile__("sti");

    clearScreen(&vga, 0x1, 0xE);
    kputs("root@KessOS~$ ", &vga, 0);
    *(vga + 2) = '|';
    return 0;
}
