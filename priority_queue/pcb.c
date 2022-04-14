#include "pcb.h"
#include "common.h"

pcb_t* current_pcb = NULL;
int next_pid = 0;
uint32_t allocated_stacks[MAX_PROCESS_ALLOCATIONS][STACK_SIZE];
pcb_t allocated_pcbs[MAX_PROCESS_ALLOCATIONS];

pcb_t* allocate_pcb(uint32_t esp, uint32_t priority){
  pcb_t* pcb = &allocated_pcbs[next_pid];
  pcb->esp = esp;
	pcb->pid = next_pid;
  pcb->priority = priority;
	pcb->next = NULL;
  next_pid++;
  return pcb;
}

uint32_t* allocate_stack(){
  return allocated_stacks[next_pid];
}