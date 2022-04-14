#ifndef PCB_H
#define PCB_H

#include <stdint.h>

// process control block, has all process info
struct pcb{
	uint32_t esp;     // stack ptr
	uint32_t pid;     // process id
	uint32_t priority // process priority
	struct pcb* next; // next pcb
};
typedef struct pcb pcb_t;

extern pcb_t* current_pcb;
extern int next_pid;

extern uint32_t* allocate_stack();
extern pcb_t* allocate_pcb(uint32_t esp, uint32_t priority);

#endif//PCB_H