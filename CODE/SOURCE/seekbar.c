  #include<common.h>
#include"seekbar.h"

int count=0;//记录up和down的次数用以在不同位置显示拖动条
int countdown=0;//记录向下翻页的次数，用以在不同位置显示拖动条

/**************************
	【滑动条模块】
	编写人：贾沫晗 
**************************/
void drawskbar(Lnode* Head)
{
	//拖动条栏设计为16×432的长方形板块。上下各取一个16×16的正方形作为上下按键
	//故实际拖动条图形占空间为16×400的长方形	
	int r;//记录总行数
	int x;//拖动条应有长度  
	r=getllen(Head);//获得总行数
	setfillstyle(1, LIGHTGRAY);
	bar(628,25,640,41);//上移按钮 
	bar(628,440,640,456);//下移按钮 
	bar(628, 25, 640, 455);//拖动条栏
	setcolor(BLUE);
	line(634, 25, 628, 33);
	line(634, 25, 640, 33);
	line(634, 25, 634, 41);//组成向上箭头
	line(634, 456, 628, 448);
	line(634, 456, 640, 448);
	line(634, 456, 634, 440);//组成向下箭头 
	if(r<=27)
	{
		setfillstyle(1, DARKGRAY);
		bar(628,41,640,440);//拖动条占满预留位置 
	}
	else if(r>27)
	{
		x=(int)10773/r; //获得拖动条长度 (10773=27*339) 27行，一行339 
		setfillstyle(1, DARKGRAY);
		bar(628,41,640,41+x);
		
	} 
}
/************************************************************************
函数：up_page/down_page 
功能： 由于文本框的大小只能容纳27行文本，需要进行翻页的操作，也就是更改显示的第一个行单链表。
       行链表的头结点称为Head。在行链表头结点之外新建一个行链表指针，称作startline。
       用Chead指向的位置来指定当前应当显示的第一行。因为屏幕大小的限制，只会显示startline指向的行链表及其后26行的文本。
       在传递参数给view函数等函数时，将startline代替Head传入。
       以上两个函数分别是指将startline上移/下移一个单位 
************************************************************************/
int up_page(Lnode* Head,Lnode **startline)
{
	int r;//记录总行数
	Lnode* q; //按行显示保存在单链表中的文本字符,q为指向行单链表中第一个节点的指针 
	int i=0;
	q=Head;
	r=getllen(Head);//这里是总行数 
	if((((int)(41+count*399/r))>=41)&&(count>0))//如果有countup并点击拖动条的上半部分，则拖动条上移，且上移一行
	{
		for(i=0;i<(count-1);i++)
		{
			q=q->nextl;
		}
		*startline=q;//把q给回startline	
		count--; 
		newskbar(Head,r);	
		if(countdown>0) 
		countdown--; 
	}
	return; 
}

int down_page(Lnode* Head,Lnode **startline)
{
	int r;//记录总行数
	int x;//拖动条应有长度 
	r=getllen(Head);
	x=(int)10773/r;
	if((((int)(41+x+count*399/r))<=440)&&(count<(r-27)))//如果有countdown并点击拖动条的下半部分，则拖动条下移，且下移一行
	{
		*startline=(*startline)->nextl;
		newskbar(Head,r);
		count++;
		countdown++;
	}
	return; 
}


int newskbar(Lnode* Head,int r)//画新的拖动条 
{
	
	int x;//拖动条应有长度 
	r=getllen(Head);
	x=(int)10773/r;
	clrmous(MouseX,MouseY);
	setfillstyle(1, LIGHTGRAY);
	bar(628,41,640,440);
	if((((int)(41+x+count*399/r)<=440))&&(((int)(41+count*399/r)>=41)))//拖动条在规定范围内
	{
		setfillstyle(1, DARKGRAY);
		bar(628,(int)(41+count*399/r),640,(int)(41+x+count*399/r));//单位长度为399/r (像素每行）
	}
	else if((((int)(41+x+count*399/r))>440))//拖动条超出下限
	{
		setfillstyle(1, DARKGRAY);
		bar(628,440-x,640,440);
	}	
	else if((((int)(41+count*399/r))<41))//拖动条超出上限
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
	int r;//记录总行数
	int x;//拖动条应有长度
	int y1_skbar; //目前拖动条上端位置
	int y2_skbar;//目前拖动条下端位置 
	int change_count1;//记录点击后count的改变量
	int change_count2;//记录点击后count的改变量
	int i=0; 
	Lnode* q;
	r=getllen(Head);
	x=(int)10773/r;
	q=Head;
	y1_skbar=(int)(41+x+count*399/r-x);//拖动条上端位置
	y2_skbar=(int)(41+x+count*399/r);//拖动条下端位置
	change_count1=(int)((y1_skbar-MouseY)*r/399);//计算点击后count的改变量
	change_count2=(int)((MouseY-y2_skbar)*r/399);//计算点击后count的改变量
	if(MouseY<y1_skbar)//如果点击在拖动条上端
	{
		for(i=0;i<(change_count1);i++)
		{
			q=q->nextl;
		}
		*startline=q;		
		count--; 
		newskbar(Head,r);		
	}
	else if(MouseY>y2_skbar)//如果点击在拖动条下端
	{
		for(i=0;i<change_count2;i++)
		{
			*startline=(*startline)->nextl;
			newskbar(Head,r);
			count++;
		}			
	} 
	else if((MouseY>=y1_skbar)&&(MouseY<=y2_skbar))//如果点击在拖动条中间
	{
		return;
	}	
	return;	
}
