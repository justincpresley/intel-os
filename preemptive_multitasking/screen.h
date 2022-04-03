#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

void k_print(char* string, int string_length, int row, int col);

void k_clearscr(int numrow, int numcol);
void print_border(int start_row, int start_col, int end_row, int end_col);

void num_to_str(uint32_t num, char buf[]);

#endif//SCREEN_H