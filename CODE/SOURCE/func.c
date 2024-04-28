#include<common.h>
#include"func.h" 

/************************************
		【编辑功能模块】
		编写人：桂熙严 
 find用于查找并标记显示
 replace用于替换字符串 
 ctrlr，turnp用于处理选定字符的工作
  highlight，changecolor，changeflag一起处理关键字代码高亮 
************************************/ 

//作用：查找并标记特定的字符串 ,一行中可以多次出现 
void find(Lnode*startline)
{
	int i,j,k,slen,r=1,c=1;
	char row[80];//用于储存读每一行取到的字符串 
	char *str,*s0,*s1;
	Lnode *q;
	node *p1;
	q=startline;
	str=(char*)malloc(10);//分配10个字符长度 ,用于临时储存要查找的字符串 
	setfillstyle(1, BLUE); 
	bar(17,25,623,455);//字符区域呈蓝色
	 puthz(150,200,"请输入要查找的字符串：", 16, 16,WHITE);
	slen=gettxtname(str,326,206)-1;//记录字符串长度 ，并读取给到str 
	view(startline); 
	for(i=1;(q!=NULL)&&(i<=27);i++)//循环检测每行 在一个页面内 
	{
		c=1;
		j=0;
		p1=q->next;
	    while(p1!=NULL&&p1->txt[0]!=13)
	    {
	         if(p1->sign==0)
	        {
			    row[j]=p1->txt[0];
			    j++;
	       	}
	         else {
	         	row[j]=p1->txt[0];
	         	j++;
	         	row[j]=p1->txt[1];
	         	j++;
			 }
			p1=p1->next;
	    }
	    row[j]='\0';
		//查找数组里是否有匹配的字符串 
		s0=row;//把row地址给到s0； 
		//查找输入的字符串，s0不断改变位置指向特定字符后一位，s1指向特定字符串，利用colorvie标记显示查找的字符串； 
        //看str是否是s0的子字符串 ,返回str第一次出现的位置 
        	do
		{
			s1=strstr(s0,str);
			c=c+(s1-s0);
			if(s1!=NULL) 
			for(k=0;k<slen;k++)
			{
				colorview(r,c,startline);
				c++;
			}
			s0=s1+slen;
			
		}while(s1!=NULL);
		memset(row,'\0',sizeof(row)) ;//清零row 
		r++;
		q=q->nextl;
   } 
   free(str); 
}
//作用：查找并替换特定字符串 
void replace(Lnode* startline) 
{
	int i,j,k,alen,blen,c=1,r=1;
	char row[80];
	char *astr,*s0,*s1,*s2,*bstr,temp[2];//astr为原来的字符，bstr为现在的字符 
	Lnode *q;
	node *p1;
	q=startline;
	astr=(char*)malloc(10);//原来的 
	bstr=(char*)malloc(76);//现在的 
	setfillstyle(1, BLUE); 
	bar(17,25,623,455);//字符区域呈蓝色 
	puthz(150,200,"输入要替换的字符串：", 16, 16,WHITE);	
	alen=gettxtname(astr,326,206)-1;//记录字符串长度 
	bar(17,25,623,455);
	puthz(150,200,"输入新的字符串：", 16, 16,WHITE);
	blen=gettxtname(bstr,278,206)-1;//记录字符串长度
	view(startline); 
	for(i=1;(q!=NULL)&&(i<=27);i++)//循环检测每行 
	{
		c=1;
		p1=q->next;
		for(j=0;p1!=NULL&&p1->txt[0]!=13;j++) //循环将链表数据读入数组
		{
			if(p1->sign==1)//如果遇到汉字存两位使列相配 
			{
				row[j]=p1->txt[0];
				j++;
				row[j]=p1->txt[1];
			 } 
			row[j]=p1->txt[0];
			p1=p1->next;	
		} 
		row[j]='\0';
		//查找数组里是否有匹配的字符串 
		s0=row;
		do
		{
			s1=strstr(s0,astr);//这里由于一次会删除，故不用对s0操作 
			if(s1!=NULL) 
			{
				c=s1-s0+alen+1;
				movecursor(c+1,r);
				for(k=0;k<alen;k++)//这个for用于执行删除原来的字符 ,长度为alen 
				{
					deltext(startline,r,c);
					c--;
				}
				s2=s1+alen;
				strcpy(s1,s2);//执行字符串上的修改 在row 里面删除原字符串 
				for(k=0;k<blen;k++)//这个用于执行插入行的字符串 
				{
					temp[0]=bstr[k];//为了适配insert传入一个数组的要求 
					temp[1]='\0';
					insert(temp,r,c,startline);//这里c在s1位置处 
					c++;
				} 
				//在数组层面实现插入
				 
				strcat(bstr,s1);//s1接在bstr后面 
				
				strcpy(s1,bstr);//把bstr中的字符填到s1位置 
				//于是实现了在中间插入 
				
				bstr[blen]='\0';
		    }
		    else          break;
		   
		}while(s1!=NULL);
		r++;
		q=q->nextl;
	}
	free(astr);
	free(bstr);
	view(startline);
}

//作用：光标向右选中一个字符 ，并录入 
int ctrlr(int rcdlen,Lnode* startline,char *rcd,int m,int n)
{
	int i;
	Lnode* q1;//此指针为指向一行数据的指针 
	node*p1;//此指针为指向一个数据节点的指针 
	q1=startline;//q1指向当前显示区域的第一行 
	for(i=1;i<m;i++)
		q1=q1->nextl;//循环使得q1移动到第m行 
	p1=q1->next;//p1指向第m行的第一列 
	for(i=1;i<n;i++)//循环到第n列
		{
			if(p1->sign==1)	i++;//如果遇到汉字，检测的列后移一位 (因为汉字占两列 
			p1=p1->next;
		}
	if(p1->sign==0)
	{
	rcd[rcdlen]=p1->txt[0];//rcdlen记录已经有的字符长度 
	rcd[rcdlen+1]='\0';//暂时将这个字符作为结尾 
	return 0; 
     }  
     else //汉字 
	 {
	 rcd[rcdlen]=p1->txt[0];
	rcd[rcdlen+1]=p1->txt[1];
	rcd[rcdlen+2]='\0';
	return 1;
   }  
 } 
 
 //作用：实现粘贴功能
 void paste(int m,int n,Lnode*startline,int rcdlen,int rcdflg,char*rcd) 
 {
 	int i,j,count=0;//标志列的位置以及字符数目 
 	char bioget[3];
	Lnode* q1,*q2;//此指针为指向行的指针 
	node*p1,*p2,*p3;//此指针为指向一个数据节点的指针 
	q1=startline;//q1指向当前显示区域的第一行 
	for(i=1;i<m;i++)
		q1=q1->nextl;//循环使得q1移动到第m行 
	p1=q1->next;//p1指向第m行的第一列 
	for(i=1;i<n-1;i++)//循环到第n-1列,指针已经到光标位置
		{
			p1=p1->next; 
			if(p1->sign==1)	i++;	//如果遇到汉字，检测的列后移一位 (因为汉字占两列 ），需要在2个字符位置处进行插入 
		}//p1在光标开始位置 
		p3=p1; 
 	if(rcdflg==1) //如果剪贴板有内容
	{
		for(i=0;i<rcdlen;i++)
		{
			  if((rcd[i]&0x80)==0)//英文字符
			  {
			  	bioget[0]=rcd[i];
			  	bioget[1]='\0';
			  	insert(bioget,((cursorY-24)/16+1),((cursorX-16)/8+1),startline) ;
			  	count++;
			  	memset(bioget,'\0',sizeof(bioget));
			   } 
			   
			 else//中文
			{
			 	p1=p3;
			 	
			  if(p1==NULL&&q1->next!=NULL) 
			  {
			     p1=q1->next;
			     for(j=1;j<count;j++)
			 	{
			 		p1=p1->next;
				 }//移动 
				 
			  bioget[0]=rcd[i];
			 	i+=1;
			 	bioget[1]=rcd[i];
			 	bioget[2]='\0' ;
			 	
				 p2=(node*)malloc(sizeof(node));
				 p1->next=p2;
				 p2->sign=1;
				 p2->txt[0] =bioget[0];
				 p2->txt[1]=bioget[1];
				 p2->txt[2] ='\0';
				 p2->next=NULL; 
				 
				 count++;
			 	setcolor(WHITE);
			 	clrmous(MouseX,MouseY);
			 	puthz(cursorX,cursorY,bioget,16, 16,WHITE);
			 	delcursor();
			 	cursorX+=16;
			 	save_bk_mou(MouseX,MouseY); 
	            drawmous(MouseX,MouseY);
	            memset(bioget,'\0',sizeof(bioget));
			  
		      }
		      
			  else if(p1==NULL&&q1->next==NULL)//汉一行字起手 
			  {
			  	p1=(node*)malloc(sizeof(node));
			  	q1->next=p1;
			  	p1->next=NULL; 
			  	bioget[0]=rcd[i];
			 	i+=1;
			 	bioget[1]=rcd[i];
			 	bioget[2]='\0' ;
			  	 p1->sign=1;
				 p1->txt[0] =bioget[0];
				 p1->txt[1]=bioget[1];
				 p1->txt[2] ='\0';
				 count++;
			 	setcolor(WHITE);
			 	clrmous(MouseX,MouseY);
			 	cursorX=17;
			 	puthz(cursorX,cursorY,bioget,16, 16,WHITE);
			 	delcursor();
			 	cursorX+=16;
			 	save_bk_mou(MouseX,MouseY); 
	            drawmous(MouseX,MouseY);
	            memset(bioget,'\0',sizeof(bioget)); 
			  }
			  
			  else if(p1!=NULL)
			  {

			  	for(j=1;j<count;j++)
			 	{
			 		p1=p1->next;
				 }//移动 
				 
			 	bioget[0]=rcd[i];
			 	i+=1;
			 	bioget[1]=rcd[i];
			 	bioget[2]='\0' ;
			 	
				 p2=(node*)malloc(sizeof(node));
				 p1->next=p2;
				 p2->sign=1;
				 p2->txt[0] =bioget[0];
				 p2->txt[1]=bioget[1];
				 p2->txt[2] ='\0';
				 p2->next=NULL; 
				 
				 count++;
			 	setcolor(WHITE);
			 	clrmous(MouseX,MouseY);
			 	puthz(cursorX,cursorY,bioget,16, 16,WHITE);
			 	delcursor();
			 	cursorX+=16;
			 	save_bk_mou(MouseX,MouseY); 
	            drawmous(MouseX,MouseY);
	            memset(bioget,'\0',sizeof(bioget)); 
			  }
			 	
			} 
		}
		
			memset(rcd,'\0',10);
	}
 }
 
 
int colorview(int m,int n,Lnode* startline)
{
	int i=0;
	Lnode* q1;
	node* p1;
	q1=startline;
	for(i=1;i<m;i++)
		q1=q1->nextl;//循环使得q1移动到第m行 
	p1=q1->next; 
	for(i=0;i<n-1;i++)
	{
		if(p1->sign==1)
		i++;
		p1=p1->next;
	}//到达指定字符位置 
if(p1!=NULL)
{
   if(p1->sign==0) //如果是英文字符 
   {
	delcursor();
	clrmous(MouseX,MouseY);
	setfillstyle(1,LIGHTGRAY);
	bar(17+8*(n-1),25+16*(m-1),24+8*(n-1),40+16*(m-1));//变成灰色底部 
	settextstyle(0,0,1);
	setcolor(WHITE);
	p1->txt[1]='\0';
	outtextxy(17+8*(n-1),31+16*(m-1),p1->txt);//重新打印字符 
	imgflag=0;
	save_bk_mou(MouseX,MouseY); 
	drawmous(MouseX,MouseY);
	newcursor();
  }
  else //如果遇到中文字符 
  {
  	delcursor();
	clrmous(MouseX,MouseY);
	setfillstyle(1,LIGHTGRAY);
	bar(17+8*(n-1),25+16*(m-1),34+8*(n-1),40+16*(m-1));//变成灰色底部 
	setcolor(WHITE);
	puthz(17+8*(n-1),25+16*(m-1),p1->txt,16, 16,WHITE); 
	imgflag=0;
	save_bk_mou(MouseX,MouseY); 
	drawmous(MouseX,MouseY);
	newcursor();
  }
}
else if(p1==NULL)//到了末尾 
{
    delcursor();
	clrmous(MouseX,MouseY);
	imgflag=0;
	save_bk_mou(MouseX,MouseY); 
	drawmous(MouseX,MouseY);
	newcursor();
}
}

 

//用于执行循环检测高亮 
int highlight(Lnode *startline)
{	//定义保留字 
	static char* c[32]={"long","short","float","double","char",
	"unsigned","signed","const","void","volatile","enum",
	"struct","union","if","else","goto","switch","case",
	"do","while","for","continue","break","return","default",
	"typedef","auto","register","extern","static","sizeof","int",};
	static int clen[32]={4,5,5,6,4,8,6,5,4,8,4,6,5,2,4,4,6,4,2,5,3,8,5,6,7,7,4,8,6,6,6,3};//记录所有保留字符的长度 
	int i,sig;
	for(i=0;i<32;i++)
		sig=changecolor(c[i],clen[i],startline);//循环查找所有的保留字 
	return sig;
}


//用于查找并改变字符串的颜色 
int changecolor(char* str,int slen,Lnode *startline)
{
	int i,j,k,c=1,r=1,sig=1;
	char row[80];
	char *s0,*s1,ch1,ch2;//ch1,ch2用于记录保留字前面和后面的字符判断保留字是否单独出现 
	Lnode *q;
	node *p1;
	q=startline;
	for(i=1;(q!=NULL)&&(i<=27);i++)//循环检测每行 
	{
		c=1;
		p1=q->next;
		for(j=0;p1!=NULL;j++) //循环将链表数据读入数组
		{
			if(p1->sign==1)//如果遇到汉字存两位使列相配 
			{
				row[j]=p1->txt[0];
				j++;
				row[j]=p1->txt[1];
			 } 
			row[j]=p1->txt[0];
			p1=p1->next;	
		} 
		row[j]='\0';
		//查找数组里是否有匹配的字符串 
		s0=row;
		//查找固定的字符串，s0不断改变位置指向特定字符后一位，s1指向特定字符串 
		do
		{
			s1=strstr(s0,str);
			c=c+(s1-s0);
			if(s1!=NULL) //如果查找到
			{ 
				ch1=*(s1-1);//前一个字符 
				ch2=*(s1+slen);//后一个字符 
				//看保留字是否单独出现 
				if(!((ch1>='0'&&ch1<='9')||(ch1>='A'&&ch2<='Z')||(ch1>='a'&&ch1<='z')||(ch1=='_')||
				(ch2>='0'&&ch2<='9')||(ch2>='A'&&ch2<='Z')||(ch2>='a'&&ch2<='z')||(ch2=='_')))//如果前面或者后面没有字符或者只有空格 
				{
					for(k=0;k<slen;k++)
					{
						changeflag(r,c,startline,YELLOW);
						c++;//实现代码高亮 
					}
					sig=0;//表示已经处理 
				}
				else
				{
					for(k=0;k<slen;k++)
					{
						changeflag(r,c,startline,WHITE);
						c++;//否则 变为白色 
					}
					sig=0;
				}
			} 
			s0=s1+slen;//再检查一遍 
			
		}while(s1!=NULL);
		r++;
		q=q->nextl;
	}
	return sig;//返回标记，0表示已经处理 高亮 
}	

//作用：改变m行n列的颜色	  
int changeflag(int m,int n,Lnode *startline,int color)
{
	int i,j;
	Lnode* q1;//此指针为指向一行数据的指针 
	node*p1;//此指针为指向一个数据节点的指针 
	q1=startline;//q1指向当前显示区域的第一行 
	for(i=1;i<m;i++)
		q1=q1->nextl;//循环使得q1移动到第m行 
	p1=q1->next;//p1指向第m行的第一列 
	for(i=1;i<n;i++)//循环到第n列
	{
		p1=p1->next;
		if(p1->sign==1)	i++;	//如果遇到汉字，检测的列后移一位 (因为汉字占两列 
	}
	p1->flag=color;
 } 

