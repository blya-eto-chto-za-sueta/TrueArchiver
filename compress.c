#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "type.h"
#include "compress.h"
#include "printMessage.h"

void compress_file(char *before, char * after) {
    FILE *FileToArc, *Archive;

    if (!fopen(before, "rb"))
    {
        compress_file_start_opening_error();
        return;
    }
    if (!fopen(after, "rb"))
    {
        compress_file_result_opening_error();
        return;
    }

    FileToArc = fopen(before, "rb");
    Archive = fopen(after, "wb");

    compress_performance();

    tree* list[256];
    Codes* codes[256];
    int characterCount =  0, i = 0, length = 0;
    char rest =  0;

    characterCount = calculating_frequences(FileToArc, list, codes);

    if (characterCount==0) {
        empty_file_compress();
        return;
    }

    unsigned char* CodingTreeString = (unsigned char*)calloc(characterCount*256,sizeof(unsigned char));

    tree *CodingTree = make_coding_tree(characterCount, list);
    make_coding_tree_string(CodingTreeString, CodingTree);


    if (characterCount != 1)
    {
        strcpy(CodingTree->left->code, "0");
        strcpy(CodingTree->right->code, "1");
        make_codes(CodingTree->left, codes);
        make_codes(CodingTree->right, codes);
    }
    else
        strcpy(codes[CodingTree->symbol]->SymbolCode, "0");
    length = strlen(CodingTreeString);
    rest = (char)length % 8;
    for (i = length; i < length + (8 - rest); i++)
        CodingTreeString[i] = '0';
    //структура архива:  длина дерева (в байтах)  | само дерево | архив| информация о конце файла
    length = length + (8 - rest);
    length = (int)length / 8;
    fwrite(&length, 4, 1, Archive);
    recording_tree(Archive, CodingTreeString);
    coding(FileToArc, Archive, codes);

    compress_complited();

    fclose(Archive);
    fclose(FileToArc);
}


int calculating_frequences(FILE * from, tree * list[256], Codes * codes[256]) {

    int characterCount = 0;
    unsigned char symbol;

    for (int i= 0 ; i<256; i++) {
        codes[i] = (Codes*)calloc(1,sizeof(Codes));

        list[i] = (tree*)calloc(1,sizeof(tree));
        list[i]->frequency = 0;
        list[i]->right = NULL;
        list[i]->left = NULL;
    }

    while (fread(&symbol,1,1,from)==1) {
        if (list[symbol]->frequency == 0) {
            characterCount++;
            list[symbol]->symbol = symbol;
        }

        list[symbol]->frequency ++;
    }
    rewind(from);

    quick_sort(list, 256);

    return characterCount;
}

void quick_sort (tree * list[256], int N){
    int size=N;// array size
    int k=0;
    int randomIndex = rand() % size;
    tree* c=list[randomIndex];
    tree* tmp ;// buffer
    N--;
    do{
        while (list[k]->frequency >c->frequency) k++;
        while(list[N]->frequency < c->frequency) N--;

        if (k<=N){
            tmp=list[k];
            list[k]=list[N];
            list[N]=tmp;
            k++;
            N--;
        }
    }while(k<=N);
    if(N>0) quick_sort(list,N+1);
    if (size>k) quick_sort(&list[k],size-k);
}

tree* make_coding_tree(int n, tree* list[256]) {
    tree *NewNode = NULL;
    if (n == 1)
    {
        NewNode = (tree*)malloc(sizeof(tree));
        NewNode->frequency = list[0]->frequency;
        NewNode->right = NULL;
        NewNode->left = NULL;
        NewNode->symbol = list[0]->symbol;
    }
    while (n != 1)
    {
        NewNode = (tree*)malloc(sizeof(tree));
        NewNode->frequency = list[n - 1]->frequency + list[n - 2]->frequency;
        NewNode->right = list[n - 1];
        NewNode->left = list[n - 2];
        for (int i = 0; i < n; i++){
            if (NewNode->frequency > list[i]->frequency){
                for (int j = n - 1; j > i; j--)
                    list[j] = list[j - 1];
                list[i] = NewNode;
                break;
            }
        }
        n--;
    }
    return NewNode;
}


void make_coding_tree_string(unsigned char* CodingTreeString, tree* CodingTree) {
    int length;
    if (CodingTree->left != NULL)
    {
        length = strlen(CodingTreeString);
        CodingTreeString[length] = '0';
        CodingTreeString[length + 1] = '\0';
        make_coding_tree_string(CodingTreeString, CodingTree->left);
    }
    if (CodingTree->right != NULL)
    {
        make_coding_tree_string(CodingTreeString, CodingTree->right);
    }
    else
    {
        length = strlen(CodingTreeString);
        CodingTreeString[length] = '1';
        CodingTreeString[length + 1] = '\0';
        strcat(CodingTreeString, binary_symbol(CodingTree->symbol));
        length = strlen(CodingTreeString);
        CodingTreeString[length + 1] = '\0';
    }
}

void make_codes(tree *CodingTree, Codes * codes[256]){
    if (CodingTree->left != NULL){
        strcpy(CodingTree->left->code, CodingTree->code);
        strcat(CodingTree->left->code, "0");
        make_codes(CodingTree->left, codes);}

    if (CodingTree->right != NULL){
        strcpy(CodingTree->right->code, CodingTree->code);
        strcat(CodingTree->right->code, "1");
        make_codes(CodingTree->right, codes);}

    else{
        strcpy(codes[CodingTree->symbol]->SymbolCode, CodingTree->code);
        codes[CodingTree->symbol]->c = CodingTree->symbol;}
}

void recording_tree(FILE* Archive, unsigned char* CodingTreeString){
    int sum = 0;
    unsigned char eight[9];
    unsigned char byte = 0;
    for (int i = 0; i < strlen(CodingTreeString); i++)
    {
        eight[sum] = CodingTreeString[i];
        sum++;
        if (sum == 8)
        {
            sum = 0;
            eight[8] = '\0';
            byte = byte_creation(eight);
            fwrite(&byte, 1, 1, Archive);
            byte = 0;
            memset(eight, 0, 9);
        }
    }
}

unsigned char byte_creation(unsigned char eight[9]){
    unsigned char byte = 0;
    int i;
    for (i = 0; i < 8; i++)
    {
        byte = byte | ((eight[i] - '0') << i);
    }
    return byte;
}

void coding(FILE* FileToArc, FILE* Archive, Codes *codes[256])
{
    unsigned char byte = 0;
    unsigned char symbol;
    int sum = 0;
    unsigned char eight[9];
    int counter = 0;
    while (fread(&symbol, 1, 1, FileToArc))
    {
        for (int i = 0; i < strlen(codes[symbol]->SymbolCode); i++)
        {
            eight[sum] = codes[symbol]->SymbolCode[i];
            sum++;
            if (sum == 8)
            {
                sum = 0;
                eight[8] = '\0';
                byte = byte_creation(eight);
                fwrite(&byte, 1, 1, Archive);
                counter++;
                byte = 0;
                memset(eight, 0, 9);
            }
        }
    }
    for (int i = sum; i < 8; i++)
        eight[i] = '0';
    eight[8] = '\0';
    byte = byte_creation(eight);
    fwrite(&byte, 1, 1, Archive);
    byte = 0;
    char end;
    end = (char)(8 - sum);
    fwrite(&end, 1, 1, Archive);
}

unsigned char* binary_symbol(unsigned char symbol){

    unsigned char* result =(unsigned char*)calloc(9,sizeof(unsigned char));
    unsigned char* r = (unsigned char*)calloc(9,sizeof(unsigned char));
    int c, i = 0, lenght, j = 0;
    c = (int)symbol;
    while (c != 0)
    {
        result[i] = c % 2;
        result[i] = result[i] + '0';
        c = c / 2;
        i++;
    }
    lenght = i;
    if (lenght < 8)
    {
        for (j = 0; j < 8 - lenght; j++)
            r[j] = '0';

    }
    for (i = lenght - 1; i >= 0; i--)
    {
        r[j] = result[i];
        j++;
    }
    r[8] = '\0';
    return r;
}