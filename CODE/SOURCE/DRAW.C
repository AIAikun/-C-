#include<common.h>
#include<draw.h>
/**************************
	����ͼģ�顿
	��д�ˣ���ĭ��
**************************/
void drawmenu()
{
	cleardevice();
	setbkcolor(BLUE);
	setfillstyle(1, LIGHTGRAY);
	bar(1, 1, 640,24);
	bar(1, 456, 640, 480);
	bar(1, 1, 10, 480);
	bar(97,1,177,24);
	bar(274,1,354,24);
	bar(451,1,533,24);
	//bar(624, 25, 640, 455);
	setcolor(DARKGRAY);
	line(97,1,97,24);
    line(177,1,177,24);
    line(274,1,274,24);
    line(354,1,354,24);
    line(451,1,451,24);
    line(531,1,531,24);
	setcolor(RED);
    line(618,7,630,19);
    line(618,19,630,7);
	puthz(121,5,"�ļ�", 16, 16,DARKGRAY);
	puthz(210,5,"����",16, 16,DARKGRAY);
	puthz(298,5,"�༭", 16, 16,DARKGRAY);
	puthz(386,5,"��ͼ", 16, 16,DARKGRAY);
	puthz(475,5,"����", 16, 16,DARKGRAY);
	puthz(24,458,"��", 16, 16,DARKGRAY);
    puthz(100,458,"��", 16, 16,DARKGRAY);
}

void drawfile()    //������ļ�����ʾ���Ӳ˵� 
{
    setcolor(LIGHTGRAY);
    bar(97,25,177,140);
    setcolor(DARKGRAY);
    line(97,25,177,25);//�½���ť 
    line(97,48,177,48);//�򿪰�ť 
    line(97,71,177,71);//���水ť 
    line(97,94,177,94);//����Ϊ��ť 
	line(97, 117, 177, 117);//�˳���ť
    puthz(121,29,"�½�", 16, 16,DARKGRAY);
    puthz(121,52,"��", 16, 16,DARKGRAY);
    puthz(121,75,"����", 16, 16,DARKGRAY);
    puthz(117,98,"����Ϊ", 16, 16,DARKGRAY);
	puthz(121, 121, "�˳�", 16, 16, DARKGRAY);
}

void drawedit()//������༭����ʾ���Ӳ˵�
{
    setcolor(LIGHTGRAY);
    bar(274,25,354,163);
    setcolor(DARKGRAY);
    line(274,25,354,25);//���ư�ť 
    line(274,48,354,48);//ճ����ť 
    line(274,71,354,71);//�滻��ť 
    line(274,94,354,94);//���Ұ�ť 
    line(274,117,354,117);//���а�ť 
	line(274, 140, 354, 140);//�˳���ť
    puthz(298,29,"����", 16, 16,DARKGRAY);
    puthz(298,52,"ճ��", 16, 16,DARKGRAY);
    puthz(298,75,"�滻", 16, 16,DARKGRAY);
    puthz(298,98,"����", 16, 16,DARKGRAY);
    puthz(298,121,"����", 16, 16,DARKGRAY);
	puthz(298, 144, "�˳�", 16, 16, DARKGRAY);
 } 
 
 void drawhelp()    //�������������ʾ���Ӳ˵� 
{
    setcolor(LIGHTGRAY);
    bar(451,25,531,94);
    setcolor(DARKGRAY);
    line(451,25,531,25);//���ڰ�ť 
    line(451,48,531,48);//������ť 
	line(451, 71, 531, 71);//�˳���ť
    puthz(475,29,"����",16, 16,DARKGRAY);
    puthz(475,52,"����", 16, 16,DARKGRAY);
	puthz(475, 75, "�˳�", 16, 16, DARKGRAY);
} 
 void drawview()    //�������ͼ����ʾ���Ӳ˵�
 {
	 setcolor(LIGHTGRAY);
	 bar(386, 25, 451, 94);
	 setcolor(DARKGRAY);
	 line(386, 25, 451, 25);//ȫ����ť 
	 line(386, 48, 451, 48);//�Ŵ�ť 
	 line(386, 71, 451, 71);//��С��ť 
	 line(386, 94, 451, 94);//�˳���ť 
	 puthz(410, 29, "ȫ��", 16, 16, DARKGRAY);
	 puthz(410, 52, "�Ŵ�", 16, 16, DARKGRAY);
	 puthz(410, 75, "��С", 16, 16, DARKGRAY);
 }
 void drawcompile()    //��������롱��ʾ���Ӳ˵�
 {
	 setcolor(LIGHTGRAY);
	 bar(210, 25, 274, 94);
	 setcolor(DARKGRAY);
	 line(210, 25, 274, 25);//���밴ť 
	 line(210, 48, 274, 48);//���а�ť 
	 line(210, 71, 274, 71);//���԰�ť 
	 line(210, 94, 274, 94);//�˳���ť 
	 puthz(234, 29, "����", 16, 16, DARKGRAY);
	 puthz(234, 52, "����", 16, 16, DARKGRAY);
	 puthz(234, 75, "����", 16, 16, DARKGRAY);
 }
void drawrc(int r, int c)//��ʾ����������
{
	char row[3];
	char col[3];
	itoa(r,row,10);
	itoa(c,col,10);
	setfillstyle(1, LIGHTGRAY);
	bar(40, 458, 90, 474);
	bar(116, 458, 166, 474);
	settextstyle(0,0,1);
	setcolor(WHITE);
	outtextxy(48,464,row);
	outtextxy(124,464,col);
}

void drawwin(int x,int y)//����Ҽ����ʱ��ʾ�ĸ��Ƽ���ճ��
{
	setfillstyle(1, LIGHTGRAY);
	bar(x,y,x+63,y+51);
	setcolor(DARKGRAY);
	line(x,y,x+63,y);
	line(x+63,y,x+63,y+51);
	line(x,y+51,x+63,y+51);
	line(x,y,x,y+51);
	line(x,y+17,x+63,y+17);
	line(x,y+34,x+63,y+34);
	puthz(x+16,y+1,"����", 16, 16,DARKGRAY);
	puthz(x+16,y+18,"����", 16, 16,DARKGRAY);
	puthz(x+16,y+35,"ճ��", 16, 16,DARKGRAY);
	
}

void full_skbar()//��һ��ȫ���ǵ��϶��� 
{
	setfillstyle(1, LIGHTGRAY);
	bar(628,25,640,41);//���ư�ť 
	bar(628,440,640,456);//���ư�ť 
	setcolor(WHITE);
	line(634,25,628,33);
	line(634,25,640,33);
	line(634,25,634,41);//������ϼ�ͷ
	line(634,456,628,448);
	line(634,456,640,448);
	line(634,456,634,440);//������¼�ͷ 
	setfillstyle(1, DARKGRAY);
	bar(628,41,640,440);//�϶���ռ��Ԥ��λ�� 	
}

