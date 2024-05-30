#pragma once
void decompress_file(char *before, char * after);
int calculating_frequences(FILE* from, tree* list[256], Codes* codes[256]);\
void tree_reconstruction_1(int n, unsigned char result[65536], unsigned char * CodingTreeString);
int tree_reconstruction_2(tree *new, int step, unsigned char TreeString[65536]);
unsigned char  ASCII_binaryCode_to_char(unsigned char a[9]);
int myPow (const int x, int n, int y, int res);