#include<common.h>
#include"INSERT.h"

/*********************************************
	【文本基础编辑模块】
	编写人：桂熙严 
insert用于执行字符插入操作；
deltext用于执行删除操作 ；
enter用于执行换行操作；
match用于执行括号引号匹配操作。 
movepic用于复制操作 
*********************************************/

//作用：将x1,y1处长为l的列图像保存，再放到x2,y2处 ，用于复制 
int movepic(int x1,int y1,int l,int x2)
{
	void *pic;//图像指针 
	pic=malloc(imagesize(x1,y1,x1+7+l*8,y1+15));//获取大小 
	getimage(x1,y1,x1+7+(l-1)*8,y1+15,pic);
	setcolor(WHITE); 
	putimage(x2,y1,pic,0);
	free(pic);
	return 0;
}
//检查传入的指针后面有几个节点并返回这个值 
int getlen(node* p)
{
	int i=1;
	while(p->next!=NULL)
	{
		i++;
		p=p->next;
	}
	return i;
}

//功能：检查一行有多少字符并返回这个值 ,不包含回车符号 
int getlinelen(Lnode *q)
{
	if(q==NULL){
		return 0;
	}
	else
	{
	int i;
	node* p;
	p=q->next;
	for(i=0;(p->txt[0]!=13)&&(p!=NULL);i++)//注意这里是节点本身的性质 
	{
		p=p->next;
	}
	return i;
	}
 } 
 //功能：找到这一行最后一个节点 
node* endofline(Lnode*q){
		int i;
	node* p;
	p=q->next;
	for(i=0;(p->next->txt[0]!=13)&&(p!=NULL);i++)//注意这里是节点本身的性质 
	{
		p=p->next;
	}
	return p;
}
//功能：找到倒数第二个节点
node*lastendline(Lnode*q){
	
	node*p;
	{
		for(p=q->next;(p->next->next!=NULL&&p->next->next->txt[0]!=13);p=p->next){;}
	}
	return p;
}
//记录总像素数 
int getline(Lnode*q) 
{
	int sum,i;
	node*p;
	p=q->next;
	sum=0;
    for(i=0;i<getlinelen(q);i++){
    	if(p->sign==1&&p->txt[0]!=13) sum+=16;
    	else if(p->txt[0]!=13) sum+=8;
    	p=p->next;
	}
	
	return sum;
	
}


int  insert(char* bioget,int m,int n,Lnode*startline)//传入的数据包括了指定的行，列，要输出字符的指针，当前第一行的头结点 ,处理的是英文，汉有其他函数
{
	int i,m1;//标志列的位置 
	Lnode* q1,*q2,*q3;//此指针为指向行的指针 
	node*p1,*p2,*p3,*p4;//此指针为指向一个数据节点的指针 
	q1=startline;//q1指向当前显示区域的第一行 
	for(i=1;i<m;i++)
		q1=q1->nextl;//循环使得q1移动到第m行 
	p1=q1->next;//p1指向第m行的第一列 
	for(i=1;i<n-1;i++)//循环到第n-1列,指针已经到光标位置
		{
			p1=p1->next;
			if(p1->sign==1)	i++;	//如果遇到汉字，检测的列后移一位 (因为汉字占两列 ），需要在2个字符位置处进行插入 
		}
		//完成初始化
if(p1->next!=NULL)//行间输入
{
		if(n==1) //处理第一列插入 
		{
			if(getline(q1)<kuandu) //一行未满 
			{
				p2=(node*)malloc(sizeof(node));
				p2->txt[0]=bioget[0];p2->txt[1]='\0';p2->sign=0; p2->flag=WHITE;
				p2->next=p1;//与p1连接 
				q1->next=p2; //p2为新的头结点 
				delcursor();//清除光标 
				clrmous(MouseX,MouseY);//清楚鼠标 
				movepic(cursorX,cursorY,getlinelen(q1),cursorX+8);//向后移动
				setfillstyle(1, BLUE);
				bar(cursorX,cursorY,cursorX+7,cursorY+15);//把第一个除掉 
				settextstyle(0,0,1);
				setcolor(WHITE);
				outtextxy(cursorX,cursorY+6,bioget); //将键盘输入的字符进行显示 
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);//重画 
				cursorX+=8;//记录光标移动8个像素的位置 
				imgflag=0; 
				newcursor();//更新光标  
			}
			else if(getline(q1)==kuandu) //一行已经满了 
			 {
				p2=(node*)malloc(sizeof(node));
				p2->txt[0]=bioget[0];p2->txt[1]='\0';p2->sign=0;p2->flag=WHITE;
				p2->next=q1->next;
				q1->next=p2; //先连接起来 
			    p3=lastendline(q1);
			    p4=endofline(q1);
				if(q1->nextl==NULL)//如果下一个行节点是空的，新建一行 
				{
					q2=(Lnode*)malloc(sizeof(Lnode));
					q2->next=p4;
					q2->nextl=NULL;
					q1->nextl=q2;
					p3->next=NULL;
					p4->next=NULL;
				}
			    else if(getline(q1->nextl)<kuandu)//下一行没满 
				{
						q2=q1->nextl;
					p4->next=q2->next;
					q2->next=p4;
					p3->next=NULL;
				}	
			view(startline);
				cursorX+=8;
				imgflag=0;
				newcursor();
	        }
	   }
		else
		{
		//处理不在第一列的插入
		    if(getline(q1)<kuandu)//本行未满 
			{
				p2=(node*)malloc(sizeof(node));
				p2->txt[0]=bioget[0];p2->txt[1]='\0';p2->sign=0; p2->flag=WHITE;
			   p2->next=p1->next;
			   p1->next=p2;
			   delcursor();//清除光标 
				clrmous(MouseX,MouseY);//清楚鼠标 
				movepic(cursorX,cursorY,getlen(p1),cursorX+8);
				setfillstyle(1, BLUE);
				bar(cursorX,cursorY,cursorX+7,cursorY+15);
				settextstyle(0,0,1);
				setcolor(WHITE);
				outtextxy(cursorX,cursorY+6,bioget); //将键盘输入的字符进行显示 
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);//重画 
				cursorX+=8;//记录光标移动8个像素的位置 
				imgflag=0; 
				newcursor();//更新光标 
			   
			}
			else//本行已经满了
			{
				p2=(node*)malloc(sizeof(node));
				p2->txt[0]=bioget[0];p2->txt[1]='\0';p2->sign=0; p2->flag=WHITE;
				p2->next=p1->next;
			   p1->next=p2;
				p4=endofline(q1);
				p3=lastendline(q1);
				if(q1->nextl==NULL)//下一行未开启
				{	
					q2=(Lnode*)malloc(sizeof(Lnode));
					q2=q1->nextl;
					q2->nextl=NULL;
					q2->next=p4;
					p3->next=NULL;
				}
				else//下一行已经开启
				{
					q2=q1->nextl;
					p4->next=q2->next;
					q2->next=p4;
					p3->next=NULL;
				}
				view(startline);
				cursorX+=8;
				imgflag=0;
				newcursor();
			}
	   }
  }
   else//行末尾输入（广义上的行末尾 ,是下一个没有节点 
    {
		if(n==1)//处理在第一个位置输入 
		{
			if(p1!=NULL)// 处理在第一个位置有节点的情况，此时不需要新建 
			{
				p1->txt[0]=bioget[0];
				p1->txt[1]='\0';
				p1->sign=0;
				p1->next=NULL;
				p1->flag=WHITE;//后面是图形操作 
				delcursor();
				clrmous(MouseX,MouseY);
				setcolor(WHITE);
				settextstyle(0,0,1);
				outtextxy(cursorX,cursorY+6,bioget); 
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);
				cursorX+=8;
				imgflag=0;
				newcursor();
			} 
			else//处理在第一个位置没有节点的情况 
			{
				p1=(node*)malloc(sizeof(node));//新建 
				p1->txt[0]=bioget[0];
				p1->txt[1]='\0';
				p1->sign=0;
				p1->next=NULL;
				p1->flag=WHITE;
				delcursor();
				clrmous(MouseX,MouseY);	
				settextstyle(0,0,1);
				setcolor(WHITE);
				outtextxy(cursorX,cursorY+6,bioget); 
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);
				cursorX+=8;
				imgflag=0;
				newcursor();
			}
			
		}//处理不在第一列的 行尾 
		else 
		{
		 if(getline(q1)==kuandu)//处理在行末尾输入（狭义的尾部 
		 {			
			p2=(node*)malloc(sizeof(node));//新建一个节点 存数据 
			p2->txt[0]=bioget[0];
			p2->txt[1]='\0';
			p2->sign=0;
			p2->flag=WHITE;
		    p1->next=NULL; 
			if(q1->nextl==NULL)//如果下一个行节点是空的，新建一行 
			{
				q2=(Lnode*)malloc(sizeof(Lnode));
				q2->next=p2;
				p2->next=NULL;
				q2->nextl=NULL;
				q1->nextl=q2;
			}
			delcursor();
			clrmous(MouseX,MouseY);
			settextstyle(0,0,1);
			setcolor(WHITE);
			cursorX=17;
			cursorY+=16;
			outtextxy(cursorX,cursorY+6,bioget); 
			save_bk_mou(MouseX,MouseY); 
			drawmous(MouseX,MouseY);
			cursorX+=8;
			imgflag=0;
			newcursor();
		}
		else //处理在中间列且行未满的行尾 
		{
			p2=(node*)malloc(sizeof(node));
			p2->txt[0]=bioget[0];p2->flag=WHITE;
			p2->txt[1]='\0';
			p2->sign=0;
			p2->next=NULL;
			p1->next=p2;
			delcursor();//顺序：清光标，清屏，确定颜色以及形式，显示文字，回复鼠标以及背景 ，回复光标 
			clrmous(MouseX,MouseY);
			settextstyle(0,0,1);
			setcolor(WHITE);
			outtextxy(cursorX,cursorY+6,bioget); 
			save_bk_mou(MouseX,MouseY); 
			drawmous(MouseX,MouseY);
			cursorX+=8;
			imgflag=0;
			newcursor();
		} 
      }
	} 
	return 0;	
}
//功能：执行enter的换行操作；
void enter(int m,int n,Lnode* startline)
{
	int i;
	Lnode* q1,*q2;//此指针为指向一行数据的指针 
	node*p1,*p2,*p3;//此指针为指向一个数据节点的指针 
	q1=startline;//q1指向当前显示区域的第一行 

	for(i=1;i<m;i++)
		q1=q1->nextl;//循环使得q1移动到第m行 
	p1=q1->next;//p1指向第m行的第一列 
	for(i=1;i<n-1;i++)//循环到第n-1列
		{
			p1=p1->next;
			if(p1->sign==1)	i++;//如果遇到汉字，检测的列后移一位 (因为汉字占两列 
			
		}
	p2=(node*)malloc(sizeof(node));
			p2->txt[0]=13;
			p2->txt[1]='\0';
			p2->sign=0;
	q2=(Lnode*)malloc(sizeof(Lnode));
	if(n==1)//处理在一行开头的情况 
	{	
		if(q1->nextl!=NULL) // 下一行有东西 
		{
			q2->nextl=q1->nextl;
			q1->nextl=q2;
			q2->next=p1;
			q1->next=p2;
			p2->next=NULL;
		}
		else//下一行空 
		{
			q2->next=p1;
			q1->next=p2;
			q1->nextl=q2;
			q2->next=NULL;
		}
	}
	else//处理不在一行开头的情况 
	{
		if(q1->nextl!=NULL)//处理有下一行的情况 
		{
			q2->nextl=q1->nextl;
			q1->nextl=q2;
			if(p1->next!=NULL)
			{ 
				q2->next=p1->next;
				p1->next=p2;
				p2->next=NULL;
			}
			else
			{
				p1->next=p2;
				q2->next=NULL;
			}
		}
		else//处理没有下一行的情况 
		{
			if(p1->next!=NULL)
			{
				q2->next=p1->next;
				q2->nextl=NULL;
				q1->nextl=q2;
				p1->next=p2;
				p2->next=NULL;
			}
			else{
				q1->nextl=q2;
				q2->nextl=NULL;
				q2->next=NULL;
				p1->next=p2; 
			}
			
		}
	}
	 if(m==27)//最后位置的换行添加了自动翻页功能 
	{
		down_page(startline,&startline);
		cursorY-=16;//光标位置不发生变化，与下面+16抵消掉 
	}
	view(startline);
	cursorX=17;
	cursorY+=16;
	imgflag=0;			

}
 
//用于检测括号引号并进行相应的匹配 
void match(char* bioget,Lnode* startline)
{
	char match[2]={'\0','\0'};
	if(bioget[0]-'('==0)//左括号 （用键值差为0判别 
	{
		match[0]=41;
		insert(match,((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
	}
	else if(bioget[0]-'{'==0)//左花括号 
	{
		match[0]=125;//键值为125 
		insert(match,((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
	}
	else if(bioget[0]==34)//pagedown 键位 
	{
		insert(bioget,((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
	}
	else if(bioget[0]-'['==0)//左方括号 
	{
		match[0]=93;
		insert(match,((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
	}
	else if(bioget[0]-'<'==0)//左三角号 
	{
		match[0]=62;
		insert(match,((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
	}
	else if(bioget[0]==39)//右方向键 ？？？ 
	{
		insert(bioget,((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
	}
}
//删除指定字符函数 ，也是退格删除键位的输入效果 
int deltext(Lnode*startline,int r,int c) //传入行指针，光标所在的行数以及列数，这里是del以及backspace的操作 ，r行c列 
{
   int m=0,sum=0,i,rest,len,len1=0;
	Lnode*q1,*q2,*q3;
	node*p1,*p2,*p3,*p4,*p5,*p6;
	q1=startline;
	for(i=1;i<r;i++)
		{
		   q2=q1; 
		   q1=q1->nextl;
		}
	p1=q1->next;
	for(i=1;i<c-2;i++)//循环到该列前2列 
		{
			p1=p1->next;
		if(p1->next->sign==1)	i++;//如果遇到汉字，检测列后移一位 
		} 
	p2=p1->next;//下一个节点 。是当前的节点 
if(c==1) //行首
{
	if(r==1)//在第一行行首
	{
		return 0; 
	}
	else//不在第一行开头 
	{
		if(getline(q2)==kuandu) //上一行满了
		{
			p3=lastendline(q2);
			p4=endofline(q2);
			if(p4->sign==0)//上一行字符结尾 
			{
				cursorX=600;
				if(p1->sign==0)
				{
					cursorX=600;
					free(p4);
			       p3->next=p1;
			       q1->next=p1->next;
		           p1->next=NULL;
				}
				else
				{
					cursorX=600;
					free(p4);
					p3->next=NULL;
				}
			} 
			else//上一行汉字结尾 
			{
				if(p1->sign==1)//这一行汉字开头 
				{
					cursorX=kuandu-16;
					free(p4);
			       p3->next=p1;
			       q1->next=p1->next;
		           p1->next=NULL;
				}
				else//这一行字符开头 
				{
					cursorX=kuandu-16;
					free(p4);
			       p3->next=p1;
			       q1->next=p1->next;
		           p1->next=NULL;
				}
			}
			
			cursorY-=16;
			view(startline);
			imgflag=0;
			newcursor();
		 } 
		else//上一行没满
		{
		  if(getline(q2)>=1)
		  {
			p3=endofline(q2);
			p3->next=p1;
			rest=kuandu-getline(q2);
			len=getline(q1);//本行长度 
			m=getline(q2);//上一行长度 
			
			
			 if(len<=rest)//上一行的长度能够容纳下一行的全部
			{
				q2->nextl=q1->nextl;
				free(q1);
				if(endofline(q2)->next->txt[0]==13) 
				free(endofline(q2)->next);
				cursorX=m+17 ;
				cursorY-=16;
				view(startline);
				imgflag=0;
				newcursor();
				
			 } 
			 else//如果不能完全填入，则只对一个文字向上移动
			{
				p1=q1->next;
				p2=p1->next; 
				q1->next=p2; 
				p3=endofline(q2);
				if(p3->next->txt[0]==13)
				free(p3->next);
				p6=(node*)malloc(sizeof(node));
				p6->txt[0]=13;
				p6->txt[1]='\0';
				p6->next=NULL;
				p1->next=p6;
			    p3->next=p1;
			    delcursor();
			    cursorX=17;
			    view(startline);
				imgflag=0;
				newcursor();
				
			 }
		   }
		   else  if(q2->next==NULL||q2->next->txt[0]==13)//上一行空 
		   {
		   	  q2->next=p1;
		   	  q2->nextl=q1->nextl;
		   	  free(q1);
		   	  cursorX=17;
		   	  cursorY-=16;
		   	  view(startline);
				imgflag=0;
				newcursor();
		   	  
		   }
		 } 
	 } 
  }
else//行间删除
    {  
	  if((p2->next==NULL)||(p2==NULL))//如果在末尾处 
		 {
			if(c==2&&p1->sign==0) //如果光标在第二个元素的位置，删除第一个字符 ，因为涉及行连表内的改变，因此需要单独讨论 
			{
				free(p1);
				q1->next=NULL;
				delcursor();
				clrmous(MouseX,MouseY);
				setfillstyle(1, BLUE);
				bar(cursorX-8, cursorY, cursorX,cursorY+15);
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);
				cursorX-=8;
				imgflag=0;
				newcursor();
				
			}
			else if(c==2&&p1->sign==1)
			{
				free(p1);
				q1->next=NULL;
				 delcursor();
				clrmous(MouseX,MouseY);
				setfillstyle(1, BLUE);
				bar(cursorX-8, cursorY, cursorX+8,cursorY+15);
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);
				cursorX+=8;
				imgflag=0;
				newcursor();
			}
			else if(c=3&&p1->sign==1)
			{
				free(p1);
				q1->next=NULL;
				 delcursor();
				clrmous(MouseX,MouseY);
				setfillstyle(1, BLUE);
				bar(cursorX-16, cursorY, cursorX,cursorY+15);
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);
				cursorX-=16;
				imgflag=0;
				newcursor();
			}
			else//不在第二个位置 或者行首汉字位置，不涉及行链表的变化 
			{
				if(p2->sign==0)//如果是字符
				{
					p1->next=NULL;//p1处结尾 ，上一个 
					free(p2);//释放节点 
					delcursor();
					clrmous(MouseX,MouseY);
					setfillstyle(1, BLUE);
					bar(cursorX-8, cursorY, cursorX,cursorY+15);//用蓝色填充来实现字符的删除 
					save_bk_mou(MouseX,MouseY); 
					drawmous(MouseX,MouseY);
					cursorX-=8;//光标向前移动 
					imgflag=0;
					newcursor();
				}
				else if(p2->sign==1)//如果是汉字
				{
					
					p1->next=NULL;
					free(p2);
					delcursor();
					clrmous(MouseX,MouseY);
					setfillstyle(1, BLUE);
					bar(cursorX-16, cursorY, cursorX,cursorY+15);//画两个字符 
					save_bk_mou(MouseX,MouseY); 
					drawmous(MouseX,MouseY);
					cursorX-=16;
					imgflag=0;
					newcursor();
				}  
			}
			
		}
		else//如果下节点非空，删掉此处节点，将后面的图像前移 
		{
			if(c==2) //如果光标在第二个位置，删除第一个字符 
			{
				q1->next=p2->next; 
				free(p2); 
				view(startline);//开始显示即可 
				cursorX-=8;
				imgflag=0;
				newcursor();
			}
			else//不在第二个位置 
			{
				if(p2->sign==0)//如果是字符
				{
					p1->next=p2->next;
					free(p2);
					view(startline);
					cursorX-=8;
					imgflag=0;	
					newcursor();		
				}
				else if(p2->sign==1)//如果是汉字
				{
					p1->next=p2->next;
					free(p2);
					setfillstyle(1, BLUE);
					bar(17, cursorY,kuandu,cursorY+15);
					delcursor();
					view(startline);
					cursorX-=16;
					imgflag=0;
				}  
			}
		} 
	} 
	return 0;	 
}
