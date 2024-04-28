  #include<common.h>
#include"seekbar.h"

int count=0;//��¼up��down�Ĵ��������ڲ�ͬλ����ʾ�϶���
int countdown=0;//��¼���·�ҳ�Ĵ����������ڲ�ͬλ����ʾ�϶���

/**************************
	��������ģ�顿
	��д�ˣ���ĭ�� 
**************************/
void drawskbar(Lnode* Head)
{
	//�϶��������Ϊ16��432�ĳ����ΰ�顣���¸�ȡһ��16��16����������Ϊ���°���
	//��ʵ���϶���ͼ��ռ�ռ�Ϊ16��400�ĳ�����	
	int r;//��¼������
	int x;//�϶���Ӧ�г���  
	r=getllen(Head);//���������
	setfillstyle(1, LIGHTGRAY);
	bar(628,25,640,41);//���ư�ť 
	bar(628,440,640,456);//���ư�ť 
	bar(628, 25, 640, 455);//�϶�����
	setcolor(BLUE);
	line(634, 25, 628, 33);
	line(634, 25, 640, 33);
	line(634, 25, 634, 41);//������ϼ�ͷ
	line(634, 456, 628, 448);
	line(634, 456, 640, 448);
	line(634, 456, 634, 440);//������¼�ͷ 
	if(r<=27)
	{
		setfillstyle(1, DARKGRAY);
		bar(628,41,640,440);//�϶���ռ��Ԥ��λ�� 
	}
	else if(r>27)
	{
		x=(int)10773/r; //����϶������� (10773=27*339) 27�У�һ��339 
		setfillstyle(1, DARKGRAY);
		bar(628,41,640,41+x);
		
	} 
}
/************************************************************************
������up_page/down_page 
���ܣ� �����ı���Ĵ�Сֻ������27���ı�����Ҫ���з�ҳ�Ĳ�����Ҳ���Ǹ�����ʾ�ĵ�һ���е�����
       �������ͷ����ΪHead����������ͷ���֮���½�һ��������ָ�룬����startline��
       ��Cheadָ���λ����ָ����ǰӦ����ʾ�ĵ�һ�С���Ϊ��Ļ��С�����ƣ�ֻ����ʾstartlineָ������������26�е��ı���
       �ڴ��ݲ�����view�����Ⱥ���ʱ����startline����Head���롣
       �������������ֱ���ָ��startline����/����һ����λ 
************************************************************************/
int up_page(Lnode* Head,Lnode **startline)
{
	int r;//��¼������
	Lnode* q; //������ʾ�����ڵ������е��ı��ַ�,qΪָ���е������е�һ���ڵ��ָ�� 
	int i=0;
	q=Head;
	r=getllen(Head);//������������ 
	if((((int)(41+count*399/r))>=41)&&(count>0))//�����countup������϶������ϰ벿�֣����϶������ƣ�������һ��
	{
		for(i=0;i<(count-1);i++)
		{
			q=q->nextl;
		}
		*startline=q;//��q����startline	
		count--; 
		newskbar(Head,r);	
		if(countdown>0) 
		countdown--; 
	}
	return; 
}

int down_page(Lnode* Head,Lnode **startline)
{
	int r;//��¼������
	int x;//�϶���Ӧ�г��� 
	r=getllen(Head);
	x=(int)10773/r;
	if((((int)(41+x+count*399/r))<=440)&&(count<(r-27)))//�����countdown������϶������°벿�֣����϶������ƣ�������һ��
	{
		*startline=(*startline)->nextl;
		newskbar(Head,r);
		count++;
		countdown++;
	}
	return; 
}


int newskbar(Lnode* Head,int r)//���µ��϶��� 
{
	
	int x;//�϶���Ӧ�г��� 
	r=getllen(Head);
	x=(int)10773/r;
	clrmous(MouseX,MouseY);
	setfillstyle(1, LIGHTGRAY);
	bar(628,41,640,440);
	if((((int)(41+x+count*399/r)<=440))&&(((int)(41+count*399/r)>=41)))//�϶����ڹ涨��Χ��
	{
		setfillstyle(1, DARKGRAY);
		bar(628,(int)(41+count*399/r),640,(int)(41+x+count*399/r));//��λ����Ϊ399/r (����ÿ�У�
	}
	else if((((int)(41+x+count*399/r))>440))//�϶�����������
	{
		setfillstyle(1, DARKGRAY);
		bar(628,440-x,640,440);
	}	
	else if((((int)(41+count*399/r))<41))//�϶�����������
	{
		setfillstyle(1, DARKGRAY);
		bar(628,41,640,41+x);
	}
	save_bk_mou(MouseX,MouseY); 
	drawmous(MouseX,MouseY);
	return;
}

int click_skbar(Lnode* Head,Lnode **startline)
{
	int r;//��¼������
	int x;//�϶���Ӧ�г���
	int y1_skbar; //Ŀǰ�϶����϶�λ��
	int y2_skbar;//Ŀǰ�϶����¶�λ�� 
	int change_count1;//��¼�����count�ĸı���
	int change_count2;//��¼�����count�ĸı���
	int i=0; 
	Lnode* q;
	r=getllen(Head);
	x=(int)10773/r;
	q=Head;
	y1_skbar=(int)(41+x+count*399/r-x);//�϶����϶�λ��
	y2_skbar=(int)(41+x+count*399/r);//�϶����¶�λ��
	change_count1=(int)((y1_skbar-MouseY)*r/399);//��������count�ĸı���
	change_count2=(int)((MouseY-y2_skbar)*r/399);//��������count�ĸı���
	if(MouseY<y1_skbar)//���������϶����϶�
	{
		for(i=0;i<(change_count1);i++)
		{
			q=q->nextl;
		}
		*startline=q;		
		count--; 
		newskbar(Head,r);		
	}
	else if(MouseY>y2_skbar)//���������϶����¶�
	{
		for(i=0;i<change_count2;i++)
		{
			*startline=(*startline)->nextl;
			newskbar(Head,r);
			count++;
		}			
	} 
	else if((MouseY>=y1_skbar)&&(MouseY<=y2_skbar))//���������϶����м�
	{
		return;
	}	
	return;	
}
