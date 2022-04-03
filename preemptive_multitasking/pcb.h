#ifndef PCB_H
#define PCB_H

#include <stdint.h>

#include "common.h"

// process control block, has all process info
struct pcb{
	uint32_t esp;     // stack ptr
	uint32_t pid;     // process id
	struct pcb* next; // next pcb
};
typedef struct pcb pcb_t;

extern pcb_t* current_pcb;
extern int next_pid;

extern uint32_t* allocate_stack();
extern pcb_t* allocate_pcb(uint32_t esp);

#endif//PCB_H