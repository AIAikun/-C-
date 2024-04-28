#include<common.h>
#include<cursor.h>
int cursorX=17;
int cursorY=25;
char bitmap[30];//���ڴ������ͼ�� 
int imgflag=0;

/****************************
�����ģ�顿
��д�ˣ���ĭ��
drawcursor���ڻ��ƹ��
getcsim���ڱ������µ�ͼ���ֹ����
delcursor����ɾ����ǰ���
newcursor���ڸ��¹��
movecursor���ڽ�����ƶ�����y��x�е�λ��
************************/

void drawcursor()    //�����ƺ��� 
{
	static int i=0;//ѭ�����,�������ߺ����ߣ�������ʾ��꣬����ɾ����� �� 
	setlinestyle(0,0,1);
	//������
	if(i<50)       
	{
	setcolor(WHITE);
	line(cursorX,cursorY,cursorX,cursorY+16);
	}
	//������
	if(i==50) putimage(cursorX,cursorY,bitmap,0);\
	//����һ�ΰ��ߺ����ߺ�i���㣬���¿�ʼѭ��
	if(i==100) i=0;
	i++;
}

//ɾ����ǰ���
void delcursor()
{
	putimage(cursorX,cursorY,bitmap,0);
}

//���ڻ�ȡ��괦��ͼ��
void getcsim() 
{
	getimage(cursorX,cursorY,cursorX,cursorY+16,bitmap);
} 

//���¹�� 
void newcursor()
{
	if(imgflag==0)//�����û�д������ͼ�񣬾ʹ��棬��ֹ����ڸ���Ļ���� 
	{	
		clrmous(MouseX,MouseY);
		getcsim();
		save_bk_mou(MouseX,MouseY); 
		drawmous(MouseX,MouseY);
		imgflag=1;
	}
	drawcursor();//���ƹ�� 
}

//�ƶ���굽x��,y�� 
void movecursor(int x,int y)
{
	delcursor();
	cursorX=17+8*(x-1);
	cursorY=25+16*(y-1);
	imgflag=0;
}
