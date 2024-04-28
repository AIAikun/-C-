//编写人：贾沫晗
#include<common.h>
#include<view.h>

//打印一次当前屏幕显示区域的代码 ,显示所有图像 
void view(Lnode* startline)
{
	int x=17,y=25,r=1,c=1;
	node* p; 
	Lnode* q; 
	clrmous(MouseX,MouseY);  //清除鼠标 
	setfillstyle(1, BLUE); 
	bar(17,25,623,455);//字符区域呈蓝色，显示全部图形框 
	for(q=startline;q!=NULL&&r<=27;r++)
	{
		p=q->next;
		for(;(p!=NULL)&&(p->txt[0]!=13);c++)
		{
			if(p->sign==1)
			{
				setcolor(WHITE);
				puthz(x,y,p->txt,16, 16,WHITE);
				x+=16;
				c++;
			}
			else if(p->sign==0)
			{
				setcolor(p->flag);//选择颜色 
				settextstyle(0,0,1);
				outtextxy(x,y+6,p->txt);
				x+=8;
			}
			p = p->next; //列指针指向下一个节点
		} 
		x=17;
		y+=16; //进入下一行第一列 
		q = q->nextl; //行指针指向下一个节点，进入下一行			
	}
	save_bk_mou(MouseX,MouseY); 
	drawmous(MouseX,MouseY);//还原 
}



 
//在XY位置输入一串字符并返回字符串长度 ,用于指定位置输入文件名等功能 ，传入需要存入文件名的数组 
int gettxtname(char* s,int x,int y)
{
	
	char a;//单个字符的声明（由于是一个一个的输出 
	char bio[2];//键盘输入 
	int i=0;
	while(1)
	{
		if (bioskey(1))//检测键盘输入 
			{
				a=bioskey(0);//获取键值 
				if(a>=32&&a<127)
				{
					bio[0]=a;
					bio[1]='\0';
					setcolor(WHITE);
					settextstyle(0,0,1);
					outtextxy(x,y,bio);//指定位置输出字符 
					x+=8;//移动一个字符宽度 
					s[i]=a;
					s[i+1]='\0';//暂时的结尾 
					i++;
				}
				else if(a==8)//点退格 ，用填充的方式删除 
				{
					if (i > 0)//如果有字符再删除 
					{
						setfillstyle(1, BLUE);
						bar(x - 8, y, x - 1, y + 16);
						i--;
						x -= 8;
					}
				}
				else if(a==13)//按回车结束输入 
				{
					break;
				}
			}
	
	}
	return i+1; 
}

//作用:检查某个坐标位置是否有字符，即节点是否为空 ,返回0为空，返回1为非空； 用于鼠标点击的识别 
int checktxt(int x,int y,Lnode* startline)
{
	int i=0;
	Lnode* q1;
	node* p1;
	q1=startline;
	for(i=1;i<y;i++)
	{
		q1=q1->nextl;
		if(q1==NULL)//如果这一行不存在返回0 。鼠标点击无效 
			return 0;
		
	}
	p1=q1->next; 
	for(i=1;i<x;i++)
	{
		if(p1==NULL)//如果这一行存在但是这个位置没有字符返回2 ，找到本行最后一个字符。将鼠标放在那个位置 
			return 2;
		else
		{
    	p1=p1->next;
		if(p1->sign==1)
		i++;
	    }
	}
	return 1; 
}

//功能：检查一共有多少行并返回行数 
int getllen(Lnode *Head)
{
	Lnode *q;
	int i;
	q=Head;
	for(i=1;q->nextl!=NULL;i++)
	{
		q=q->nextl;
	}
	return i;
 } 
 
