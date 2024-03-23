#include <graphics.h>
#include <stdio.h>
#include <ege/sys_edit.h>
#include <windows.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<time.h>
using namespace std;
 
const int inf=0x3f3f3f3f;
#define OK 1
#define ERROR 0 //״̬��ʼ�� 
 
typedef int Status;
 
typedef struct snode{
	int data;
	struct snode* next;
}snode; //�ڵ�ṹ�� 
typedef struct linkstack{
	snode* top;
	snode* bottom;
	int length;
}linkstack; //��ջ�Ľṹ�� 
Status creat(linkstack* S){//����һ����ջ 
	S->top=S->bottom=(snode*)malloc(sizeof(snode));//ͷβָ���ʼ�� 
	if(!S->top){
		return ERROR;
	}//�ռ����ʧ�ܱ��� 
	S->top->next=NULL;
	S->bottom->next=NULL;
	S->length=0;//��ʼ��Ϊ�գ�����Ϊ0 
	return OK; 
}
 
bool empty(linkstack S){//�ж�ջ�Ƿ�Ϊ��  
	return !S.length;
}
 
int size(linkstack S){//����ջ�Ĵ�С  
	return S.length;
}
 
Status push(linkstack* S,int e){//Ԫ����ջ  
	snode* newx=(snode*)malloc(sizeof(snode));//���½ڵ���д��� 
	if(!newx){
		return ERROR;//�ռ䴴��ʧ�ܱ��� 
	}
	newx->data=e;
	newx->next=S->top->next;
	S->top->next=newx;//���������ӳ� 
	if(!S->length)
		S->bottom=S->bottom->next;//����ǿյľʹӵ�һ����ʼ 
	S->length++;
	return OK;
}
 
Status pop(linkstack* S){//����ջ��Ԫ��  
	if(!S->length){
		return inf;//���ؼ���ֵ��ʾջ���� 
	}
	snode* del=S->top->next;
	S->top->next=del->next;//��ȡջ��Ԫ�� 
	free(del);//�ͷſռ� 
	S->length--;//����ջ�ĳ��� 
	if(!S->length)
		S->bottom=S->top;//��������곤��Ϊ0����ջ�׾���ջ�� 
	return OK;
}
 
int gettop(linkstack S){//���ջ��Ԫ�� �浽e��  
	if(!S.length){
		return inf;//ջΪ�գ���Ԫ�ؾͷ��ؼ���ֵ 
	}
	return S.top->next->data;//����ջ��Ԫ�ص����� 
}
 

 
Status clear(linkstack *S){//���ջ  
	while(S->top->next)
		pop(S);//ֱ�Ӱ�ջ��Ԫ��һ��һ������ 
	return OK; 
}
 
Status destroy(linkstack* S){//���ٵ�ǰջ  
	snode* del;
	while(S->top){
		del=S->top;
		S->top=S->top->next;
		free(del);//һ�����ͷ��ڴ�ﵽ����Ч�� 
	}
	S->top=S->bottom=NULL;
	return OK;
}
 
int type(int c){
	if(c>='0'&&c<='9')
		return 1;//����
	return 0;//�ַ� 
}//�ж��ַ���������������� 
int precede(char a,char b){//�ж��������ŵ����ȼ�  ��ʾ��һ�� �� �ڶ��� 
	int rule[7][7]={//��������ȼ��� 1��ʾ>�������ȼ��� ,2��ʾ<�������ȼ��� ,0��ʾ=��ͬ�����ȼ��� ,-1��ʾ����������ר�ã��� 
		1, 1, 2, 2, 2, 1, 1,
		1, 1, 2, 2, 2, 1, 1,
		1, 1, 1, 1, 2, 1, 1,
		1, 1, 1, 1, 2, 1, 1,
		2, 2, 2, 2, 2, 0, -1,
		1, 1, 1, 1, -1, 1, 1,
		2, 2, 2, 2, 2, -1, 0 
	};
	
	char pp[7]={'+','-','*','/','(',')','#'};//���ڲ������������ţ����ű�ʾ�Ѿ����˽�β����ֹͣ���ţ�  
	int hang=0,lie=0;
	while(a!=pp[hang])
		hang++;
	while(b!=pp[lie])
		lie++;//������һ������������λ�ã���λ���ȼ� 
	return rule[hang][lie];//�������ȼ� 
} 
 
int operate(int a,char theta,int b){ 
	switch(theta){
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			return a/b;
	}//�������ļ��㴦�� 
}
 
int solve(char str[999]){//������
	str[strlen(str)]='#';
	linkstack num,sign;
	creat(&num);
	creat(&sign);//������������num�����֣�sign������� 
	push(&sign,'#');//�ں�����Ͼ��ű�ʾ���� 
	int a,b;
	char theta;
	for(int i=0;i<strlen(str);i++)
	if(!(str[i]=='#'||str[i]=='('||str[i]==')'||str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]>='0'&&str[i]<='9')){
		return inf;//�������뱨�� 
	} 
	
	if(str[strlen(str)-1]!='#'||str[0]=='#'){
		return inf;//���һ��ʼ���ǿգ�Ҳ���� 
	}
	
	for(int i=0;i<strlen(str);i++){
		int sum=0;
		if(type(str[i])){
			while(type(str[i])){
				int temp=str[i]-'0';
				sum=sum*10+temp;
				i++;
			}//��������־Ͳ��Ͻ�λ 
			push(&num,sum);//���� 
		}//�����������Ż��������λ������ 
		
		switch(precede(gettop(sign),str[i])){
			case 0://�����Ѿ�ƥ�� 
				pop(&sign);
				break;
			case 1://�������ȼ��͵������ �ȼ�����������ջ  
				theta=gettop(sign);
				pop(&sign) ;
				a=gettop(num);
				pop(&num);
				b=gettop(num);
				pop(&num);
				if(a==inf||b==inf){//����ջ���ˣ����������  
					return ERROR;	
				}
				push(&num,operate(b,theta,a));//������ջջ������Ԫ��ȡ������ȡ������ջ��ջ�����Ž��м��� 
				i--;
				break;
			case 2://�������ȼ��ߵ������ �߼��������ջ 
				push(&sign,str[i]);
				break; 		
		}
	}
	int res=gettop(num);	
	pop(&num);
	pop(&sign);
	clear(&num);
	clear(&sign);
	destroy(&num);
	destroy(&sign);//����ڴ� 
	return res;
}
struct RectButton
{
	int x, y;
	int width, height;
};//��ť�ṹ�� 
//���尴ť��ȷ������
bool insideRectButton(const RectButton* button, int x, int y)
{
	return (x >= button->x) && (y >= button->y)
		&& (x < button->x + button->width)
		&& (y < button->y + button->height);
}//�ж��Ƿ�㵽��ť 
void drawRectButton(const RectButton* button,char a[])
{
	setfillcolor(EGERGB(0x1E, 0x90, 0xFF));
	bar(button->x, button->y, button->x + button->width, button->y + button->height);
	xyprintf(button->x+(button->width)/4,button->y+(button->height)/4,a);
}//��ť�滭

RectButton button1 = {
	200, 200,  
	80, 80,  
};

RectButton button2 ={
	200,400,
	80,80,
};
void mainwindow(){
	initgraph(1000,1000,INIT_RENDERMANUAL);
	setbkcolor(WHITE);
	setcaption("������");
	sys_edit editBox1;
	editBox1.create(false);
	editBox1.size(200, 24 + 8);
	editBox1.setbgcolor(YELLOW);
	editBox1.setfont(24, 0, "����");
	editBox1.move(40, 40);
	editBox1.visable(true);
	editBox1.setfocus();
	const int buffSize = 100;//��ʼ������� 
	bool clickButton1 = false;
	bool clickButton2 = false;
	bool Button1rf = false;
	bool Button2rf = false;//��ť��ʼ��
	editBox1.settext("������ʽ");
	Sleep(2000);
	editBox1.settext("");
	cleardevice();
	for(;is_run(); delay_fps(60)) {
		cleardevice();
		drawRectButton(&button1,"����");
		drawRectButton(&button2,"�˳�");
		editBox1.visable(true);
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			//�ж�������������������ȷ��λ�ã�̧��Ϊִ��ʱ�̣�
			if (msg.is_left()) {
				if (msg.is_down()) {
					clickButton1 = insideRectButton(&button1, msg.x, msg.y);
					clickButton2 = insideRectButton(&button2, msg.x, msg.y);
				}
				else {
					//���̧���ж��Ƿ���Ҫִ���¼���Ӧ
					if (clickButton1)
					{
						clickButton1 = false;
						Button1rf = true;
					}
					if (clickButton2)
					{
						clickButton2 = false;
						Button2rf = true;
					}		
				}
			}
		}
		if(Button1rf){
			Button1rf = false;
			char str[999];
			editBox1.gettext(buffSize, str);
			int result;
			result=solve(str);
			if(result==inf){
				xyprintf(200,500,"���ִ���"); 
			}
			else{
				xyprintf(200,500,"���Ϊ%d",result);
			}
			Sleep(2000);
			editBox1.settext("");
			memset(str, 0, sizeof(str)); 
			cleardevice();
		}
		if(Button2rf){
			Button2rf = false;
			cleardevice();
			xyprintf(200,500,"�˳�");
			Sleep(1000);
			editBox1.destory();//��������� 
			cleardevice();
			break; 
		}
	}
}
int main(){
	mainwindow();
	return 0;
}




