#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LEN 256
#define TABLE_SIZE 676

typedef struct node
{
    char word[WORD_LEN + 1];
    struct node *next;
} node;

int djb2(const char *str)
{
    unsigned long hash = 3;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % 676;
}

void init_table(node *table[])
{
	for (int i = 0; i < TABLE_SIZE; i++)
		table[i] = NULL;
}

long int load(const char *dict_name, node *table[])
{
	FILE *dict;
	if ((dict = fopen(dict_name, "r")) == NULL)
		return false;
	
	long int total_words = 0;	
	char word[WORD_LEN];
	while (fscanf(dict, "%s", word) != EOF)
	{
		int index = djb2(word);
		node *n = malloc(sizeof(node));
		
		for (int i = 0; word[i] != '\0'; i++)
			word[i] = tolower(word[i]);

		n->next = NULL;
		strcpy(n->word, word);

		if (table[index] == NULL)
		{	
			table[index] = n;
		}
		else
		{
			n->next = table[index];
			table[index] = n;
		}
		total_words++;
	}
	return total_words;
}

bool find(node *table[], const char *str)
{
	node *n = table[djb2(str)];

	while (n != NULL)
	{
		if (strcmp(str, n->word) == 0)
			return true;
		n = n->next;
	}
	return false;
}

void free_list(node *head)
{
   struct node *tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }

}

double similarity(node *table[], char *str)
{
	node *n = table[djb2(str)];
//	double 

//	while (n != NULL)

}

void unload(node *table[])
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
		free_list(table[i]);
    }
}


void print_branch(node *ptr)
{
    node *tmp = ptr;
    while (tmp != NULL)
    {
        printf("%s\n", tmp->word);
        tmp = tmp->next;
    }
}
