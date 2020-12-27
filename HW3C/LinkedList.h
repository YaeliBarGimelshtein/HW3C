#pragma once
#ifndef __LINKEDLIST__
#define __LINKEDLIST__

typedef void* DATA;

typedef struct node
{
	DATA			key;
	struct node*	next;
}NODE;

// List
typedef struct
{
	NODE head;
}LIST;



int L_init(LIST* pList); // create new list
NODE* L_insert(NODE* pNode, DATA Value); // add new node after *pNode
NODE* L_SortInsert(NODE* head, DATA value, int(*compareFunc)(const void*, const void*));
int L_delete(NODE* pNode, void(*freeFunc)(void*)); // erase node *pNode
int L_free(LIST* pList, void(*freeFunc)(void*)); // free list memory
int L_print(const LIST* pList, void(*print)(const void*)); // print the list content




#endif