#include "listfun.h"

#ifndef  __MY_SPORTMEET_H__ 
#define __MY_SPORTMEET_H__

#define MAXARR 21													//最高学校编号

//结构体
typedef struct Player
{
	STNode node;
	int itemNumber;													//项目编号
	char name[64];													//姓名
	char sex[64];													//性别
	int schoolNumber;												//学校编号
	int rank;														//名次
}STPlayer;

typedef struct TempPlayer
{
	STNode node;
	char itemNumber[64];											//项目编号
	char name[64];													//姓名
	char sex[64];													//性别
	char schoolNumber[64];											//学校编号
	char rank[64];													//名次

}TSTPlayer;

typedef struct DataRrsult
{									
	STNode node;
	int schoolNumber;												//学校编号
	int womenTeamScore;												//女团得分
	int manTeamScore;												//男团得分
	int schoolScore;												//学校得分
}STDataRrsult;

//函数

int legalInput(TSTPlayer* node);									//判断是否合法输入合法返回1非法返回-1
int ifstrdig(const char* str);										//判断是否为数字
int strchadig(const char* str);										//字符串转换整数
void* dataInput(void);												//从键盘获取输入内容若合法输入返回结构体内容
																	//若不合法输入要求用户重新输入首次输入编号0代表退出输入
																	//标记参参赛学校编号,最高编号MAXARR-1最小编号1
bool findThisNode(STDataRrsult* node, STDataRrsult* ptrHead);		//判断此属性节点是否存在
STDataRrsult* totalScoreFun(STPlayer* ptrHead);						//统计得分函数
void dataPrint(STPlayer* nodeSP, STDataRrsult* nodeSD);				//打印结果
int getSocer(STPlayer* node);										//计算得分
STDataRrsult* SelectSort(STDataRrsult* t);							//链表的排序
void printSocer(STPlayer* nodeSP, STDataRrsult* nodeSD, const char* position); //打印成绩单
#endif