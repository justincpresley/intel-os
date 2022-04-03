#include <stdint.h>

#include "common.h"
#include "screen.h"
#include "pcb.h"
#include "idt.h"
#include "process.h"
#include "pic.h"
#include "timer_device.h"

extern void go();

extern void p1();
extern void p2();
extern void p3();
extern void p4();
extern void p5();

// Start of Program
int main(){
	k_clearscr(CONSOLE_ROWS, CONSOLE_COLS);

	int screen_text_length = 18;
	char* screen_text = "Running Processes:";
	k_print(screen_text, screen_text_length, 0, 0);

	init_idt();
	init_timer_device(50);
	setup_pic();

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
	}
}
void p2(){
  int i = 0;
  char proc_msg[16] = {'p','r','o','c','e','s','s',' ','p','2',':',' ','0','0','0'};
  while(1){
    num_to_str(i, proc_msg+12);
    k_print(proc_msg, sizeof(proc_msg), 4, 0);
    i = ((i+1)%500);
  }
}
void p3(){
  int i = 0;
  char proc_msg[16] = {'p','r','o','c','e','s','s',' ','p','3',':',' ','0','0','0'};
  while(1){
    num_to_str(i, proc_msg+12);
    k_print(proc_msg, sizeof(proc_msg), 5, 0);
    i = ((i+1)%500);
  }
}
void p4(){
  int i = 0;
  char proc_msg[16] = {'p','r','o','c','e','s','s',' ','p','4',':',' ','0','0','0'};
  while(1){
    num_to_str(i, proc_msg+12);
    k_print(proc_msg, sizeof(proc_msg), 6, 0);
    i = ((i+1)%500);
  }
}
void p5(){
  int i = 0;
  char proc_msg[16] = {'p','r','o','c','e','s','s',' ','p','5',':',' ','0','0','0'};
  while(1){
    num_to_str(i, proc_msg+12);
    k_print(proc_msg, sizeof(proc_msg), 7, 0);
    i = ((i+1)%500);
  }
}