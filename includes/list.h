#ifndef LIST_H
#define LIST_H


typedef struct Node  Node;
typedef struct Node* List;


struct Node
{
	char character;
	Node* next;
};


List new_list(void);
List add(List list, char c);
List destroy_list(List list);
bool is_empty_list(List list);
bool contains(List list, char c);
void print_list(List list);


#endif
