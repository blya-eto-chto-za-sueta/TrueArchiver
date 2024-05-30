#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "type.h"
#include "printMessage.h"
#include "decompress.h"
# pragma comment ( linker , "/ STACK :50000000 ")

void decompress_file(char *before, char * after) {
    FILE *Archive, *NewFile;

    if (!fopen(before, "rb"))
    {
        decompress_file_archive_opening_error();
        return;
    }
    if (!fopen(after, "rb"))
    {
        decompress_file_result_opening_error();
        return;
    }

    Archive = fopen(before, "rb");
    NewFile = fopen(after, "wb");
    decompress_performance();

    int length;
	unsigned long long characterCount = 0;
	unsigned char byte;
	char rest;

	while (fread(&byte, 1, 1, Archive))
		characterCount++;
	if (characterCount == 0)
	{
		empty_file_decompress();
		getchar();
		return;
	}

	rest = byte;
	rewind(Archive);

	fread(&length, 4, 1, Archive);
	characterCount = characterCount - length - 1;

	int b, i, j, k;
	unsigned char* C = (unsigned char*)calloc(65536, sizeof(unsigned char));

	k = 0;
	for (i = 0; i < length; i++)
	{
		fread(&byte, 1, 1, Archive);
		for (j = 0; j < 8; j++)
		{
			b = (byte & 1);
			byte >>= 1;
			C[k] = (unsigned char)(b + '0');
			k++;
		}
	}
	C[k] = '\0';

	unsigned char* TreeString = (unsigned char*)calloc(65536, sizeof(unsigned char));


	tree_reconstruction_1(length*8, TreeString, C);
	tree * new = NULL, *head;
	new = (tree*)malloc(sizeof(tree));
	head = new;
	int step = 0;
	step = tree_reconstruction_2(new, step, TreeString);
	head = new;
	//rest - количество незадействованных битов в последнем байте
	tree * root = head;
	char end = 8;
	if (root->right == NULL || root->left == NULL)
	{
		fwrite(&root->symbol, 1, 1, NewFile);
		fclose(Archive);
		fclose(NewFile);
		return;
	}

	for(k = 0; k < characterCount - 5; k++)
	{
		fread(&byte, 1, 1, Archive);
		for (i = 0; i < end; i++)
		{
			if ((byte & (1 << i)) == 0)
			{
				root = root->left;
				if (root->left == NULL && root->left == NULL)
				{
					fwrite(&root->symbol, 1, 1, NewFile);
					root = head;
				}

			}
			else
			{
				root = root->right;
				if (root->left == NULL && root->left == NULL)
				{
					fwrite(&root->symbol, 1, 1, NewFile);
					root = head;
				}
			}
		}
	}
	fread(&byte, 1, 1, Archive);
	for (i = 0; i < 8 - rest; i++)
	{
		if ((byte & (1 << i)) == 0)
		{
			root = root->left;
			if (root->left == NULL && root->left == NULL)
			{
				fwrite(&root->symbol, 1, 1, NewFile);
				root = head;
			}

		}
		else
		{
			root = root->right;
			if (root->left == NULL && root->left == NULL)
			{
				fwrite(&root->symbol, 1, 1, NewFile);
				root = head;
			}
		}
	}
	decompress_complited();
	fclose(Archive);
	fclose(NewFile);
}

void tree_reconstruction_1(int n, unsigned char result[65536], unsigned char * CodingTreeString) {
	int i = 0, j = 0, k = 0;
	unsigned char eight[9];
	for (i = 0; i < n; i++)
	{
		result[j] = CodingTreeString[i];
		j++;
		if (CodingTreeString[i] == '1')
		{
			i++;
			for (k = 0; k < 8; k++)
			{
				eight[k] = CodingTreeString[i];
				i++;
			}
			i--;
			eight[8] = '\0';
			result[j] = ASCII_binaryCode_to_char(eight);
			j++;
			memset(eight, 0, 9);
		}
	}
	result[j] = '\0';
}
unsigned char  ASCII_binaryCode_to_char(unsigned char a[9]) {
	int i = 0, k, st, sum = 0, x = 0;
	unsigned char c;
	while (a[i] != '\0')
	{
		i++;
	}
	k = i;
	int count = 0;
	for (i = k - 1; i >= 0; i--)
	{
		st = myPow(2,0,i,1);
		x = (a[count] - '0') * st;
		sum += x;
		count++;
	}
	c = sum;
	return c;
}

int tree_reconstruction_2(tree *new, int step, unsigned char TreeString[65536]) {
	if (TreeString[step] == '0')
	{
		tree *newLeafe1 = NULL;
		newLeafe1 = (tree*)malloc(sizeof(tree));
		newLeafe1->left = newLeafe1->right = NULL;
		new->left = newLeafe1;

		tree *newLeafe2 = NULL;
		newLeafe2 = (tree*)malloc(sizeof(tree));
		newLeafe2->left = newLeafe2->right = NULL;
		new->right = newLeafe2;

		step = tree_reconstruction_2(new->left, step + 1, TreeString);
		step = tree_reconstruction_2(new->right, step + 1, TreeString);
		return step;
	}
	else
	{
		step++;
		new->symbol = TreeString[step];
		new->left = NULL;
		new->right = NULL;
		return step;
	}
}

int myPow (const int x, int n, int y, int res){
	if (n==y) return res;
	else {
		myPow(x,n+1,y,res*x);
	}

}