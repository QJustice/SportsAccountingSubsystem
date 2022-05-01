#ifndef  __MY_STLIST_H__ 
#define __MY_STLIST_H__

#define SUCCESS 0
#define FAILURE -1

//与自定义数据类型node进行对应
typedef struct Node {
	struct Node* next;
}STNode;

//链表头结点
typedef struct LinkList {
	struct Node head;
	int size;				//包含链表大小因为获取链表大小时不需要每次遍历(链表结点数量过多会消耗时间)
}STLinkList;

void* linklist_init(void);														//初始化链表
int linklist_push_back(void* temp_list_ptr, void* temp_data);					//尾插入
int linklist_push_front(void* temp_list_ptr, void* temp_data);					//头插入
void list_destory(void* temp_list_ptr);											//销毁链表(插入节点必须为堆空间，不可以是自动变量)
void list_print(void* temp_list_ptr, void* TEMP_PRINTLIST);						//遍历链表，需要提供TEMP_PRINTLIST自定义数据输出函数
int list_get_size(void* temp_list_ptr);											//获取链表长度

#endif