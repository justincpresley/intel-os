#include "pcb.h"
#include "common.h"

uint32_t allocated_stacks[MAX_PROCESS_ALLOCATIONS][STACK_SIZE];
pcb_t allocated_pcbs[MAX_PROCESS_ALLOCATIONS];

pcb_t* allocate_pcb(){ return &allocated_pcbs[next_pid]; }
uint32_t* allocate_stack(){ return allocated_stacks[next_pid]; }