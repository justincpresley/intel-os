#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

extern pcb_t* pcb_queue_head;
extern int pcb_queue_length;

extern void enqueue(pcb_t* pcb);
extern pcb_t* dequeue();

#endif//ROUND_ROBIN_H