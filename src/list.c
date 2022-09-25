#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"
#include "display.h"



List new_list(void)
{
	return NULL;
}


bool is_empty_list(List list)
{
	return (list == new_list());
}


List add(List list, char c)
{
	Node* new_node = malloc(sizeof(Node));
	new_node->character = c;
	new_node->next = NULL;

	if(is_empty_list(list))
		return new_node;
	
	Node* current_node = list;
	while(current_node->next)
		current_node = current_node->next;
	current_node->next = new_node;
	return list;
}


List destroy_list(List list)
{
	Node* current_node = list;
	Node* next_node = NULL;
	while(current_node)
	{
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
	return new_list();
}


bool contains(List list, char c)
{
	while(list)
	{
		if(list->character == c)
			return true;
		list = list->next;
	}
	return false;
}


void print_list(List list)
{
	printf(""YEL"Attempted letters : ");
	while(list)
	{
		printf("%c ", list->character);
		list = list->next;
	}
	printf(""COLOR_RESET"\n");	
}
