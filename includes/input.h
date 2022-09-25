#ifndef INPUT_H
#define INPUT_H


void flush_input_buffer();
int read_input(char *str, int count);
int read_capital_letter();
int* strtoi(char* str, int* nb);
int* read_integer(int* nb);


#endif
