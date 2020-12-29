#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"


int L_init(LIST* pList)
{
	if (pList == NULL) 
		return 0;	

	pList->head.next = NULL;
	return 1;
}



NODE* L_insert(NODE* pNode, DATA Value)
{
	NODE* tmp;

	if (!pNode)
		return NULL;

	tmp = (NODE*)malloc(sizeof(NODE));	// new node

	if (tmp != NULL) {
		tmp->key = Value;
		tmp->next = pNode->next;
		pNode->next = tmp;
	}
	return tmp;
}

NODE* L_SortInsert(NODE* head, DATA value, int(*compareFunc)(const void*,const void*))
{
	if (head==NULL)
		return NULL;

	NODE* helper;
	if (head->next == NULL)
		return L_insert(head, value);
	
	helper = head->next;
	while (helper != NULL) //checks until the last one
	{
		if(compareFunc(value, helper->key) < 0) //in case the smallest
			return L_insert(head, value);

		if (helper->next == NULL)
			break;

		if (compareFunc(value, helper->key)>0 && compareFunc(value, helper->next->key)<0) //any other case
		{
			return L_insert(helper, value);
		}

		
		helper = helper->next;
	}
	//in case biggest
	return L_insert(helper, value);
}




int L_delete(NODE* pNode, void(*freeFunc)(void*))
{
	NODE* tmp;

	if (!pNode )
		return 0;

	tmp = pNode->next;

	if (!tmp)
		return 0;

	pNode->next = tmp->next;
	if (freeFunc != NULL)
		freeFunc(tmp->key);
	free(tmp);
	return 1;
}

int L_free(LIST* pList, void(*freeFunc)(void*))
{
	NODE* head;
	
	if (!pList) 
		return 0;
	
	head = &(pList->head);
	if (head == NULL)
		return 0;

	int res = 1;
	while (res)
	{
		res = L_delete(head, freeFunc);
	}
	return 1;
}

int L_print(const LIST* pList, void(*print)(const void*))
{
	NODE *tmp;
	int	c = 0;

	if (!pList) 
		return 0;

	tmp = pList->head.next;
	if (tmp == NULL)
		return 0;

	while (tmp->next != NULL)
	{
		print(tmp->key);
		tmp = tmp->next;
		c++;
	}
	print(tmp->key);
	c++;
	
	return c;
}

NODE* L_find(NODE* pNode, DATA Value, int(*compare)(const void*,const void*))
{
	NODE* tmp;

	if (!pNode)
		return NULL;

	tmp = pNode->next; //first in list

	while (tmp!=NULL && (compare(tmp->key, Value)!=0))
	{
		tmp = tmp->next;
	}

	return tmp;
}