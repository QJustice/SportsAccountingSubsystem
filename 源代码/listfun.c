#include <stdio.h>
#include <stdlib.h>
#include "listfun.h"

//初始化链表
void* linklist_init()
{
	STLinkList* list_ptr = (STLinkList*)malloc(sizeof(STLinkList));
	list_ptr->head.next = NULL;
	list_ptr->size = 0;

	return (void*)list_ptr;
}

//尾插入
int linklist_push_back(void* temp_list_ptr, void* temp_data)
{
	STLinkList* list_ptr = (STLinkList*)temp_list_ptr;
	STNode* data = (STNode*)temp_data;

	if (list_ptr == NULL || data == NULL)
	{
		printf("function linklist_push_back : err %d\n", FAILURE);
		return FAILURE;
	}

	//辅助结点指针，头结点指针赋值给赋值结点
	STNode* p = &(list_ptr->head);
	while (p->next != NULL)
		p = p->next;

	p->next = data;
	data->next = NULL;

	list_ptr->size++;

	return SUCCESS;
}

//头插入
int linklist_push_front(void* temp_list_ptr, void* temp_data)
{
	STLinkList* list_ptr = (STLinkList*)temp_list_ptr;
	STNode* data = (STNode*)temp_data;

	if (list_ptr == NULL || data == NULL)
	{
		printf("\nfunction linklist_push_front : err %d\n", FAILURE);
		return FAILURE;
	}

	data->next = list_ptr->head.next;
	list_ptr->head.next = data;

	list_ptr->size++;

	return SUCCESS;
}

//遍历链表
void list_print(void* temp_list_ptr, void* TEMP_PRINTLIST)
{
	STLinkList* list_ptr = (STLinkList*)temp_list_ptr;
	typedef void (*FN_PRINTLIST)(void* node);

	FN_PRINTLIST PRINTLIST = (FN_PRINTLIST)TEMP_PRINTLIST;

	if (list_ptr == NULL || PRINTLIST == NULL)
	{
		printf("\nfunction linklist_push_front : err\n");
		return;
	}
	STNode* p = &(list_ptr->head);
	while (p->next != NULL)
	{
		p = p->next;
		PRINTLIST((void*)p);
	}
}

//销毁链表
void list_destory(void* temp_list_ptr)
{
	STLinkList* list_ptr = (STLinkList*)temp_list_ptr;

	if (list_ptr == NULL || list_ptr->head.next == NULL)
		return;
	STNode* tempHN = list_ptr->head.next;
	STNode* kill = NULL;
	while (tempHN)
	{
		kill = tempHN;
		tempHN = tempHN->next;
		free(kill);
	}
	free(list_ptr);
	list_ptr = NULL;
}

//获取链表长度
int list_get_size(void* temp_list_ptr)
{	
	STLinkList* list_ptr = (STLinkList*)temp_list_ptr;

	if (list_ptr == NULL)
	{
		printf("\nfunction list_get_size : err %d\n", FAILURE);
		return FAILURE;
	}
	return list_ptr->size;
}


