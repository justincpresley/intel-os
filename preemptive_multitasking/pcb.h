#ifndef PCB_H
#define PCB_H

#include <stdint.h>

// process control block, has all process info
struct pcb{
	uint32_t esp;     // stack ptr
	uint32_t pid;     // process id
	struct pcb* next; // next pcb
};
typedef struct pcb pcb_t;

uint32_t* allocate_stack();
pcb_t* allocate_pcb();

#endif//PCB_H