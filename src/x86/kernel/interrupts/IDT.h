#ifndef IDT_H
#define IDT_H

#define IDT_SIZE 256

#define TRAP_GATE_FLAGS 0x8F
#define INT_GATE_FLAGS 0x8E
#define INT_GATE_USER_FLAGS 0xEE

#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT 0x21

#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT 0xA1


#include "../drivers/IO/IO.h"
#include <stdint.h>
#include <stddef.h>

/* 
 * Each entry describes where ISR
 * is located in memory to service
 * the interrupt.
 */

typedef struct {
    uint16_t isr_addr_low;
    uint16_t kernel_cs;         // Code segment where the ISR is.
    uint8_t reserved;           // Reserved by intel for some reason.
    uint8_t attr;
    uint16_t isr_addr_high;
} __attribute__((packed)) idt_entry32_t;


/*
 *  IDTR describes where in memory
 *  the IDT is.
 */

typedef struct {
    uint16_t limit;         // Max address of IDT.
    uint32_t base;          // Lowest address of IDT.
} __attribute__((packed)) idtr32_t;

typedef struct {
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t sp;
    uint32_t ss;
} __attribute__((packed)) int_frame32_t;


/*
 * Interrupt attribute will
 * return with IRET, not RET.
 */


void set_idt_desc32(uint8_t entry, void* isr, uint8_t flags);
void idt_install();

#endif
