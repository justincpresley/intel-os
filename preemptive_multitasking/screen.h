#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

extern void k_print(char* string, int string_length, int row, int col);

extern void k_clearscr(int numrow, int numcol);
extern void print_border(int start_row, int start_col, int end_row, int end_col);

extern void num_to_str(uint32_t num, char buf[]);

#endif//SCREEN_H