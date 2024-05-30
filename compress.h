#pragma once
#include "type.h"
void compress_file(char *before, char * after);
int calculating_frequences(FILE * from, tree * list[256], Codes * codes[256]);
void quick_sort(tree * list[256], int N);
tree* make_coding_tree(int n, tree* list[256]);
void make_coding_tree_string(unsigned char* CodingTreeString, tree* CodingTree);
void make_codes(tree *CodingTree, Codes * codes[256]);
unsigned char byte_creation(unsigned char eight[9]);
void recording_tree(FILE* Archive, unsigned char* CodingTreeString);
void coding(FILE* FileToArc, FILE* Archive, Codes *codes[256]);
unsigned char* binary_symbol(unsigned char symbol);