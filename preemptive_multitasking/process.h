#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

void dispatch();

void default_handler();
int create_process(uint32_t process_entry);

#endif//PROCESS_H