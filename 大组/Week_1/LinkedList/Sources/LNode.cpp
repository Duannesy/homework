#include <graphics.h>
#include <stdio.h>
#include <ege/sys_edit.h>
#include <windows.h>
#define blen sizeof(struct bill)
#include<time.h>
struct RectButton
{
	int x, y;
	int width, height;
};//按钮结构体 
//定义按钮，确定区域
RectButton button1 = {
	200, 200,  
	80, 80,  
};

RectButton button2 ={
	200,400,
	400,80,
};

RectButton button3={
	200,600,
	400,80,
};

RectButton button4={
	100,600,
	80,80,
};

RectButton button5={
	200,600,
	80,80,
};
RectButton button6={
	200,200,
	80,80,
};

RectButton button7={
	200,400,
	80,80,
};

RectButton button8={
	200,600,
	80,80
};
RectButton button9={
	400,200,
	80,80,
};
struct LNode{
	int num;//数据存储 
	struct LNode *next;//指向下一个节点 
	struct LNode *front;//指向上一个节点 
};
//以下都是图形化界面的函数处理（上学期课设的） 
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
void show(struct LNode* head){

	struct LNode* p;
	p=head;
	while(p!=NULL){
		printf("%d",p->num);
		p=p->next;
		printf("-");
	}
	printf("\n");
}//遍历链表，将链表元素输出，展示效果 
struct LNode *swapList(struct LNode *head) {
    struct LNode *p1,*p2,*p;
    p1=head;
    p2=head->next;
    head=p2;
    p1->next=p2->next;
    p2->next=p1;//因为开始两个没有前一个所以特殊化处理 
    p=p1;
    while(p->next!=NULL){
    	p1=p->next;
    	p2=p1->next;
    	p->next=p2;
    	p1->next=p2->next;
    	p2->next=p1;
    	p=p1;//对要交换两项的前一项进行标记，再进行交换； 
	}
	return(head);
    
}
void find(struct LNode *head){
	struct LNode *p1,*p2;
	p1=p2=head;
	while(p2->next!=NULL){
		p1=p1->next;
		p2=p2->next;
		if(p2!=NULL){
			p2=p2->next;//这里为了防止偶数长度进入空指针报错，实际上还是双倍速度 
		}
	}//使用快慢双指针找出中点节点； 
	printf("%d\n",p1->num);
}


void judge(struct LNode *head){
	int pan=1; 
	struct LNode *p1,*p2;
	while(p2->next!=NULL){
		p1=p1->next;
		p2=p2->next;
		if(p2!=NULL){
			p2=p2->next;
		}
		if(p1=p2){
			pan=0;
			break;//追上了就是成环 
		}
	}//如果快指针碰到空指针就说明没成环
	if(pan==1){
		printf("没有成环"); 
	}
	else{
		printf("成环了"); 
	} 
	
}//这个函数解决判断成环问题，但是在主程序里面单链表没有设置指定接在哪个节点上（默认是不成环的），所以不会运行，望学长周知 



struct LNode *reversedigui(struct LNode *head){
	if(head==NULL||head->next==NULL)
	return head;
	struct LNode *new_head=reversedigui(head->next);//到下一层反转 
	head->next->next=head;
	head->next=NULL;//重置头节点和尾结点 
	return new_head; 
}//递归法反转
struct LNode* reversediedai(struct LNode *head)
{
	struct LNode *p1=NULL,*p2=NULL,*p3=NULL;//初始化所有变量 
	p1=head;
	p2=p1->next;//标记下一个 
	while(p2!=NULL)
	{
	p3=p2->next;
	p2->next=p1;
	p1=p2;
	p2=p3;//交换反转操作 
	}
	head->next=NULL;
	head=p1;
	p1=NULL;
	return head; 
} //迭代法反转 


//上述两个反转只会在程序执行一个，默认是递归法反转	
	
void opeate(struct LNode *head){
	initgraph(1000,1000,INIT_RENDERMANUAL);
	setbkcolor(WHITE);
	setcaption("opeate");
	bool clickButton6 = false;
	bool clickButton7 = false;
	bool clickButton8 = false;
	bool clickButton9 = false;
	bool Button6rf = false;
	bool Button7rf = false;
	bool Button8rf = false;
	bool Button9rf = false;//初始化所有按钮 
	for (;is_run(); delay_fps(60)) {
		cleardevice();
		xyprintf(400,400,"输出结果显示在终端");
		drawRectButton(&button6,"奇偶调换");
		drawRectButton(&button7,"找到中点");
		drawRectButton(&button8,"反转链表");
		drawRectButton(&button9,"退出");
		setfont(24, 0, "黑体");
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			//判断鼠标左键点击（左键按下确定位置，抬起为执行时刻）
			if (msg.is_left()) {
				if (msg.is_down()) {
					clickButton6 = insideRectButton(&button6, msg.x, msg.y);
					clickButton7 = insideRectButton(&button7, msg.x, msg.y);
					clickButton8 = insideRectButton(&button8, msg.x, msg.y);
					clickButton9 = insideRectButton(&button9, msg.x, msg.y);
				}
				else {
					//左键抬起，判断是否需要执行事件响应
					if (clickButton6)
					{
						clickButton6 = false;
						Button6rf = true;
					}
					if (clickButton7)
					{
						clickButton7 = false;
						Button7rf = true;
					}
					if (clickButton8){
						clickButton8 = false;
						Button8rf = true;
					}
					if (clickButton9){
						clickButton9 = false;
						Button9rf = true;
					}
				}
			}
		}
		if(Button9rf){
			Button9rf = false;
			cleardevice();
			setcolor(BLACK);
			setfont(24, 0, "");
			xyprintf(240, 360, "你已退出");
			Sleep(1000);
			break;
		}
		if(Button6rf){
			Button6rf = false;
			head=swapList(head);
			show(head);
		}
		if(Button7rf){
			Button7rf = false;
			find(head);	
		}
		if(Button8rf){
			Button8rf = false;
			head=reversedigui(head);
			show(head);	
		}//每个按钮对应不同功能 
		
	}
}
void createsingle(){
	initgraph(1000,1000,INIT_RENDERMANUAL);
	setbkcolor(WHITE);
	setcaption("单链表创建");
	sys_edit editBox1;
	editBox1.create(false);
	editBox1.size(200, 24 + 8);
	editBox1.setbgcolor(YELLOW);
	editBox1.setfont(24, 0, "黑体");
	editBox1.move(40, 40);
	editBox1.visable(false);
	editBox1.setfocus();
	const int buffSize = 100;//初始化输入框 
	bool clickButton4 = false;
	bool clickButton5 = false;
	bool Button4rf = false;
	bool Button5rf = false;//按钮初始化
	editBox1.visable(true);
	editBox1.settext("输入数据");
	char num[100];
	Sleep(2000);
	editBox1.settext("");
	cleardevice();
	struct LNode *head,*p1,*p2;
	int n=0; 
	head=(LNode*)malloc(sizeof(LNode));//链表头初始化 
	p1=p2=(LNode*)malloc(sizeof(LNode));//指针链表初始化
	for(;is_run(); delay_fps(60)) {
		cleardevice();
		drawRectButton(&button4,"确认输入");
		drawRectButton(&button5,"完成");
		editBox1.visable(true);
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			//判断鼠标左键点击（左键按下确定位置，抬起为执行时刻）
			if (msg.is_left()) {
				if (msg.is_down()) {
					clickButton4 = insideRectButton(&button4, msg.x, msg.y);
					clickButton5 = insideRectButton(&button5, msg.x, msg.y);
				}
				else {
					//左键抬起，判断是否需要执行事件响应
					if (clickButton4)
					{
						clickButton4 = false;
						Button4rf = true;
					}
					if (clickButton5)
					{
						clickButton5 = false;
						Button5rf = true;
					}		
				}
			}
		}
		if(Button4rf){
			Button4rf = false;
			editBox1.gettext(buffSize, num);
			sscanf(num, "%d", &p1->num);
			if(n==0){
				head=p1;
			}
			else{
				p2->next=p1;
			}
			n++;
			p2=p1;
			p1=(LNode*)malloc(sizeof(LNode));
			editBox1.settext("");
			cleardevice();
		}
		if(Button5rf){
			Button5rf = false;
			cleardevice();
			if(n==0){
				xyprintf(200,500,"结束");
				Sleep(1000);
				cleardevice();
				break;
			}
			p2->next=NULL;
			xyprintf(200,500,"完成创建");
			Sleep(1000);
			editBox1.destory();//销毁输入框 
			cleardevice();
			opeate(head);
			break; 
		}
	} 
	
}
void createdouble(){
	initgraph(1000,1000,INIT_RENDERMANUAL);
	setbkcolor(WHITE);
	setcaption("双向链表创建");
	sys_edit editBox1;
	editBox1.create(false);
	editBox1.size(200, 24 + 8);
	editBox1.setbgcolor(YELLOW);
	editBox1.setfont(24, 0, "黑体");
	editBox1.move(40, 40);
	editBox1.visable(false);
	editBox1.setfocus();
	const int buffSize = 100;//初始化输入框 
	bool clickButton4 = false;
	bool clickButton5 = false;
	bool Button4rf = false;
	bool Button5rf = false;//按钮初始化
	editBox1.visable(true);
	editBox1.settext("输入数据");
	char num[100];
	Sleep(2000);
	editBox1.settext("");
	cleardevice();
	struct LNode *head,*p1,*p2;
	int n=0; 
	head=(LNode*)malloc(sizeof(LNode));//链表头初始化 
	p1=p2=(LNode*)malloc(sizeof(LNode));//指针链表初始化
	for (;is_run(); delay_fps(60)) {
		cleardevice();
		drawRectButton(&button4,"确认输入");
		drawRectButton(&button5,"完成");
		editBox1.visable(true);
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			//判断鼠标左键点击（左键按下确定位置，抬起为执行时刻）
			if (msg.is_left()) {
				if (msg.is_down()) {
					clickButton4 = insideRectButton(&button4, msg.x, msg.y);
					clickButton5 = insideRectButton(&button5, msg.x, msg.y);
				}
				else {
					//左键抬起，判断是否需要执行事件响应
					if (clickButton4)
					{
						clickButton4 = false;
						Button4rf = true;
					}
					if (clickButton5)
					{
						clickButton5 = false;
						Button5rf = true;
					}		
				}
			}
		}
		if(Button4rf){
			Button4rf = false;
			editBox1.gettext(buffSize, num);
			sscanf(num, "%d", &p1->num);
			if(n==0){
				head=p1;
			}
			else{
				p2->next=p1;
			}
			n++;
			p2=p1;
			p1=(LNode*)malloc(sizeof(LNode));
			editBox1.settext("");
			cleardevice();
		}
		if(Button5rf){
			Button5rf = false;
			cleardevice();
			if(n==0){
				xyprintf(200,500,"结束");
				Sleep(1000);
				cleardevice();
				break;
			}
			p2->next=NULL;
			struct LNode *p1,*p2;
			p1=head;
			p1->front=NULL;
			p2=p1->next;
			while(p1->next!=NULL){
				p2->front=p1;
				p1=p2;
				p2=p2->next;
			}
			xyprintf(200,500,"完成创建");
			Sleep(1000);
			editBox1.destory();//销毁输入框 
			cleardevice();
			break; 
		}
	} 
	
}
void start(){
	initgraph(1000,1000,INIT_RENDERMANUAL);
	setbkcolor(WHITE);
	setcaption("LNode");
	bool clickButton1 = false;
	bool clickButton2 = false;
	bool clickButton3 = false;
	bool Button1rf = false;
	bool Button2rf = false;
	bool Button3rf = false;//初始化所有按钮 
	for (;is_run(); delay_fps(60)) {
		cleardevice();
		drawRectButton(&button1,"离开");
		drawRectButton(&button2,"创造单向链表");
		drawRectButton(&button3,"创造双向链表");
		setfont(24, 0, "黑体");
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			//判断鼠标左键点击（左键按下确定位置，抬起为执行时刻）
			if (msg.is_left()) {
				if (msg.is_down()) {
					clickButton1 = insideRectButton(&button1, msg.x, msg.y);
					clickButton2 = insideRectButton(&button2, msg.x, msg.y);
					clickButton3 = insideRectButton(&button3, msg.x, msg.y);
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
					if (clickButton3){
						clickButton3 = false;
						Button3rf = true;
					}
				}
			}
		}
		if(Button1rf){
			Button1rf = false;
			cleardevice();
			setcolor(BLACK);
			setfont(24, 0, "");
			xyprintf(240, 360, "你已退出");
			Sleep(1000);
			break;
		}
		if(Button2rf){
			Button2rf = false;
			cleardevice();
			createsingle();
		}
		if(Button3rf){
			Button3rf = false;
			cleardevice();
			createdouble();	
		}	
	}
}
int main(){
	start();
	closegraph();
	return 0;
} 
