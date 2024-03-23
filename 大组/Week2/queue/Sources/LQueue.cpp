#include <stdlib.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0
#include<malloc.h>
#include<iostream>
using namespace std;
typedef int QElemType; 
typedef int Status;
 
typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;//节点的结构体 
 
typedef struct{
	QueuePtr front;//队头指针
	QueuePtr rear;//队尾指针 
}LinkQueue;

Status InitQueue(LinkQueue &Q)//初始化队列
{
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front){
		printf("内存分配失败\n"); 
		return FALSE;//存储空间分配失败
	}
	 
	Q.front->next=NULL;
	printf("初始化成功!\n");
	return TRUE;  
}
Status DestoryQueue(LinkQueue &Q)//销毁队列 
{
	if(Q.front==NULL){
		printf("链表不存在或已经被销毁，请重新初始化!\n");
		return false;
	}
	while(Q.front)
	{
		Q.rear=Q.front->next;
		free(Q.front);//释放内存 
		Q.front=Q.rear;
	}
	printf("销毁成功!\n");
	return TRUE;
}
Status ClearQueue(LinkQueue &Q)//清除队列元素 
{
	
	if(Q.front==NULL){
		printf("链表不存在或已经被销毁，请重新初始化!\n");
		return false;
	}
	if(Q.front==Q.rear)
	{
		printf("队列为空!\n");
		return false;
	
	}
	//先将队尾指针指向对头指针的下一个结点
	Q.rear=Q.front->next;
	while(Q.front->next)
	{
		//队尾指针后移
		Q.rear=Q.rear->next; 
		//释放对头指针和队尾指针中间的结点
		free(Q.front->next);
		//连接队列
		Q.front->next=Q.rear; 
	 } 
	 //队列为空时，调整队尾指针
	 Q.rear=Q.front; 
	 printf("清空成功!\n");
}
Status QueueEmpty(LinkQueue &Q)//判断队列是否为空 
{
	if(Q.front==NULL){
		printf("链表不存在或已经被销毁，请重新初始化!\n");
		return false;
	}
	if(Q.front==Q.rear)
	{
		printf("队列为空!\n");
		return true;
	
	}
	printf("该队列不为空!\n");
	return false; 
}
int QueueLength(LinkQueue Q)//获取队列长度 
{
	if(Q.front==NULL){
		printf("链表不存在或已经被销毁，请重新初始化!\n");
		return false;
	}
	int i=0;
	while(Q.front!=Q.rear)
	{
		i++;
		Q.front=Q.front->next;//不断从队列头向尾遍历，计数 
	}
	printf("该队列长度为:%d\n",i);
}
Status GetHead(LinkQueue Q,QElemType &e)//获取头元素 
{
	//先判断是否为空
	if(Q.front==NULL){
		printf("链表不存在或已经被销毁，请重新初始化!\n");
		return false;
	}
	if(Q.front==Q.rear){
		printf("队列已空\n"); 
		return FALSE;
	} 
	else
	{
		e=Q.front->next->data;
	    return e;
	}
	
}
Status EnQueue(LinkQueue &Q,QElemType e)//插入队尾元素 
{
	//为新元素e分配空间
	if(Q.front==NULL){
		printf("链表不存在或已经被销毁，请重新初始化!\n");
		return false;
	} 
	QNode *p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p){
		printf("内存分配失败\n");
		return FALSE;
	}  
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;//修改队尾指针，插入新队尾结点 
	Q.rear=p; 
	printf("插入成功！\n"); 
	return TRUE;
}
Status DeQueue(LinkQueue &Q,QElemType &e)//删除队头元素 
{
	if(Q.front==NULL){
		printf("链表不存在或已经被销毁，请重新初始化!\n");
		return false;
	}
	QNode *p;
	if(Q.front==Q.rear){
		printf("队列已空\n");
		return FALSE;//判断队列是否为空
	}   
	p=Q.front->next;//p指向队头元素结点 
	e=p->data;
	Q.front->next=p->next;//修改队列头结点指针，则删除队头元素结点 
	if(Q.rear==p)  Q.rear=Q.front;//对于队列只有一个元素结点，要同时修改队尾指针 
	free(p);
	return TRUE;
}
Status QueueTraverse(LinkQueue Q)//输出整个队列元素 
{
	QNode *p;
	if(Q.front==NULL){
		printf("链表不存在或已经被销毁，请重新初始化!\n");
		return false;
	}
	if(Q.front==Q.rear){
		printf("队列已空\n");
		return FALSE;
	}  
	p=Q.front->next;//存储头元素
	printf("该队列元素有:\n");
	while(p!=NULL)
	{
		printf("%d \n",p->data);
		p=p->next;
	} 
}
int main()
{
	LinkQueue Q;//初始化队列链表 
	int e;
	int a;
	printf("----链式队列基本操作-----\n");
	printf("1.初始化队列\n");
	printf("2.销毁队列\n");
	printf("3.清空队列\n");
	printf("4.判断队列是否为空\n");
	printf("5.求队列的长度\n");
	printf("6.获取队头元素\n");
	printf("7.插入元素进入队尾\n");
	printf("8.删除队头元素\n");
	printf("9.输出所有元素\n");
	printf("0.退出\n");
	printf("请输入操作代码：");
	do{
		scanf("%d",&a);
		if(a==0)  break;
		else{
			switch(a){
				case 1:
					InitQueue(Q);
					printf("请输入操作代码：");
					break;
				case 2:
					DestoryQueue(Q);
					printf("请输入操作代码：");
					break;
				case 3:
					ClearQueue(Q);
					printf("请输入操作代码：");
					break;
				case 4:
					QueueEmpty(Q);
					printf("请输入操作代码：");
					break;
				case 5:
					QueueLength(Q);
					printf("请输入操作代码：");
					break;
				case 6:
					printf("队头元素为:%d\n",GetHead(Q,e));
					printf("请输入操作代码：");
					break;
				case 7:
				    cout<<"请输入您需要插入的元素：";
					scanf("%d",&e);
					EnQueue(Q,e);
					printf("请输入操作代码：");
					break;
				case 8:
				    e=DeQueue(Q,e); 
				    printf("%d\n",e);
				    printf("删除队头元素成功！\n");
					printf("请输入操作代码：");
					break;
				case 9:
					QueueTraverse(Q);
					printf("请输入操作代码：");
					break;
			}
		}
	}while(a!=0);
}


