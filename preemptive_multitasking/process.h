#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

extern void default_handler();
extern int create_process(uint32_t process_entry);

#endif//PROCESS_H