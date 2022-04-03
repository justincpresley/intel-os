#include <stdint.h>

#include "common.h"
#include "screen.h"
#include "pcb.h"
#include "idt.h"
#include "process.h"

// Globals
int console_num_rows = 25;
int console_num_cols = 80;

pcb_t* pcb_queue_head = NULL;
int pcb_queue_length = 0;

// Function Prototypes
// Process Functions
void enqueue(pcb_t* pcb);
pcb_t* dequeue();
void go();
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