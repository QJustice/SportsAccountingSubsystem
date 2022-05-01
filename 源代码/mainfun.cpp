#define _CRT_SECURE_NO_WARNINGS
#include "sportmeet.h"
#include "listfun.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int legalInput(TSTPlayer* node)								//判断是否合法输入合法返回1非法返回-1
{
	if ((ifstrdig(node->schoolNumber)) != 1)
	{
		printf("\n学校编号输入字符异常，请输入数字\n");
		return -1;
	}
	if (strchadig(node->schoolNumber) < 1 || strchadig(node->schoolNumber) > MAXARR - 1)
	{
		printf("\n学校编号输入范围异常，正确输入范围为1——%d\n", MAXARR - 1);
		return -1;
	}		
	if ((ifstrdig(node->itemNumber)) != 1)
	{
		printf("\n项目编号输入字符异常，请输入数字\n");
		return -1;
	}
	if ((ifstrdig(node->rank)) != 1)
	{
		printf("\n名次输入字符异常，请输入数字\n");
		return -1;
	}
	if (strcmp(node->sex, "girl") && strcmp(node->sex, "boy") || strcmp(node->sex, "girl") && strcmp(node->sex, "boy"))
	{
		printf("\n性别输入异常，请输入相应英文单词: 男（boy）/女（girl）\n");
		return -1;
	}
	return 0;
}

int ifstrdig(const char* str)								//判断是否为数字
{
	for (int i = 0; str[i] != '\0'; i++)
		if (!(isdigit(str[i])))								//不是数字返回-1
			return -1;
	return 1;
}

int strchadig(const char* str)								//字符串转换整数
{
	int result = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		result *= 10;
	//ASII
		result += str[i] - '0';
	}
	return result;
}

void* dataInput(void)
{
	TSTPlayer tempNode;								//临时结构体用于存储临时的输入信息
	
	void* dataListHead = linklist_init();			//链表初始化创建链表头并返回指向链表头的指针
	while(1)
	{
		int flag = 1;
		do
		{	
			scanf("%s", tempNode.itemNumber);
			//判断是否符合结束条件（项目编号为0）tempNode内部是字符串存储信息
			//所以需要strchadig来把tempNode.itemNumber转换为整数
			if (strchadig(tempNode.itemNumber) == 0)
				return dataListHead;
			scanf("%s %s %s %s", tempNode.name, tempNode.sex, tempNode.schoolNumber, tempNode.rank);
			
			if (legalInput(&tempNode) == 0)		//是否合法输入，合法输入法将标记
				flag = 0;						//输入合法改变标记
			if (flag)							//非法输入提示重新输入
				printf("请重新输入\n");
			rewind(stdin);						//清空缓冲区
		} while (flag);							//非法输入需要重新输入
		//申请内存创建链表节点
		STPlayer* dataNodep = (STPlayer*)malloc(sizeof(STPlayer));
		if (dataNodep == NULL)					//检测内存申请状态
		{
			printf("\nataInput error ：出错原因申请内存失败\n");
			return NULL;
		}
		//给内存块赋值
		dataNodep->itemNumber = strchadig(tempNode.itemNumber);
		strcpy(dataNodep->name, tempNode.name);
		strcpy(dataNodep->sex, tempNode.sex);
		dataNodep->rank = strchadig(tempNode.rank);
		dataNodep->schoolNumber = strchadig(tempNode.schoolNumber);
		//插入链表节点
		linklist_push_back(dataListHead, dataNodep);
	}
}

//得分处理
STDataRrsult* totalScoreFun(STPlayer* ptrHead)
{
	STLinkList* list_ptr = (STLinkList*)ptrHead;
	STDataRrsult* reslutHead = (STDataRrsult*)linklist_init();			//链表初始化创建链表头并返回指向链表头的指针
	if (list_ptr == NULL)	//异常处理
	{
		printf("\nfunction linklist_push_front : err\n");
		return NULL;
	}
	STNode* p = &(list_ptr->head);
	//遍历参赛队员链表
	while (p->next != NULL)
	{
		p = p->next;
		
		STPlayer* tempPtr = (STPlayer*)p;
		STDataRrsult* dataNodep = (STDataRrsult*)malloc(sizeof(STDataRrsult));
		if (dataNodep == NULL)					//检测内存申请状态
		{
			printf("\nataInput error ：出错原因申请内存失败\n");
			return NULL;
		}
		//内存置零
		memset(dataNodep, 0, sizeof(STDataRrsult));
		//给临时内存快赋值
		if (strcmp(tempPtr->sex, "boy") == 0)
			dataNodep->manTeamScore += getSocer(tempPtr);
		if (strcmp(tempPtr->sex, "girl") == 0)
			dataNodep->womenTeamScore += getSocer(tempPtr);
		dataNodep->schoolNumber = tempPtr->schoolNumber;
		dataNodep->schoolScore = dataNodep->manTeamScore + dataNodep->womenTeamScore;
		//如果是新的节点那就插入得分数据链表中
		if (!findThisNode(dataNodep, reslutHead))   
			linklist_push_front(reslutHead, dataNodep);
		else //防止内存泄漏
			free(dataNodep);
	}
	return reslutHead;
}

void dataPrint(STPlayer* nodeSP, STDataRrsult* nodeSD)
{
	STLinkList* list_ptrsp = (STLinkList*)nodeSP;
	STLinkList* list_ptrsd = (STLinkList*)nodeSD;
	STNode* psp = &(list_ptrsp->head);
	STNode* psd = &(list_ptrsd->head);
	STNode* tpsp = psp;
	STNode* tpsd = psd;
	STDataRrsult* ttpsd = NULL;
	STPlayer* ttpsp = NULL;
	printf("学校号 项目号 姓名  性别  名次 得分\n");
	while (tpsd->next != NULL)
	{
		//遍历链表
		tpsd = tpsd->next;
		tpsp = psp;
		
		while (tpsp->next != NULL)
		{
			tpsp =tpsp->next;
			//类型转换用于数据比较
			ttpsd = (STDataRrsult*)tpsd;
			ttpsp = (STPlayer*)tpsp;
			////根据提示输入数据
			//输出
			//学校号    项目号      姓名      性别      名次      得分
				// 学校的成绩表
				//1号学校的男团总分为：
				//1号学校的女团总分为：
				//1号学校的团总分为：
				//共有n个学校的成绩表及总分
			if (ttpsd->schoolNumber == ttpsp->schoolNumber)			
				printf("%-7d %-5d %-5s %-6s %-4d %-10d\n", ttpsp->schoolNumber, ttpsp->itemNumber, ttpsp->name, ttpsp->sex,  ttpsp->rank, getSocer(ttpsp));
		}
		printf("%d号学校的男团总分为 %-3d\n%d号学校的女团总分为 %-3d\n%d号学校的团总分为   %-3d\n",ttpsd->schoolNumber, ttpsd->manTeamScore, ttpsd->schoolNumber, ttpsd->womenTeamScore, ttpsd->schoolNumber, ttpsd->schoolScore);
		//防止末行多余输出
		if (tpsd->next != NULL)
			printf("\n学校号 项目号 姓名  性别  名次 得分\n");
	}
}

//寻找相关数据节点
bool findThisNode(STDataRrsult* node, STDataRrsult* ptrHead)
{
	STLinkList* list_ptr = (STLinkList*)ptrHead;
	if (list_ptr == NULL)
	{
		printf("\nfunction findThisNode : err\n");
		return false;
	}

	STNode* p = &(list_ptr->head);
	while (p->next != NULL)
	{
		p = p->next;
		STDataRrsult* tempNodePtr = (STDataRrsult*)p;
		STDataRrsult* dataNodep = tempNodePtr;		
		if (node->schoolNumber == tempNodePtr->schoolNumber)
		{
			//发现相关数据节点直接加上数据
			tempNodePtr->schoolScore += node->schoolScore;
			tempNodePtr->manTeamScore += node->manTeamScore;
			tempNodePtr->womenTeamScore += node->womenTeamScore;
			return true;
		}		
	}
	//当此数据节点不存在时返回false
	return false;
}

int getSocer(STPlayer* node)
{
	//获取得分情况
	if (node->itemNumber % 2 == 0)
	{
		if (node->rank == 3)
			return 2;
		if (node->rank == 2)
			return 3;
		if (node->rank == 1)
			return 5;
	}
	else
	{
		if (node->rank == 5)
			return 1;
		if (node->rank == 4)
			return 2;
		if (node->rank == 3)
			return 3;
		if (node->rank == 2)
			return 5;
		if (node->rank == 1)
			return 7;
	}
	return 0;
}

STDataRrsult* SelectSort(STDataRrsult* t)
{
	//链表排序
	STNode* p, * q, * small, * L = (STNode*)t;
	STDataRrsult* tq, * ts;
	int temp;
	int tempsocer;

	for (p = L->next; p->next != NULL; p = p->next)    /*每次循环都找出一个最小值，将最小值交换到第一位，然后将指针向后移动一位*/
	{
		small = p;
		for (q = p->next; q; q = q->next)    /*由前向后遍历，找出最小的节点*/
		{
			tq = (STDataRrsult*)q;
			ts = (STDataRrsult*)small;
			if (tq->schoolNumber< ts->schoolNumber)
				small = q;
		}
		if (small != p)
		{
			//数据转换用与数据转移
			tq = (STDataRrsult*)p;
			ts = (STDataRrsult*)small;
			//调换数据包
			temp = tq->schoolNumber;
			tq->schoolNumber = ts->schoolNumber;
			ts->schoolNumber = temp;

			tempsocer = tq->manTeamScore;
			tq->manTeamScore = ts->manTeamScore;
			ts->manTeamScore = tempsocer;
			
			tempsocer = tq->womenTeamScore;
			tq->womenTeamScore = ts->womenTeamScore;
			ts->womenTeamScore = tempsocer;

			tempsocer = tq->schoolScore;
			tq->schoolScore = ts->schoolScore;
			ts->schoolScore = tempsocer;
		}
	}
	return (STDataRrsult*)L;
}

void printSocer(STPlayer* nodeSP, STDataRrsult* nodeSD, const char* position)
{
	//打印成绩单
	//打开文件，创建文件指针
	FILE* fp = fopen(position, "w");
	if (fp == NULL)
	{
		printf("文件建立失败！成绩表打印失败！\n");
		return;
	}
	STLinkList* list_ptrsp = (STLinkList*)nodeSP;
	STLinkList* list_ptrsd = (STLinkList*)nodeSD;
	STNode* psp = &(list_ptrsp->head);
	STNode* psd = &(list_ptrsd->head);
	STNode* tpsp = psp;
	STNode* tpsd = psd;
	STDataRrsult* ttpsd = NULL;
	STPlayer* ttpsp = NULL;
	fprintf(fp,"学校号 项目号 姓名     性别      名次      得分\n");
	while (tpsd->next != NULL)
	{
		//遍历数据链表
		tpsd = tpsd->next;
		tpsp = psp;

		while (tpsp->next != NULL)
		{
			tpsp = tpsp->next;
			ttpsd = (STDataRrsult*)tpsd;
			ttpsp = (STPlayer*)tpsp;
			////根据提示输入数据
			//输出
			//学校号    项目号      姓名      性别      名次      得分
				// 学校的成绩表
				//1号学校的男团总分为：
				//1号学校的女团总分为：
				//1号学校的团总分为：
				//共有n个学校的成绩表及总分
			//条件输出
			if (ttpsd->schoolNumber == ttpsp->schoolNumber)
				fprintf(fp,"%-10d %-10d %-10s %-10s %-10d %-10d\n", ttpsp->schoolNumber, ttpsp->itemNumber, ttpsp->name, ttpsp->sex, ttpsp->rank, getSocer(ttpsp));
		}
		fprintf(fp,"%d号学校的男团总分为 %-3d\n%d号学校的女团总分为 %-3d\n%d号学校的团总分为   %-3d\n", ttpsd->schoolNumber, ttpsd->manTeamScore, ttpsd->schoolNumber, ttpsd->womenTeamScore, ttpsd->schoolNumber, ttpsd->schoolScore);
		if (tpsd->next != NULL)
			fprintf(fp,"\n学校号 项目号 姓名     性别      名次      得分\n");
	}
	printf("\n成绩单打印完毕，保存路径为%s\n", position);
}