#include "screen.h"

void k_clearscr(int numrow, int numcol){
	int i; // temp variable for work
	// make a char array to print one row
	char arr[numcol];
	for(i=0; i<numcol; i++){
		arr[i] = ' '; // blank
	}
	// print each row with row char array
	i = 0;
	while(i < numrow){
		k_print(arr, numcol, i, 0);
		i = i + 1;
	}
}

void print_border(int start_row, int start_col, int end_row, int end_col){
	int i; // temp variable for work
	int numcol = end_col - start_col + 1;
	int numrow = end_row - start_row + 1;
	// make the arr for top and bottom of the box
  char tbarr[numcol];
  for(i=0; i<numcol; i++){
		if(i == 0 || i == numcol-1){
			tbarr[i] = '+';
		}else{
      tbarr[i] = '-';
    }
	}
	// print based on row
	char* sidechar = "|";
	for(i=0; i<numrow; i++){
		if(i == 0 || i == numrow-1){
			// bottom or top
			k_print(tbarr, numcol, i+(start_row-1), start_col-1);
		}else{
			// in the middle
			k_print(sidechar, 1, i+(start_row-1), start_col-1); // left
			k_print(sidechar, 1, i+(start_row-1), end_col-1); // right
		}
	}
}

int num_to_str_helper(uint32_t num, char buf[]){
	if(num == 0){ return 0; }
	int idx = num_to_str_helper((num / 10), buf);
	buf[idx] = num % 10 + '0';
	buf[idx+1] = '\0';
	return idx + 1;
}
void num_to_str(uint32_t num, char buf[]){
	if(num == 0){
		buf[0] = '0';
		buf[1] = '\0';
	}else{
		num_to_str_helper(num, buf);
	}
}
