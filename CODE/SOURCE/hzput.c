#include<common.h>
#include<HZPUT.h> 
extern int cursorX;
/************************
【汉字输入法】
 hz_put处理输入
  input_method用于为用户提供方法选取 
************************/ 
int hz_put(int cursorX,int cursorY,int m,int n,Lnode*startline)//传入光标位置 ,行列数 
{ 
	int asc,pylen,kbget=0,i,maxhz,len;//记录键值 ;
	int barx1,barx2,bary1,bary2;
	int method=-1;//输入法返回方式：1.按SPACE键返回输入汉字 2.按ENTER键返回输入英文 3.退格键返回不输入
	void *image;//图像指针 
	char *p,temp ;
	Lnode* q1,*q2;
	node*p1,*p2,*p3;
	char str[3]={'\0','\0','\0'};//储存一个汉字 
	char py[12]={'\0','\0','\0','\0','\0','\0','\0','\0',
	            '\0','\0','\0','\0'};//拼音字符串(西文字符串)
	q1=startline;//q1指向当前显示区域的第一行 
	for(i=1;i<m;i++)
		q1=q1->nextl;//循环使得q1移动到第m行 
	len=getline(q1);
	if(q1->next==NULL)//如果这一行还没有被开启
	 {
	 	p2=(node*)malloc(sizeof(node));//新建一个节点 
	     q1->next=p2;
		 p2->sign=1;
	 }
	 else //这一行有元素 
	{
	if((kuandu-len)<16)//行宽不够 
	{
			p1=q1->next;//p1指向第m行的第一列 
	      for(i=1;i<n-1;i++)//循环到第n-1列
		   {
			p1=p1->next;
			if(p1->sign==1)	i++;//如果遇到汉字，检测列后移一位 (因为汉字占两列 
		   }  
	      p3=(node*)malloc(sizeof(node));//新建一个节点 
	      p3->sign=0;
	      p3->txt[0] =13;
	      p3->txt[1]='\0';
	      p1->next=p3;
	      p3->next=NULL;
	      p2=(node*)malloc(sizeof(node));//新建一个节点 
	      p2->sign=1;	//记录节点态为汉字 
	      if(q1->nextl==NULL) 
	      {
	      	q2=(Lnode*)malloc(sizeof(Lnode));
	        q1->nextl=q2;
	      	q2->nextl=NULL;
	      	q2->next=p2;
	      	p2->next=NULL;
	      	cursorX=17;
	        cursorY+=16;

		  }
		  else
		  {
		  q2=q1->nextl;
		  p2->next=q2->next;
		  q2->next=p2;
		  cursorX=17;
	      cursorY+=16;
		  }
	}
	else //行宽足够 
	{
	
	   p1=q1->next;//p1指向第m行的第一列 
	   for(i=1;i<n-1;i++)//循环到第n-1列
		{
			p1=p1->next;
			if(p1->sign==1)	i++;//如果遇到汉字，检测列后移一位 (因为汉字占两列 
		}  
	   p2=(node*)malloc(sizeof(node));//新建一个节点 
	   p2->sign=1;	//记录节点态为汉字 
	   if(p1->next!=NULL)//有下一个 
	   {
		p3=p1->next;
		p2->next=p3;
		p1->next=p2;
		                                                                                                                                                                                                                                              
       }
	    else//p1后面没有 ，行尾 
	   {   
	    p1->next=p2;
		p2->next=NULL;
       }
    }
	}     
	settextjustify(LEFT_TEXT,CENTER_TEXT);//设置文字样式 （对齐方式 
	clrmous(MouseX, MouseY);//清除鼠标

	while(bioskey(1))//清除键盘缓冲区  防止误输入
	{
		bioskey(0);
	}
	if((image=malloc(8241))==NULL)//获取一个图像 失败 
	{
		closegraph();
		printf("error!,hz_input");
		getch(); 
		exit(1);
	}
	while(1)
	{
		if(kbhit())//检测有无键盘输入，有返回非0 ，每次检测一个符号 
		{
			kbget=bioskey(0);//记录键值 ;
		
			/*进入汉字输入法*/																
			asc=kbget&0xff;//取余数 
			if(asc>=97&&asc<=122)
			{
				barx1=(cursorX+8-50>0)?(cursorX+8-50):0;       //计算输入法位置  离所输入距离较近且不溢出屏幕
	    		barx2=(barx1+200<630)?(barx1+200):(barx1=430,630);
				bary1=cursorY+40;
				bary2=(bary1+40<480)?(bary1+40):(bary1=cursorY-80,bary1+40);
				getimage(barx1,bary1,barx2,bary2,image);//将输入框处的原有图像保存，防止覆盖导致的丢失 
				pyFrm(barx1,bary1,barx2,bary2);//该位画出输入框 
				setfillstyle(1,RED);
				method=input_method(barx1,bary1,str,kbget,py);// 选择方式 
				switch(method)//选返回方式 
				{
					case 1://由数字键或空格键退出输入法  输入汉字
					    if(strlen(str))//返回字符串可能为空
						{
							strcpy(p,str);//返回的付给p ，一个汉 
							strcpy(p2->txt,p);
						}
							puthz(cursorX,cursorY,str,16,16,WHITE);
						putimage(barx1,bary1,image,0);
						free(image); 
						settextjustify(0,2);
					    return 0;
					case 2://由回车键退出输入法 （键入西文）
						pylen=strlen(py);//记录键入长度 
						putimage(barx1,bary1,image,0);
						free(image);
						for(i=0;i<pylen-1;i++) 
						{
							settextjustify(0,2);
							insert(&py[i],((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
							delcursor();
						}
						strcpy(p,py);
						p+=pylen;
						settextjustify(0,2);
					    return 0;
					case 3://西文删除为0自动退出输入法 不输出，输出空格 
						putimage(barx1,bary1,image,0);
						free(image);
					    break;
					case 4:
						putimage(barx1,bary1,image,0);
						free(image);
						settextjustify(0,2);//文本的对齐方式函数 
						return 1;
				}
				kbget=0;
				method=-1;
			}
			else if(asc>31&&asc<127)//字符输入
			{
				continue;//继续循环 
			}
			else if(kbget==ESC)
			{
				settextjustify(0,2);
				return 1;
			}
			memset(py,'\0',12);//函数作用：将某快内存设定为指定的值 ，重新赋0 
			memset(str,'\0',3);
		}
		
		
	}
}

//下面是学长代码 
/***********************************************************************
FUNCTION:input_method
DESCRIPTION: 汉字输入法调入
INPUT:x,y,str,value,py
RETURN:1:输出汉字；2：输出字母；3：输出空格
************************************************************************/

int input_method(int x,int y,char *str,int value,char *py)//返回一个数，决定输出方式 ，传入输入的按键值 
{
	FILE *fp=NULL,*oldfp=NULL;//两个文件 
	int fJudge=FAIL;
	char *p=py;//py给p储存 ，临时储存要输入的符，便于修改 
	int trigger=1;//进入时触发输入标志
	char temphz[5][3]={{'\0','\0','\0'},{'\0','\0','\0'},
	                   {'\0','\0','\0'},{'\0','\0','\0'},
					   {'\0','\0','\0'}},temp[3];//存了5个长度为3个字符的字符串，用于储存汉字
	int fposition=0;//条形框的位起点位置，拼音文件里面的位置 
	int hznow=0,hznum=0;//记录当前汉字的位置 
	int asc,i;
	int PyStartx=x+8,PyStarty=y+4;
	int HzStartx=x+8,HzStarty=y+22;
	char *ABpath="pinyin\\";//汉语拼音检索标准路径，当前路径下的pinyin文件 
	char pypath[45];					//汉语拼音检索相对路径
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	strcpy(pypath,"pinyin\\");//将文件路径交给pypath 
	while(1)
	{
		if(trigger||kbhit())//第一次进入自动触发 以后均需键盘
		{
			clrmous(MouseX,MouseY);
			trigger=0;//进入未触发状态 
			if(kbhit()) value=bioskey(0);//有键盘输入，录入value 
			asc=value&0xff;
			/*特殊按键处理*/
			switch(value)
			{
				case ESC:
					return 4;//其他处理 
				case BACK://退格键 
					p--;
					*p='\0';//删除一个已经输入的符号 
					if(py[0]=='\0')//如果删除完了，退出输入 
					{
						if(oldfp) fclose(oldfp);
						if(fp) fclose(fp);
						return 3;
					}
					break;
				case SPACE://空格键 输入汉字 
					strcpy(str,temphz[hznow]);//将现在位置的汉字字符串给到str等待输出 
					if(oldfp) fclose(oldfp);
					if(fp) fclose(fp);
					return 1;
				case ENTER://完成输入，打印到屏幕上 
					if(oldfp) fclose(oldfp);
					if(fp) fclose(fp);//关闭已经打开的文件 
					return 2;
				case LASTLINE://按下键 
					if(fposition>=8)//接下来重定位文件指针前八个字节（移动四个汉字） ，四个汉字占据一个页面 
					{
						fposition-=8;
					}
					break;
				case NEXTLINE:
					if(!feof(fp))//接下来重定位文件指针后八个字节（四个汉字）
					{
						fposition+=8;
					}
					break;
				case LEFT://左移动一个
					if(hznow)
					{
						hznow--;
					}
					else if(fposition>=8)//需要左换页
					{
						fposition-=8;
						hznow=3;
					}
					break;
				case RIGHT:
					if(hznow<hznum-1)//同左
					{
						hznow++;
					}
					else if(!feof(fp))
					{
						fposition+=8;
						hznow=0;
					}
					break;
					/*按数字键选中输入汉字*/
				case FIRST:
					strcpy(str,temphz[0]);//选第一个，把首元素给到str用于输出 
					if(oldfp) fclose(oldfp);
					if(fp) fclose(fp);
					return 1;
				case SECOND:
					strcpy(str,temphz[1]);
					if(oldfp) fclose(oldfp);
					if(fp) fclose(fp);
					return 1;
				case THIRD:
					strcpy(str,temphz[2]);
					if(oldfp) fclose(oldfp);
					if(fp) fclose(fp);
					return 1;
				case FOURTH:
					strcpy(str,temphz[3]);
					if(oldfp) fclose(oldfp);
					if(fp) fclose(fp);
					return 1;
			}
			/*输入字符处理*/
			if(asc>31&&asc<127&&strlen(py)<MAXPY&&asc!='['&&asc!=']')    //有效输入时则复位
			{
				*p=asc;//将asc的值储存在p中 
				p++;//移动p到下一个 
				fposition=0;
				hznow=0;
			}
			pyFrm(x,y,x+200,y+40);
			setfillstyle(1,WHITE);
			settextstyle(1,0,2);
			outtextxy(PyStartx,PyStarty,py);        //拼音字体
		    strcat(pypath,py);//将pinyin文件夹路径和py字符连接 
		    strcat(pypath,".txt");//加上.TXT的后缀名 ,pypath成为完整的文件路径 
		    if(fJudge) //将当前文件指针保存 同时关闭上一个文件  为输入特殊字符准备
			{
				if(oldfp)
				{
					fclose(oldfp);
				}
				oldfp=fp;
			}
		    if((fp=fopen(pypath,"r"))==NULL)//特殊字符存在  保留上一个文件检索结果
		    {
		    	fJudge=FAIL;
		    	fp=oldfp;
			}
			else
			{
				fJudge=SUCCESS;
			}
			if(fp)//按照只读方式打开了这个txt文件 
			{
				fseek(fp,fposition,SEEK_SET);//找到指定位置的文件内容 
		  		for(i=0;i<5;i++)
		    	{
		    		fread(temphz[i],2,1,fp);//读入一个汉字，并存在temphz中 
		    		if(feof(fp))//读到文件尾
		    		{
		    			hznum=i;//按道理此处文件尾多读一次 需要减一  然而此处不减一的效果更好
		    			break;
					}
				}
				if(!feof(fp))//未读到文件尾 全显汉字
				{
					hznum=4;
				}
				for(i=0;i<hznum;i++)
				{
					setcolor(BLUE);
                    settextstyle(1,0,2);
		   		    xouttextxy(HzStartx+i*50,HzStarty+5,itostr(i+1,temp),DARKGRAY);
    				puthz(HzStartx+i*50+16,HzStarty,temphz[i],16,16,DARKGRAY);
				}
				puthz(HzStartx+hznow*50+16,HzStarty,temphz[hznow],16,16,CYAN);//显示选中汉字
			}
		}
		strcpy(pypath,ABpath);          //绝对路径复原（不可少），只停留在拼音大文件夹的层级 ，便于下次使用 
		value=0;
	}
}

/************************************************************************
FUNCTION:pyFrm
DESCRIPTION: 输入法小框
INPUT:x1,y1,x2,y2
RETURN:无
************************************************************************/

void pyFrm(int x1,int y1,int x2,int y2)
{
	setfillstyle(1,WHITE);
	bar(x1,y1,x2,y2);
	setcolor(BLUE);
	setlinestyle(0,0,1);
	line(x1+5,y1+20,x2-5,y1+20);
	setcolor(DARKGRAY);
	rectangle(x1,y1,x2,y2);
}

int xouttextxy(int x,int y,char *s,int color)//8x16点阵字库的输出 
{
	FILE *asc=NULL;
	int i,j,k;
	char *mat,*temp;
	int len;
	long offset;
	int mask;

	len=strlen(s);//记录s的长度 
	if(!len) return 0;//空字符串不执行操作
	if((asc=fopen("HZK\\ASC16","rb"))==NULL)//打开汉字库的文件 。文件指针指向头部 ；如果打开失败就报错 
	{
		closegraph();
		printf("outtextxy can't open asc16!,xouttextxy");
		delay(3000);
		exit(1);
	}
	if((mat=(char *)malloc(16*sizeof(char)*len))==NULL)//存放点阵
	{
		closegraph();
		printf("Failed!,xouttextxy");
		fclose(asc);
		getch();
		exit(1);
	}
	temp=mat;
	for(i=0;i<len;i++)
	{
		offset=(long)16*s[i];//计算字符的文件偏移
		fseek(asc,offset,SEEK_SET);
		fread(temp,sizeof(char),16,asc);//将所有字符点阵存入mat
		temp+=16;
	}
	fclose(asc);//关闭文件 
	for(i=0;i<len;i++)//通过放点显示字符
	{
		for(j=0;j<16;j++)
		{
			mask=0x80;
			for(k=0;k<8;k++)
			{
				if(mat[i*16+j]&mask)
				putpixel(x+8*i+k,y+j,color);//库里的字符打点函数 
				mask>>=1;
			}
		}
	}
	free(mat);
	return len;
}

/************************************************************************
FUNCTION:itostr
DESCRIPTION: 数字标号
INPUT:a,s
RETURN:数字s
************************************************************************/

char *itostr(int a,char *s)
{
	switch(a)
	{
		case 1:
			strcpy(s,"1.");
			return s;
		case 2:
			strcpy(s,"2.");
			return s;
		case 3:
			strcpy(s,"3.");
			return s;
		case 4:
			strcpy(s,"4.");
			return s;
	}
	return s;
}


