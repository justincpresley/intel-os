#include <stdint.h>
#include <limits.h>

#include "common.h"
#include "screen.h"
#include "pcb.h"
#include "idt.h"
#include "process.h"
#include "pic.h"
#include "timer_device.h"

extern void p1();
extern void p2();
extern void p3();
extern void p4();
extern void p5();

// Start of Program
int main(){
	k_clearscr(CONSOLE_ROWS, CONSOLE_COLS);
	print_border(1, 1, CONSOLE_ROWS, CONSOLE_COLS);
	k_print("| OS Status: RUNNING  |", 23, CONSOLE_ROWS-1, CONSOLE_COLS-26);

	init_idt();
	init_timer_device(50);
	setup_pic();

	// add all processes
	int retval;
	retval = create_process((uint32_t)&idle, 5);
	retval = create_process((uint32_t)&p1, 10);
	retval = create_process((uint32_t)&p2, 10);
	retval = create_process((uint32_t)&p3, 15);

	// begin runnning processes
	go();
	return 0;
}

// Processes
void p1(){
	int i = 0;
  char proc_msg[16] = {'p','r','o','c','e','s','s',' ','p','1',':',' ','0','0','0'};
  while(i < INT_MAX/100){
    num_to_str(i%999, proc_msg+12);
    k_print(proc_msg, sizeof(proc_msg), 3, 1);
    i += 1;
  }
	k_print("DONE", 4, 3, 13);
}
void p2(){
	int i = 0;
  char proc_msg[16] = {'p','r','o','c','e','s','s',' ','p','2',':',' ','0','0','0'};
  while(i < INT_MAX/100){
    num_to_str(i%999, proc_msg+12);
    k_print(proc_msg, sizeof(proc_msg), 4, 1);
    i += 1;
  }
	k_print("DONE", 4, 4, 13);
}
void p3(){
  int i = 0;
  char proc_msg[16] = {'p','r','o','c','e','s','s',' ','p','3',':',' ','0','0','0'};
  while(i < INT_MAX/100){
    num_to_str(i%999, proc_msg+12);
    k_print(proc_msg, sizeof(proc_msg), 5, 1);
    i += 1;
  }
	k_print("DONE", 4, 5, 13);
}