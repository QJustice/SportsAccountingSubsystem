#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "sportmeet.h"
#include "listfun.h"

const char* position = "D:/socer.txt"; //成绩单保存路径
//测试函数群（调试时使用）
void testDataPrintPlayer(STPlayer* prnode)
{
	printf(" %d %d %s %s %d\n", prnode->schoolNumber, prnode->itemNumber, prnode->name, prnode->sex, prnode->rank);
}
void testDataPrintdata(STDataRrsult* prnode)
{
	printf("第%d学校 %d %d %d\n",prnode->schoolNumber,  prnode->manTeamScore, prnode->womenTeamScore, prnode->schoolScore);
}

int main(void)
{
	printf("请输入：\n");
	printf("项目编号，姓名，姓别，学校， 名次\n");
	void* ptrToData = dataInput();
	printf("------------------------------\n");
	STDataRrsult* rhead = NULL;
	//list_print(ptrToData, (void*)testDataPrintPlayer);
	rhead = totalScoreFun(((STPlayer*)ptrToData));
	//rhead = list_sort(rhead);
	rhead = SelectSort(rhead);
	//list_print(rhead, (void*)testDataPrintdata);
	dataPrint((STPlayer*)ptrToData, rhead);
	char str[64];
	int flag = 1;
	printf("若需要打印成绩单请输入yes，不需要请输入no\n");
	do
	{
		rewind(stdin);						//清空缓冲区
		scanf("%s", str);
		if (strcmp(str, "yes") == 0)
		{
			flag = 0;
			printSocer((STPlayer*)ptrToData, rhead, position);
		}
		else if (strcmp(str, "no") == 0)
		{
			flag = 0;
			printf("已取消成绩单打印\n");
		}
		else	//非法输入判断
		{
			flag = 1;
			printf("输入异常,请重新输入，yes or no.\n");
			rewind(stdin);						//清空缓冲区
		}
			
	} while (flag);
	//销毁链表
	list_destory(ptrToData);
	list_destory(rhead);

	return 0;
}