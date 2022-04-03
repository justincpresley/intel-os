#include "idt.h"
#include "process.h"

#include <stdint.h>

#define IDT_TABLE_ITEMS 256

// an entry within the interrupt descriptor table
struct idt_entry {
	uint16_t base_low16;
	uint16_t selector8;
	uint8_t always_zero8;
	uint8_t access8;
	uint16_t base_high16;
} __attribute__((packed));
typedef struct idt_entry idt_entry_t;
// struct for intel idt assembler instruction
struct idtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
typedef struct idtr idtr_t;

// interrupt descriptor table
idt_entry_t idt[IDT_TABLE_ITEMS];

void init_idt_entry(idt_entry_t* entry, uint32_t base, uint16_t selector, uint8_t access){
	entry->base_low16 = (uint16_t) ((uint32_t) base & 0x0000FFFF);
	entry->base_high16 = (uint16_t) (((uint32_t) base & 0xFFFF0000) >> 16);
	entry->selector8 = selector;
	entry->access8 = access;
	entry->always_zero8 = 0;
}

extern void lidtr(idtr_t *idtr);
extern void dispatch();

void init_idt(){
	for(int i=0; i<IDT_TABLE_ITEMS; i++){
		if(i < 32){
			// for 0-31, set to point to the default handler
      init_idt_entry(idt+i, (uint32_t)&default_handler, 16, 0x8e);
    }else if(i == 32){
			// for 32, set it to point to dispatcher function
			init_idt_entry(idt+i, (uint32_t)&dispatch, 16, 0x8e);
    }else if(i > 33){
			// for 33-255, set it to point to 0
			init_idt_entry(idt+i, 0, 0, 0);
		}
	}
	idtr_t idtr;
	idtr.limit = (sizeof(idt_entry_t) * IDT_TABLE_ITEMS) - 1;
	idtr.base = (uint32_t)&idt;
	lidtr(&idtr);
}