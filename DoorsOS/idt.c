#include "include/stdint.h"
#include "interrupts/idt.h"

void set_idt_gate(int n, unsigned long handler) {
    idt[n].base_low = handler & 0xFFFF;
    idt[n].sel = 0x08; // Segmento de código do kernel
    idt[n].flags = 0x8E; // Presente, Ring 0, Interrupção 32-bit
    idt[n].base_high = (handler >> 16) & 0xFFFF;
}