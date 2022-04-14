#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

extern void go();

extern void idle();
extern void default_handler();
extern int create_process(uint32_t process_entry, uint32_t priority);

#endif//PROCESS_H