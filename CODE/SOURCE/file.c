#include<common.h>
#include"file.h"
char filename[40]={0};//定义全局变量filename 

/**************************
	【文件模块】
	编写人：桂熙严 
**************************/
int FreeAll(Lnode* p) //删除p及后面的行节点和节点 
{
	if (p->next) 
	Freenode(p->next);  
	if (p->nextl) 
	FreeAll(p->nextl);  
	free(p);  
	return;  
}  

int Freenode(node* p)  //删除p后节点 
{  
	if (p->next) Freenode(p->next);  
	free(p);  
	return;  
}  

	
Lnode* opens(Lnode *Hp,Lnode **startline)  //打开文件 的函数 
{  
    FILE* fp;  //文件指针 
    Lnode* q1, * q2;
    node* p1, * p2; //设置两个指针，在交换中前进 
    int temp; //temp用于接收从文件中获得的字符 
	int Hflg=0;
	int Hflg2=0; //Hflg，Hflg2用来判定是否是第一行 
    int count = 0; //count用于记录某行已经输入的字符总像素数目 
	int flags = 1;//标记列数 
	int i = 0;  
    cleardevice();//清屏
	drawmenu(); 		
	delcursor();//删除光标，准备输出提示 
	puthz(30,210,"输入一个文件名",16,16,WHITE);  
	setcolor(WHITE);
	outtextxy(140,215,"(e.g. c:\\test.c):") ;//打开文件示例 
	gettxtname(filename,280,215);//获取指定路径下的文件名称 ，在filename 数组里面储存 
	setcolor(WHITE); 
    fp = fopen(filename, "r");//以只读方式打开文件（名字为filename，filename必须要存在  
    if (fp == NULL)//打开文件失败 
    {   
	    cleardevice();  //清屏整个屏幕 
		puthz(288,232,"打开失败", 16, 16,WHITE);
	    getch(); //等待用户输入字符 
	    drawmenu();//重新画图 
	    return Hp;  //返回第一行指针 
    }  
   else
    {  
	    FreeAll(Hp->nextl);  //释放空间，准备把文件读入链表 ，这里传入了Hp的下一行 ,
	    Hp->next = NULL;  //手动消除第一行，防止第一行头结点消失 
	    Hp->nextl = NULL;  
	 
	while (!feof(fp))  //读取字符,feof（fp）文件结束返回0，反之非零  （判断文件是否结束 ，大循环 
	{  
    	count = 0; //字符计数 
		flags = 1;  
	    q2 = (Lnode*)malloc(sizeof(Lnode));//新建一个行单链表
	    p1= (node*)malloc(sizeof(node)); //新建一个列单链表中的节点
		q2->next = p1;
		p1->next=NULL; 
		q2->nextl = NULL; 
		if(Hflg==0)//这里判断是否是在读第一行，第一行操作结束后不再执行此行操作 
	    {
	    	Hp=q2;//把q2作为第一行 
	        Hflg=1;//表示已经不是第一行了 
		}
		temp = fgetc(fp); 	 //开始获得文件中的字符
		 
	    while ((temp != 10 )&& (temp != 13)&& (count <= 600) && (!feof(fp))) //行内循环，当换行时跳出 
		//若循环结束，则说明在单链表中一行处理完毕，因此开始新行  ，换行的条件 
	    {    
	        if (flags == 1) //flags==1说明在第一个节点输入     
			{ 
				if (temp == 0x09) //如果检测到tab，将其全部替换成空格 
	            {  
	            	p1->txt[0] = ' '; //从第一行第一个节点开始 
					p1->txt[1]='\0';
	 			    p1->sign=0;//记录为字符状态 
	 			    count+=8;//当做已经8个字符处理 
	                for (i = 0; i < 3; i++)  //再来3个空格 
	                {   
						p2 = (node*)malloc(sizeof(node));  //再新建一个节点 
	                	p2->txt[0] =' ';
						p2->txt[1]='\0';  
	                    p2->next = NULL;  
	                    p1->next = p2; 
						p2=p2->next; 
	                    p1 = p1->next;                     
	                    count+=8;  
	                }  
	            	temp = fgetc(fp);//读取下一个 
	            	
	            }
				else//未检测到tab键 
				{
					if((temp & 0x80)==0)//temp与0x80作与，若其值为0，表示是非中文字符 
					{
						p1->txt[0] = temp;  
				        p1->txt[1]='\0';
				        p1->sign=0;
				        p1->flag=WHITE;
			         	p1->next = NULL;  
			         	count+=8;
					}
					else if((temp & 0x80)!=0)//其值不为0，表示是中文字符 
					{
						p1->txt[0]=temp;			        						
						temp = fgetc(fp);
						p1->txt[1]=temp;
						p1->txt[2]='\0';				        												
						p1->sign=1;
			        	p1->next = NULL;  
			        	count+=16;  //一个中文字符占两个字节 
					}
					temp = fgetc(fp);//重读		
				}
				flags=0; //标记不在第一列 
			}
			else if(flags==0) //不在第一个节点输入 
	        {
		
	        	if (temp == 0x09) /*如果检测到tab，将其全部替换成空格*/  
	            {  
	            	p2 = (node*)malloc(sizeof(node));
	                for (i = 0; i < 4; i++)  //4个空格符 
	                {   
						if(i!=0) p2 = (node*)malloc(sizeof(node));  
	                	p2->txt[0] =' ';
						p2->txt[1]='\0';  
	                    p2->next = NULL;  
	                    p1->next = p2; 
						p2=p2->next; 
	                    p1 = p1->next;                     
	                    count+=8;
	                }  
	            	temp = fgetc(fp);//重置 
	            }  
	            else 
	            {
					if((temp & 0x80)==0)//temp与0x80作与，若其值为0，表示是非中文字符 
					{
						p2 = (node*)malloc(sizeof(node));
						p2->txt[0] = temp;  
				        p2->txt[1]='\0';
				        p2->sign=0;
				        p2->flag=WHITE;
			         	p2->next = NULL;  
			         	p1->next = p2; 
						p1 = p2; //来回交换，实现递推 
			         	count+=8;
					}
					else if((temp & 0x80)!=0)//其值不为0，表示是中文字符 
					{
						p2 = (node*)malloc(sizeof(node));
						p2->txt[0]=temp;			        						
						temp = fgetc(fp);
						p2->txt[1]=temp;
						p2->txt[2]='\0';				        												
						p2->sign=1;
			        	p2->next = NULL;  
			        	p1->next = p2; 
						p1 = p2;  
			        	count+=16;  //一个中文字符占两个字节 
					}
					temp = fgetc(fp);
		    	}  
	        } 
		}
		if(count==0)//空行，p1未变动 
		{
			p1->txt[0]= 13; 
			p1->sign=0;
			p1->next = NULL; 
			if(Hflg2==0)
	        {
	        	q1 = q2; 
	            Hflg2=1;
			}
			else
	        {
				q1->nextl = q2; 
				q1 = q2; //行的递推关系 
			}		 
			
		}
	    if (count > 0)  //一行结束且不是空行 ，p1这时在行尾 
	    {
	        p2 = (node*)malloc(sizeof(node)); 
			p2->txt[0]= 13; 
			p2->sign=0;
			p2->next = NULL;  
	        p1->next = p2; 
	        if(Hflg2==0)
	        {
	        	q1 = q2; 
	            Hflg2=1;
			}
			else
	        {
				q1->nextl = q2; 
				q1 = q2; //行的递推关系 
			}		 
	    }  
      }
    view(Hp);//将链表显示在可输入范围内 	
	*startline=Hp;	//startline指向这个开头 
	return Hp;
	}
}

/************************************************************************
函数：newbuild
功能：新建一个文件，通过 fp = fopen(filename, "wb+")实现
      若输入的文件已存在，将提示该文件存在，并直接打开此文件 
参数：链表Lnode*Hp 
************************************************************************/	     
int newbuild(Lnode* Hp,Lnode **startline) 
{  
    FILE* fp;  
    Lnode* q1, * q2;
    node* p1, * p2;  
    int temp;
	int Hflg=0;
	int Hflg2=0; //Hflg，Hflg2用来判定是否是第一行 
    int count = 0; 
	int flags = 1;
	int i = 0;  
    cleardevice();//清屏
	drawmenu(); 		
	delcursor();//删除光标，准备输出提示 
	puthz(30,210,"请输入您想新建文件的文件名",16,16,WHITE);  
	setcolor(WHITE);
	outtextxy(241, 215, ":");
	gettxtname(filename,250,215);
	setcolor(WHITE); 
    fp = fopen(filename, "r");//达到"若没有这个文件，则建立一个文件"的目的
if (fp == NULL)//不存在该文件 
    {   
	    cleardevice();//清屏
		drawmenu(); 		  
		setcolor(WHITE);  
    	fp = fopen(filename, "wb+");//用读写打开一个二进制文件文件		 
    }  
else//文件已经存在 ，读取 
	{  
	    cleardevice();//清屏
		drawmenu(); 		
		delcursor();//删除光标，准备输出提示 
		setcolor(WHITE);
		puthz(222,202,"新建失败",16,16,WHITE);
		puthz(222,218,"因为该文件已经存在",16,16,WHITE);
		puthz(222,234,"正在为您打开该文件",16,16,WHITE);
		puthz(222,250,"请稍候",16,16,WHITE);
		outtextxy(270,254,".");
		delay(500); 
		outtextxy(286,254,".");
		delay(500);
		outtextxy(302,254,".");
		delay(500);
		outtextxy(318,254,".");
		delay(500);//延时后显示已有文件 
	    fp = fopen(filename, "r");//以只读方式打开文件，filename必须要存在  
		FreeAll(Hp->nextl);   
		Hp->next = NULL;  
		Hp->nextl = NULL;  
	while (!feof(fp))  //读取字符,feof（fp）文件结束返回0，反之非零  （判断文件是否结束 ，大循环 
	{  
    	count = 0; //字符计数 
		flags = 1;  
	    q2 = (Lnode*)malloc(sizeof(Lnode));//新建一个行单链表
	    p1= (node*)malloc(sizeof(node)); //新建一个列单链表中的节点
		q2->next = p1;
		p1->next=NULL; 
		q2->nextl = NULL; 
		if(Hflg==0)//这里判断是否是在读第一行，第一行操作结束后不再执行此行操作 
	    {
	    	Hp=q2;//把q2作为第一行 
	        Hflg=1;//表示已经不是第一行了 
		}
		temp = fgetc(fp); 	 //开始获得文件中的字符
		 
	   while ((temp != 10 )&& (temp != 13)&& (count <= 600) && (!feof(fp))) //行内循环，当换行时跳出 
		//若循环结束，则说明在单链表中一行处理完毕，因此开始新行  ，换行的条件 
	    {    
	        if (flags == 1) //flags==1说明在第一个节点输入     
			{ 
				if (temp == 0x09) //如果检测到tab，将其全部替换成空格 
	            {  
	            	p1->txt[0] = ' '; //从第一行第一个节点开始 
					p1->txt[1]='\0';
	 			    p1->sign=0;//记录为字符状态 
	 			    count+=8;//当做已经8个字符处理 
	                for (i = 0; i < 3; i++)  //再来3个空格 
	                {   
						p2 = (node*)malloc(sizeof(node));  //再新建一个节点 
	                	p2->txt[0] =' ';
						p2->txt[1]='\0';  
	                    p2->next = NULL;  
	                    p1->next = p2; 
						p2=p2->next; 
	                    p1 = p1->next;                     
	                    count+=8;  
	                }  
	            	temp = fgetc(fp);//读取下一个 
	            	
	            }
				else//未检测到tab键 
				{
					if((temp & 0x80)==0)//temp与0x80作与，若其值为0，表示是非中文字符 
					{
						p1->txt[0] = temp;  
				        p1->txt[1]='\0';
				        p1->sign=0;
				        p1->flag=WHITE;
			         	p1->next = NULL;  
			         	count+=8;
					}
					else if((temp & 0x80)!=0)//其值不为0，表示是中文字符 
					{
						p1->txt[0]=temp;			        						
						temp = fgetc(fp);
						p1->txt[1]=temp;
						p1->txt[2]='\0';				        												
						p1->sign=1;
			        	p1->next = NULL;  
			        	count+=16;  //一个中文字符占两个字节 
					}
					temp = fgetc(fp);//重读		
				}
				flags=0; //标记不在第一列 
			}
			else if(flags==0) //不在第一个节点输入 
	        {
		
	        	if (temp == 0x09) /*如果检测到tab，将其全部替换成空格*/  
	            {  
	            	p2 = (node*)malloc(sizeof(node));
	                for (i = 0; i < 4; i++)  //4个空格符 
	                {   
						if(i!=0) p2 = (node*)malloc(sizeof(node));  
	                	p2->txt[0] =' ';
						p2->txt[1]='\0';  
	                    p2->next = NULL;  
	                    p1->next = p2; 
						p2=p2->next; 
	                    p1 = p1->next;                     
	                    count++;
	                }  
	            	temp = fgetc(fp);//重置 
	            }  
	            else 
	            {
					if((temp & 0x80)==0)//temp与0x80作与，若其值为0，表示是非中文字符 
					{
						p2 = (node*)malloc(sizeof(node));
						p2->txt[0] = temp;  
				        p2->txt[1]='\0';
				        p2->sign=0;
				        p2->flag=WHITE;
			         	p2->next = NULL;  
			         	p1->next = p2; 
						p1 = p2; //来回交换，实现递推 
			         	count+=8;
					}
					else if((temp & 0x80)!=0)//其值不为0，表示是中文字符 
					{
						p2 = (node*)malloc(sizeof(node));
						p2->txt[0]=temp;			        						
						temp = fgetc(fp);
						p2->txt[1]=temp;
						p2->txt[2]='\0';				        												
						p2->sign=1;
			        	p2->next = NULL;  
			        	p1->next = p2; 
						p1 = p2;  
			        	count+=16;  //一个中文字符占两个字节 
					}
					temp = fgetc(fp);
		    	}  
	        } 
		}
		if(count==0)//空行，p1未变动 
		{
			p1->txt[0]= 13; 
			p1->sign=0;
			p1->next = NULL; 
			if(Hflg2==0)
	        {
	        	q1 = q2; 
	            Hflg2=1;
			}
			else
	        {
				q1->nextl = q2; 
				q1 = q2; //行的递推关系 
			}		 
		}
	    if (count > 0)  //一行结束且不是空行 ，p1这时在行尾 
	    {
	        p2 = (node*)malloc(sizeof(node)); 
			p2->txt[0]= 13; 
			p2->sign=0;
			p2->next = NULL;  
	        p1->next = p2; 
	        if(Hflg2==0)
	        {
	        	q1 = q2; 
	            Hflg2=1;
			}
			else
	        {
				q1->nextl = q2; 
				q1 = q2; //行的递推关系 
			}
				 
	    }  
	    
	}
	 view(Hp);//将链表显示在可输入范围内 	
	*startline=Hp;	//startline指向这个开头 
  }
}
/************************************************************************
函数：save 
功能：将修改的字符保存进链表（即修改链表）以达到保存文件的目的 
参数：链表Lnode*Hp 
************************************************************************/
int save(Lnode* Hp)  
{ 
	FILE* fp;  
	Lnode* q;  
	node* p;
	q=Hp;//第一行 
	fp = fopen(filename, "w");//以只写方式打开已经存在filename 的文件 
	if (fp == NULL)//打开文件失败 （文件还未新建 ，filename没东西 
    {   
	    cleardevice();  
		puthz(288,232,"打开失败", 16, 16,WHITE);//这里仅有filename不存在或者错误才会报错 
	    getch(); 
	    drawmenu();
	    return 0;  
    }
	do //如果filename有东西 
	{
	    p = q->next; //指向node类型的数据
	    while (p != NULL)  
	    {  
	    	
	    	if(p->sign==0)
	        {
	        	if(p->txt[0]==13||p==NULL)
	        		fputc('\n', fp);//换行符的输出 
	        	else
	       	    	fprintf(fp,"%c",p->txt[0]) ;//利用fprint写入文件中 
	      	      
	   		}
	   		else if(p->sign==1)//汉字情况 
	   		{
	   			fprintf(fp,"%c",p->txt[0]) ;
	      	    fprintf(fp,"%c",p->txt[1]) ;//写入两个字符 
			}
			p = p->next; //下一个 
			fflush(fp);//清空缓冲区，将缓冲区内容写入文件 确保后续读入不被影响 
	    } 
		
	    q = q->nextl;  //一行写完了 
	} while (q!=NULL);  

	fclose(fp); //关闭此文件
	view(Hp);
 
    return; 

}

 //另存为功能 
int saveas(Lnode* Hp)  
{  
    FILE* fp;  
	Lnode* q;  
	node* p;  
	char newname[15];//文件名 
	setfillstyle(1, BLUE); 
	bar(17,25,623,455);
	puthz(30,210,"请输入您想另存为文件的文件名",16,16,WHITE);  
	setcolor(WHITE);
	outtextxy(255, 215, ":");
	gettxtname(newname,265,215); 
	q=Hp;
	//通过键盘修改链表 
	fp = fopen(newname, "w");//以只写方式打开文件 ，存在文件则清空再写入，不存在则创建后写入 
	if (fp == NULL)//打开文件失败 ，newname 不存在 
    {   
	    cleardevice();  
		puthz(288,232,"打开失败", 16, 16,WHITE);
	    getch(); 
	    drawmenu();
	    return 0;  
    }
	do //写入此文件中 
	{
	    p = q->next; 
	    while (p != NULL)  
	    {  
	    	
	    	if(p->sign==0)
	        {
	        	if(p->txt[0]==13)
	        		fputc('\n', fp);//用文件指针定位文件 
	        	else
	       	    	fprintf(fp,"%c",p->txt[0]) ;
	      	      
	   		}
	   		else if(p->sign==1)
	   		{
	   			fprintf(fp,"%c",p->txt[0]) ;
	      	    fprintf(fp,"%c",p->txt[1]) ;
	      	    
			}
			p = p->next; 
			fflush(fp);
	    } 
		
	    q = q->nextl;  
	} while (q!=NULL);  
	fclose(fp); //关闭此文件
	view(Hp);
    return; 
}  

