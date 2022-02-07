#include "../IDT.h"


static idt_entry32_t idt32[IDT_SIZE];     // Actual IDT.
static idtr32_t idtr32;


void idt_install() { 
    idtr32.limit = (uint16_t)(sizeof(idt_entry32_t) * 256);
    idtr32.base = (uint32_t)&idt32; 

    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);

    __asm__ __volatile__("lidt %0" : : "memory"(idtr32));  
}


void set_idt_desc32(uint8_t entry, void* isr, uint8_t flags) {
    idt_entry32_t* descriptor = &idt32[entry];
    descriptor->isr_addr_low = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs = 0x08;
    descriptor->reserved = 0;
    descriptor->attr = flags;
    descriptor->isr_addr_high = ((uint32_t)isr >> 16) & 0xFFFF;
}
