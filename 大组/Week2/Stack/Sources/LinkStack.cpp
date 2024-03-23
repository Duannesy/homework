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
#define ERROR 0 //状态初始化 
 
typedef int Status;
 
typedef struct snode{
	int data;
	struct snode* next;
}snode; //节点结构体 
typedef struct linkstack{
	snode* top;
	snode* bottom;
	int length;
}linkstack; //链栈的结构体 
Status creat(linkstack* S){//创建一个空栈 
	S->top=S->bottom=(snode*)malloc(sizeof(snode));//头尾指针初始化 
	if(!S->top){
		return ERROR;
	}//空间调用失败报错 
	S->top->next=NULL;
	S->bottom->next=NULL;
	S->length=0;//初始化为空，长度为0 
	return OK; 
}
 
bool empty(linkstack S){//判断栈是否为空  
	return !S.length;
}
 
int size(linkstack S){//返回栈的大小  
	return S.length;
}
 
Status push(linkstack* S,int e){//元素入栈  
	snode* newx=(snode*)malloc(sizeof(snode));//对新节点进行创建 
	if(!newx){
		return ERROR;//空间创建失败报错 
	}
	newx->data=e;
	newx->next=S->top->next;
	S->top->next=newx;//对链进行延长 
	if(!S->length)
		S->bottom=S->bottom->next;//如果是空的就从第一个开始 
	S->length++;
	return OK;
}
 
Status pop(linkstack* S){//弹出栈顶元素  
	if(!S->length){
		return inf;//返回极大值表示栈空了 
	}
	snode* del=S->top->next;
	S->top->next=del->next;//读取栈顶元素 
	free(del);//释放空间 
	S->length--;//减少栈的长度 
	if(!S->length)
		S->bottom=S->top;//如果弹出完长度为0，则栈底就是栈顶 
	return OK;
}
 
int gettop(linkstack S){//获得栈顶元素 存到e中  
	if(!S.length){
		return inf;//栈为空，无元素就返回极大值 
	}
	return S.top->next->data;//返回栈顶元素的数字 
}
 

 
Status clear(linkstack *S){//清空栈  
	while(S->top->next)
		pop(S);//直接把栈顶元素一个一个弹出 
	return OK; 
}
 
Status destroy(linkstack* S){//销毁当前栈  
	snode* del;
	while(S->top){
		del=S->top;
		S->top=S->top->next;
		free(del);//一个个释放内存达到销毁效果 
	}
	S->top=S->bottom=NULL;
	return OK;
}
 
int type(int c){
	if(c>='0'&&c<='9')
		return 1;//数字
	return 0;//字符 
}//判断字符是运算符还是数字 
int precede(char a,char b){//判断两个符号的优先级  表示第一个 ？ 第二个 
	int rule[7][7]={//运算符优先级表 1表示>（高优先级） ,2表示<（低优先级） ,0表示=（同样优先级） ,-1表示（左右括号专用）。 
		1, 1, 2, 2, 2, 1, 1,
		1, 1, 2, 2, 2, 1, 1,
		1, 1, 1, 1, 2, 1, 1,
		1, 1, 1, 1, 2, 1, 1,
		2, 2, 2, 2, 2, 0, -1,
		1, 1, 1, 1, -1, 1, 1,
		2, 2, 2, 2, 2, -1, 0 
	};
	
	char pp[7]={'+','-','*','/','(',')','#'};//用于查找运算符的序号（井号表示已经到了结尾，是停止符号）  
	int hang=0,lie=0;
	while(a!=pp[hang])
		hang++;
	while(b!=pp[lie])
		lie++;//这是在一个个遍历表中位置，定位优先级 
	return rule[hang][lie];//返回优先级 
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
	}//计算器的计算处理 
}
 
int solve(char str[999]){//主函数
	str[strlen(str)]='#';
	linkstack num,sign;
	creat(&num);
	creat(&sign);//创建两个链表num是数字，sign是运算符 
	push(&sign,'#');//在后面加上井号表示结束 
	int a,b;
	char theta;
	for(int i=0;i<strlen(str);i++)
	if(!(str[i]=='#'||str[i]=='('||str[i]==')'||str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]>='0'&&str[i]<='9')){
		return inf;//这是输入报错 
	} 
	
	if(str[strlen(str)-1]!='#'||str[0]=='#'){
		return inf;//如果一开始就是空，也报错 
	}
	
	for(int i=0;i<strlen(str);i++){
		int sum=0;
		if(type(str[i])){
			while(type(str[i])){
				int temp=str[i]-'0';
				sum=sum*10+temp;
				i++;
			}//如果是数字就不断进位 
			push(&num,sum);//返回 
		}//这里我做了优化，解决多位数问题 
		
		switch(precede(gettop(sign),str[i])){
			case 0://括号已经匹配 
				pop(&sign);
				break;
			case 1://碰到优先级低的运算符 先计算出结果并入栈  
				theta=gettop(sign);
				pop(&sign) ;
				a=gettop(num);
				pop(&num);
				b=gettop(num);
				pop(&num);
				if(a==inf||b==inf){//数字栈空了，还有运算符  
					return ERROR;	
				}
				push(&num,operate(b,theta,a));//将数字栈栈顶两个元素取出，并取出符号栈的栈顶符号进行计算 
				i--;
				break;
			case 2://碰到优先级高的运算符 高级运算符入栈 
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
	destroy(&sign);//清空内存 
	return res;
}
struct RectButton
{
	int x, y;
	int width, height;
};//按钮结构体 
//定义按钮，确定区域
bool insideRectButton(const RectButton* button, int x, int y)
{
	return (x >= button->x) && (y >= button->y)
		&& (x < button->x + button->width)
		&& (y < button->y + button->height);
}//判断是否点到按钮 
void drawRectButton(const RectButton* button,char a[])
{
	setfillcolor(EGERGB(0x1E, 0x90, 0xFF));
	bar(button->x, button->y, button->x + button->width, button->y + button->height);
	xyprintf(button->x+(button->width)/4,button->y+(button->height)/4,a);
}//按钮绘画

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
	setcaption("计算器");
	sys_edit editBox1;
	editBox1.create(false);
	editBox1.size(200, 24 + 8);
	editBox1.setbgcolor(YELLOW);
	editBox1.setfont(24, 0, "黑体");
	editBox1.move(40, 40);
	editBox1.visable(true);
	editBox1.setfocus();
	const int buffSize = 100;//初始化输入框 
	bool clickButton1 = false;
	bool clickButton2 = false;
	bool Button1rf = false;
	bool Button2rf = false;//按钮初始化
	editBox1.settext("输入算式");
	Sleep(2000);
	editBox1.settext("");
	cleardevice();
	for(;is_run(); delay_fps(60)) {
		cleardevice();
		drawRectButton(&button1,"计算");
		drawRectButton(&button2,"退出");
		editBox1.visable(true);
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			//判断鼠标左键点击（左键按下确定位置，抬起为执行时刻）
			if (msg.is_left()) {
				if (msg.is_down()) {
					clickButton1 = insideRectButton(&button1, msg.x, msg.y);
					clickButton2 = insideRectButton(&button2, msg.x, msg.y);
				}
				else {
					//左键抬起，判断是否需要执行事件响应
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
				xyprintf(200,500,"出现错误"); 
			}
			else{
				xyprintf(200,500,"结果为%d",result);
			}
			Sleep(2000);
			editBox1.settext("");
			memset(str, 0, sizeof(str)); 
			cleardevice();
		}
		if(Button2rf){
			Button2rf = false;
			cleardevice();
			xyprintf(200,500,"退出");
			Sleep(1000);
			editBox1.destory();//销毁输入框 
			cleardevice();
			break; 
		}
	}
}
int main(){
	mainwindow();
	return 0;
}




