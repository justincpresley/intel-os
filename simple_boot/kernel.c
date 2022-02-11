// Function Prototypes
void k_clearscr(int numrow, int numcol);
void k_print(char* string, int string_length, int row, int col);
void print_border(int start_row, int start_col, int end_row, int end_col);

// Start of Program
int main(){
	// size of the terminal (default)
	int numrow = 25;
	int numcol = 80;

	// clear
	k_clearscr(numrow, numcol);
	// border
	print_border(1, 1, numrow, numcol);
	// screen text
	char* screen_text = "OS 4100";
	k_print(screen_text, 7, 12, 39-3);

	// run forever, not allowing it to return (it will encounter an error if returned)
	while(1){}
	return 0;
}


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
