#include "process.h"
#include "common.h"
#include "pcb.h"
#include "screen.h"
#include "round_robin.h"

void idle(){
  int screen_text_length = 31;
  char* screen_text = "| OS Status: IDLE  /  |";
  k_print(screen_text, screen_text_length, CONSOLE_ROWS-1, CONSOLE_COLS-26);
  while(1){
    k_print("\\", 1, CONSOLE_ROWS-1, CONSOLE_COLS-7);
    k_print("/", 1, CONSOLE_ROWS-1, CONSOLE_COLS-7);
  }
}

void default_handler(){
	// print an error
	int screen_text_length = 31;
	char* screen_text = "| OS Status: ERROR    |";
	k_print(screen_text, screen_text_length, CONSOLE_ROWS-1, CONSOLE_COLS-26);
	// run forever, not allowing return as it would cause an error
	while(1);
}

int create_process(uint32_t process_entry, uint32_t priority){
  if (next_pid >= MAX_PROCESS_ALLOCATIONS){
		return 1; // max processes error, can not allocated any more
	}
	uint32_t* stackptr = allocate_stack();
	uint32_t* st = stackptr + STACK_SIZE;

	// Stack Setup
	// Address to jump to after Exit
	st--;
	*st = go;
	// Time quantum interrupts
	st--;
	*st = 512;
	// CS
	st--;
	*st = 16;
	// Address of process
	st--;
	*st = process_entry;
	// EBP
	st--;
	*st = 0;
	// ESP
	st--;
	*st = 0;
	// EDI
	st--;
	*st = 0;
	// ESI
	st--;
	*st = 0;
	// EDX
	st--;
	*st = 0;
	// ECX
	st--;
	*st = 0;
	// EBX
	st--;
	*st = 0;
	// EAX
	st--;
	*st = 0;
	// DS
	st--;
	*st = 8;
	// ES
	st--;
	*st = 8;
	// FS
	st--;
	*st = 8;
	// GS
	st--;
	*st = 8;

	enqueue(allocate_pcb((uint32_t)st, priority));
	return 0; // no errors
}