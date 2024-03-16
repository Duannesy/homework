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
};//��ť�ṹ�� 
//���尴ť��ȷ������
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
	int num;//���ݴ洢 
	struct LNode *next;//ָ����һ���ڵ� 
	struct LNode *front;//ָ����һ���ڵ� 
};
//���¶���ͼ�λ�����ĺ���������ѧ�ڿ���ģ� 
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
void show(struct LNode* head){

	struct LNode* p;
	p=head;
	while(p!=NULL){
		printf("%d",p->num);
		p=p->next;
		printf("-");
	}
	printf("\n");
}//��������������Ԫ�������չʾЧ�� 
struct LNode *swapList(struct LNode *head) {
    struct LNode *p1,*p2,*p;
    p1=head;
    p2=head->next;
    head=p2;
    p1->next=p2->next;
    p2->next=p1;//��Ϊ��ʼ����û��ǰһ���������⻯���� 
    p=p1;
    while(p->next!=NULL){
    	p1=p->next;
    	p2=p1->next;
    	p->next=p2;
    	p1->next=p2->next;
    	p2->next=p1;
    	p=p1;//��Ҫ���������ǰһ����б�ǣ��ٽ��н����� 
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
			p2=p2->next;//����Ϊ�˷�ֹż�����Ƚ����ָ�뱨��ʵ���ϻ���˫���ٶ� 
		}
	}//ʹ�ÿ���˫ָ���ҳ��е�ڵ㣻 
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
			break;//׷���˾��ǳɻ� 
		}
	}//�����ָ��������ָ���˵��û�ɻ�
	if(pan==1){
		printf("û�гɻ�"); 
	}
	else{
		printf("�ɻ���"); 
	} 
	
}//�����������жϳɻ����⣬���������������浥����û������ָ�������ĸ��ڵ��ϣ�Ĭ���ǲ��ɻ��ģ������Բ������У���ѧ����֪ 



struct LNode *reversedigui(struct LNode *head){
	if(head==NULL||head->next==NULL)
	return head;
	struct LNode *new_head=reversedigui(head->next);//����һ�㷴ת 
	head->next->next=head;
	head->next=NULL;//����ͷ�ڵ��β��� 
	return new_head; 
}//�ݹ鷨��ת
struct LNode* reversediedai(struct LNode *head)
{
	struct LNode *p1=NULL,*p2=NULL,*p3=NULL;//��ʼ�����б��� 
	p1=head;
	p2=p1->next;//�����һ�� 
	while(p2!=NULL)
	{
	p3=p2->next;
	p2->next=p1;
	p1=p2;
	p2=p3;//������ת���� 
	}
	head->next=NULL;
	head=p1;
	p1=NULL;
	return head; 
} //��������ת 


//����������תֻ���ڳ���ִ��һ����Ĭ���ǵݹ鷨��ת	
	
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
	bool Button9rf = false;//��ʼ�����а�ť 
	for (;is_run(); delay_fps(60)) {
		cleardevice();
		xyprintf(400,400,"��������ʾ���ն�");
		drawRectButton(&button6,"��ż����");
		drawRectButton(&button7,"�ҵ��е�");
		drawRectButton(&button8,"��ת����");
		drawRectButton(&button9,"�˳�");
		setfont(24, 0, "����");
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			//�ж�������������������ȷ��λ�ã�̧��Ϊִ��ʱ�̣�
			if (msg.is_left()) {
				if (msg.is_down()) {
					clickButton6 = insideRectButton(&button6, msg.x, msg.y);
					clickButton7 = insideRectButton(&button7, msg.x, msg.y);
					clickButton8 = insideRectButton(&button8, msg.x, msg.y);
					clickButton9 = insideRectButton(&button9, msg.x, msg.y);
				}
				else {
					//���̧���ж��Ƿ���Ҫִ���¼���Ӧ
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
			xyprintf(240, 360, "�����˳�");
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
		}//ÿ����ť��Ӧ��ͬ���� 
		
	}
}
void createsingle(){
	initgraph(1000,1000,INIT_RENDERMANUAL);
	setbkcolor(WHITE);
	setcaption("��������");
	sys_edit editBox1;
	editBox1.create(false);
	editBox1.size(200, 24 + 8);
	editBox1.setbgcolor(YELLOW);
	editBox1.setfont(24, 0, "����");
	editBox1.move(40, 40);
	editBox1.visable(false);
	editBox1.setfocus();
	const int buffSize = 100;//��ʼ������� 
	bool clickButton4 = false;
	bool clickButton5 = false;
	bool Button4rf = false;
	bool Button5rf = false;//��ť��ʼ��
	editBox1.visable(true);
	editBox1.settext("��������");
	char num[100];
	Sleep(2000);
	editBox1.settext("");
	cleardevice();
	struct LNode *head,*p1,*p2;
	int n=0; 
	head=(LNode*)malloc(sizeof(LNode));//����ͷ��ʼ�� 
	p1=p2=(LNode*)malloc(sizeof(LNode));//ָ�������ʼ��
	for(;is_run(); delay_fps(60)) {
		cleardevice();
		drawRectButton(&button4,"ȷ������");
		drawRectButton(&button5,"���");
		editBox1.visable(true);
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			//�ж�������������������ȷ��λ�ã�̧��Ϊִ��ʱ�̣�
			if (msg.is_left()) {
				if (msg.is_down()) {
					clickButton4 = insideRectButton(&button4, msg.x, msg.y);
					clickButton5 = insideRectButton(&button5, msg.x, msg.y);
				}
				else {
					//���̧���ж��Ƿ���Ҫִ���¼���Ӧ
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
				xyprintf(200,500,"����");
				Sleep(1000);
				cleardevice();
				break;
			}
			p2->next=NULL;
			xyprintf(200,500,"��ɴ���");
			Sleep(1000);
			editBox1.destory();//��������� 
			cleardevice();
			opeate(head);
			break; 
		}
	} 
	
}
void createdouble(){
	initgraph(1000,1000,INIT_RENDERMANUAL);
	setbkcolor(WHITE);
	setcaption("˫��������");
	sys_edit editBox1;
	editBox1.create(false);
	editBox1.size(200, 24 + 8);
	editBox1.setbgcolor(YELLOW);
	editBox1.setfont(24, 0, "����");
	editBox1.move(40, 40);
	editBox1.visable(false);
	editBox1.setfocus();
	const int buffSize = 100;//��ʼ������� 
	bool clickButton4 = false;
	bool clickButton5 = false;
	bool Button4rf = false;
	bool Button5rf = false;//��ť��ʼ��
	editBox1.visable(true);
	editBox1.settext("��������");
	char num[100];
	Sleep(2000);
	editBox1.settext("");
	cleardevice();
	struct LNode *head,*p1,*p2;
	int n=0; 
	head=(LNode*)malloc(sizeof(LNode));//����ͷ��ʼ�� 
	p1=p2=(LNode*)malloc(sizeof(LNode));//ָ�������ʼ��
	for (;is_run(); delay_fps(60)) {
		cleardevice();
		drawRectButton(&button4,"ȷ������");
		drawRectButton(&button5,"���");
		editBox1.visable(true);
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			//�ж�������������������ȷ��λ�ã�̧��Ϊִ��ʱ�̣�
			if (msg.is_left()) {
				if (msg.is_down()) {
					clickButton4 = insideRectButton(&button4, msg.x, msg.y);
					clickButton5 = insideRectButton(&button5, msg.x, msg.y);
				}
				else {
					//���̧���ж��Ƿ���Ҫִ���¼���Ӧ
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
				xyprintf(200,500,"����");
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
			xyprintf(200,500,"��ɴ���");
			Sleep(1000);
			editBox1.destory();//��������� 
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
	bool Button3rf = false;//��ʼ�����а�ť 
	for (;is_run(); delay_fps(60)) {
		cleardevice();
		drawRectButton(&button1,"�뿪");
		drawRectButton(&button2,"���쵥������");
		drawRectButton(&button3,"����˫������");
		setfont(24, 0, "����");
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			//�ж�������������������ȷ��λ�ã�̧��Ϊִ��ʱ�̣�
			if (msg.is_left()) {
				if (msg.is_down()) {
					clickButton1 = insideRectButton(&button1, msg.x, msg.y);
					clickButton2 = insideRectButton(&button2, msg.x, msg.y);
					clickButton3 = insideRectButton(&button3, msg.x, msg.y);
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
			xyprintf(240, 360, "�����˳�");
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
