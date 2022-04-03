#include <stdint.h>

#include "common.h"
#include "screen.h"
#include "pcb.h"

#define IDT_SIZE 256

// Expected ASM Functions
// * k_print
// * lidtr
// * go
// * dispatch

// Structures
// an entry within the interrupt descriptor table
struct idt_entry {
	uint16_t base_low16;
	uint16_t selector;
	uint8_t always0;
	uint8_t access;
	uint16_t base_high16;
} __attribute__((packed));
typedef struct idt_entry idt_entry_t;
// struct for intel idt assembler instruction
struct idtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
typedef struct idtr idtr_t;


// Globals
int console_num_rows = 25;
int console_num_cols = 80;

int next_pid = 0;
idt_entry_t idt[IDT_SIZE]; // interrupt descriptor table

pcb_t* pcb_queue_head = NULL;
int pcb_queue_length = 0;
pcb_t* current_pcb = NULL;


// Function Prototypes
// Process Functions
void enqueue(pcb_t* pcb);
pcb_t* dequeue();
void init_idt_entry(idt_entry_t* entry, uint32_t base, uint16_t selector, uint8_t access);
void init_idt();
void go();
void dispatch();
void default_handler();
void lidtr(idtr_t* idtr);
int create_process(uint32_t process_entry);
// Processes
void p1();
void p2();
void p3();
void p4();
void p5();

// Start of Program
int main(){
	k_clearscr(console_num_rows, console_num_cols);

	int screen_text_length = 18;
	char* screen_text = "Running Processes:";
	k_print(screen_text, screen_text_length, 0, 0);

	init_idt();

	// add all processes
	int retval;
	retval = create_process((uint32_t)&p1);
	retval = create_process((uint32_t)&p2);
	retval = create_process((uint32_t)&p3);
	retval = create_process((uint32_t)&p4);
	retval = create_process((uint32_t)&p5);

	// begin runnning processes
	go();
	return 0;
}

// Processes
void p1(){
	int i = 0;
	char proc_msg[16] = {'p','r','o','c','e','s','s',' ','p','1',':',' ','0','0','0'};
	while(1){
		num_to_str(i, proc_msg+12);
		k_print(proc_msg, sizeof(proc_msg), 3, 0);
		i = ((i+1)%500);
		asm("int $32"); // Call dispatcher
	}
}
void p2(){
  int i = 0;
  char proc_msg[16] = {'p','r','o','c','e','s','s',' ','p','2',':',' ','0','0','0'};
  while(1){
    num_to_str(i, proc_msg+12);
    k_print(proc_msg, sizeof(proc_msg), 4, 0);
    i = ((i+1)%500);
    asm("int $32"); // Call dispatcher
  }
}
void p3(){
  int i = 0;
  char proc_msg[16] = {'p','r','o','c','e','s','s',' ','p','3',':',' ','0','0','0'};
  while(1){
    num_to_str(i, proc_msg+12);
    k_print(proc_msg, sizeof(proc_msg), 5, 0);
    i = ((i+1)%500);
    asm("int $32"); // Call dispatcher
  }
}
void p4(){
  int i = 0;
  char proc_msg[16] = {'p','r','o','c','e','s','s',' ','p','4',':',' ','0','0','0'};
  while(1){
    num_to_str(i, proc_msg+12);
    k_print(proc_msg, sizeof(proc_msg), 6, 0);
    i = ((i+1)%500);
    asm("int $32"); // Call dispatcher
  }
}
void p5(){
  int i = 0;
  char proc_msg[16] = {'p','r','o','c','e','s','s',' ','p','5',':',' ','0','0','0'};
  while(1){
    num_to_str(i, proc_msg+12);
    k_print(proc_msg, sizeof(proc_msg), 7, 0);
    i = ((i+1)%500);
    asm("int $32"); // Call dispatcher
  }
}

// Process Functions
void enqueue(pcb_t* pcb){
	if(pcb_queue_length == 0){
		pcb_queue_head = pcb;
	}else{
		int i = pcb_queue_length;
		pcb_t* temp = pcb_queue_head;
		while(--i != 0){
			temp = temp->next;
		}
		temp->next = pcb;
	}
	pcb_queue_length++;
}
pcb_t* dequeue(){
	if(pcb_queue_length == 0){
		return NULL;
	}
	pcb_t* temp = pcb_queue_head;
	pcb_queue_head = pcb_queue_head->next;
	pcb_queue_length--;
	return temp;
}
void init_idt_entry(idt_entry_t* entry, uint32_t base, uint16_t selector, uint8_t access){
	entry->base_low16 = (uint16_t) ((uint32_t) base & 0x0000FFFF);
	entry->base_high16 = (uint16_t) (((uint32_t) base & 0xFFFF0000) >> 16);
	entry->selector = selector;
	entry->access = access;
	entry->always0 = 0;
}
void init_idt(){
	for(int i=0; i<IDT_SIZE; i++){
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
	idtr.limit = (sizeof(idt_entry_t) * IDT_SIZE) - 1;
	idtr.base = (uint32_t)&idt;
	lidtr(&idtr);
}
void default_handler(){
	// print an error
	int screen_text_length = 31;
	char* screen_text = "ERROR: Entering Default Handler";
	k_print(screen_text, screen_text_length, 24, 0);
	// run forever, not allowing return as it would cause an error
	while(1);
}
int create_process(uint32_t process_entry){
	if (next_pid >= MAX_PROCESS_ALLOCATIONS){
		return 1; // max processes error, can not allocated any more
	}
	uint32_t* stackptr = allocate_stack();
	uint32_t* st = stackptr + STACK_SIZE;

	// Stack Setup
	// 0x000 for no interrupts
	st--;
	*st = 0x000;
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

	pcb_t* pcb = allocate_pcb();
	pcb->esp = (uint32_t)st;
	pcb->pid = next_pid;
	pcb->next = NULL;

	next_pid++;
	enqueue(pcb);
	return 0; // no errors
}