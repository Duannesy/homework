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
}QNode,*QueuePtr;//�ڵ�Ľṹ�� 
 
typedef struct{
	QueuePtr front;//��ͷָ��
	QueuePtr rear;//��βָ�� 
}LinkQueue;

Status InitQueue(LinkQueue &Q)//��ʼ������
{
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front){
		printf("�ڴ����ʧ��\n"); 
		return FALSE;//�洢�ռ����ʧ��
	}
	 
	Q.front->next=NULL;
	printf("��ʼ���ɹ�!\n");
	return TRUE;  
}
Status DestoryQueue(LinkQueue &Q)//���ٶ��� 
{
	if(Q.front==NULL){
		printf("�������ڻ��Ѿ������٣������³�ʼ��!\n");
		return false;
	}
	while(Q.front)
	{
		Q.rear=Q.front->next;
		free(Q.front);//�ͷ��ڴ� 
		Q.front=Q.rear;
	}
	printf("���ٳɹ�!\n");
	return TRUE;
}
Status ClearQueue(LinkQueue &Q)//�������Ԫ�� 
{
	
	if(Q.front==NULL){
		printf("�������ڻ��Ѿ������٣������³�ʼ��!\n");
		return false;
	}
	if(Q.front==Q.rear)
	{
		printf("����Ϊ��!\n");
		return false;
	
	}
	//�Ƚ���βָ��ָ���ͷָ�����һ�����
	Q.rear=Q.front->next;
	while(Q.front->next)
	{
		//��βָ�����
		Q.rear=Q.rear->next; 
		//�ͷŶ�ͷָ��Ͷ�βָ���м�Ľ��
		free(Q.front->next);
		//���Ӷ���
		Q.front->next=Q.rear; 
	 } 
	 //����Ϊ��ʱ��������βָ��
	 Q.rear=Q.front; 
	 printf("��ճɹ�!\n");
}
Status QueueEmpty(LinkQueue &Q)//�ж϶����Ƿ�Ϊ�� 
{
	if(Q.front==NULL){
		printf("�������ڻ��Ѿ������٣������³�ʼ��!\n");
		return false;
	}
	if(Q.front==Q.rear)
	{
		printf("����Ϊ��!\n");
		return true;
	
	}
	printf("�ö��в�Ϊ��!\n");
	return false; 
}
int QueueLength(LinkQueue Q)//��ȡ���г��� 
{
	if(Q.front==NULL){
		printf("�������ڻ��Ѿ������٣������³�ʼ��!\n");
		return false;
	}
	int i=0;
	while(Q.front!=Q.rear)
	{
		i++;
		Q.front=Q.front->next;//���ϴӶ���ͷ��β���������� 
	}
	printf("�ö��г���Ϊ:%d\n",i);
}
Status GetHead(LinkQueue Q,QElemType &e)//��ȡͷԪ�� 
{
	//���ж��Ƿ�Ϊ��
	if(Q.front==NULL){
		printf("�������ڻ��Ѿ������٣������³�ʼ��!\n");
		return false;
	}
	if(Q.front==Q.rear){
		printf("�����ѿ�\n"); 
		return FALSE;
	} 
	else
	{
		e=Q.front->next->data;
	    return e;
	}
	
}
Status EnQueue(LinkQueue &Q,QElemType e)//�����βԪ�� 
{
	//Ϊ��Ԫ��e����ռ�
	if(Q.front==NULL){
		printf("�������ڻ��Ѿ������٣������³�ʼ��!\n");
		return false;
	} 
	QNode *p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p){
		printf("�ڴ����ʧ��\n");
		return FALSE;
	}  
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;//�޸Ķ�βָ�룬�����¶�β��� 
	Q.rear=p; 
	printf("����ɹ���\n"); 
	return TRUE;
}
Status DeQueue(LinkQueue &Q,QElemType &e)//ɾ����ͷԪ�� 
{
	if(Q.front==NULL){
		printf("�������ڻ��Ѿ������٣������³�ʼ��!\n");
		return false;
	}
	QNode *p;
	if(Q.front==Q.rear){
		printf("�����ѿ�\n");
		return FALSE;//�ж϶����Ƿ�Ϊ��
	}   
	p=Q.front->next;//pָ���ͷԪ�ؽ�� 
	e=p->data;
	Q.front->next=p->next;//�޸Ķ���ͷ���ָ�룬��ɾ����ͷԪ�ؽ�� 
	if(Q.rear==p)  Q.rear=Q.front;//���ڶ���ֻ��һ��Ԫ�ؽ�㣬Ҫͬʱ�޸Ķ�βָ�� 
	free(p);
	return TRUE;
}
Status QueueTraverse(LinkQueue Q)//�����������Ԫ�� 
{
	QNode *p;
	if(Q.front==NULL){
		printf("�������ڻ��Ѿ������٣������³�ʼ��!\n");
		return false;
	}
	if(Q.front==Q.rear){
		printf("�����ѿ�\n");
		return FALSE;
	}  
	p=Q.front->next;//�洢ͷԪ��
	printf("�ö���Ԫ����:\n");
	while(p!=NULL)
	{
		printf("%d \n",p->data);
		p=p->next;
	} 
}
int main()
{
	LinkQueue Q;//��ʼ���������� 
	int e;
	int a;
	printf("----��ʽ���л�������-----\n");
	printf("1.��ʼ������\n");
	printf("2.���ٶ���\n");
	printf("3.��ն���\n");
	printf("4.�ж϶����Ƿ�Ϊ��\n");
	printf("5.����еĳ���\n");
	printf("6.��ȡ��ͷԪ��\n");
	printf("7.����Ԫ�ؽ����β\n");
	printf("8.ɾ����ͷԪ��\n");
	printf("9.�������Ԫ��\n");
	printf("0.�˳�\n");
	printf("������������룺");
	do{
		scanf("%d",&a);
		if(a==0)  break;
		else{
			switch(a){
				case 1:
					InitQueue(Q);
					printf("������������룺");
					break;
				case 2:
					DestoryQueue(Q);
					printf("������������룺");
					break;
				case 3:
					ClearQueue(Q);
					printf("������������룺");
					break;
				case 4:
					QueueEmpty(Q);
					printf("������������룺");
					break;
				case 5:
					QueueLength(Q);
					printf("������������룺");
					break;
				case 6:
					printf("��ͷԪ��Ϊ:%d\n",GetHead(Q,e));
					printf("������������룺");
					break;
				case 7:
				    cout<<"����������Ҫ�����Ԫ�أ�";
					scanf("%d",&e);
					EnQueue(Q,e);
					printf("������������룺");
					break;
				case 8:
				    e=DeQueue(Q,e); 
				    printf("%d\n",e);
				    printf("ɾ����ͷԪ�سɹ���\n");
					printf("������������룺");
					break;
				case 9:
					QueueTraverse(Q);
					printf("������������룺");
					break;
			}
		}
	}while(a!=0);
}


