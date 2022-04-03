#include "round_robin.h"
#include "common.h"

pcb_t* pcb_queue_head = NULL;
int pcb_queue_length = 0;

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