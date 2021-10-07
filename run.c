#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
//#include "jaarowinkler.h"

#define WORD_LEN 256
#define TABLE_SIZE 676
#define MAX_INPUT 100

typedef struct node
{
    char word[WORD_LEN + 1];
    struct node *next;
} node;

// hashtable functions
int djb2(unsigned char *str);
long int load(const char *dict_name, node *table[]);
void init_table(node *table[]);
void print_branch(node *ptr);
void unload(node *table[]);
bool find(node *table[], const char *str);

int max_array(int arr[], int n);
void print_array(int arr[], int n);

// caesar shift functions
void encode(char *str, int key);

node *table[TABLE_SIZE];
char input[MAX_INPUT][WORD_LEN + 1];
int all_shifts[26] = {0};

int main(int argc, char *argv[])
{
	init_table(table);
	long int size = load("dict", table);
  
	// Copy argv into input
	int i = 0;
	for (char **p = argv + 1; p < argv + argc; p++)
		strcpy(input[i++], *p);
	
	for (int j = 0; j < 26; j++)
	{
		for (int k = 0; k < i; k++)
		{
			char tmp[WORD_LEN];
			strcpy(tmp, input[k]);

			encode(tmp, j);
			if (find(table, tmp))
				all_shifts[j]++;
		}
	}
	int correct_key = (26 - max_array(all_shifts, 26)) % 26;
		
	printf("\n\n");
	for (int j = 0; j < i; j++)
	{	
		encode(input[j], 26 - correct_key);
		printf("%s ", input[j]);
	}
	printf("\n\n");

	printf("Key seems to be %d\n", correct_key);
	unload(table);
}

int max_array(int arr[], int n)
{
	int max_value = arr[n - 1];
	int max_index = n - 1;
	while ((n--) > 0)
	{
		if (arr[n] > max_value)
		{
			max_value = arr[n];
			max_index = n;
		}
	}
	return max_index;
}

void print_array(int arr[], int n)
{
	for (int *p = arr; p < arr + n; p++)
		printf("%d ", *p);
	printf("\n");
}
