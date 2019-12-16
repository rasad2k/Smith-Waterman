#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile(FILE * fp, char * str);
char max(char a, char b, char c);
char ** initTable(char * test, char * buf);
void printTable(char ** table);
void printFillTable(char * test, char * str, char match, char mismatch, char gap);
char * traceback(char ** table, char x, char y);
