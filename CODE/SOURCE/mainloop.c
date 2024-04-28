#include<common.h>
#include "mainloop.h"
/*************************************
【主循环函数】
编写人：贾沫晗
 mainloop为主循环函数
chosedit响应点击编辑菜单栏后的操作 
chosfile响应点击文件菜单栏后的操作 
choshelp响应点击帮助菜单栏后的操作 
**************************************/
char rcd[80];//用于存放剪贴板的内容
int rcdlen=0;//用于储存剪贴板的长度 
int rcdflg=0; //用于指示剪贴板是否已经剪切 
int grey=0;//记录是否有灰色部分（用于处理查找的 
//主循环函数 
void mainloop()
{
	//初始化变量 ，链表 
	int ch,row=1,column=1,o,i=0,mx,my,j,sig;
	char a;
	char bioget[2];//用于存放当前的键值 
	void *bitmap2;//用于存放鼠标右键菜单遮挡住的的图像
	node* p1,p2;
	Lnode* Head, * q, *startline, * temp;//用于储存行链表的头指针
	Head=(Lnode*)malloc(sizeof(Lnode));//为行单链表首节点分配空间 
	q=Head;	Head->nextl=NULL;	
	q->next=NULL;
	startline=Head;
	drawmenu();
	full_skbar();
	//主循环 
	while(1)
	{
		newmouse(&MouseX, &MouseY, &press);
		memset(bioget,'\0',2);
		row=(cursorY-24)/16+1;
		column=(cursorX-16)/8+1;
		drawrc(row+countdown,column);
		newcursor();//如果还没有储存光标的图像，就储存，防止光标掩盖屏幕内容
		//判断鼠标点击 
		if(mouse_press(9,25,615,455)==1)//如果鼠标点击屏幕位置，移动光标到鼠标的位置 
		{
			if((rcdlen!=0)&&(rcdflg==0))//如果剪贴板有内容，但是没有复制或者剪切，就清空剪贴板
			{
				rcdlen=0;
				view(startline);
			}
			if (grey==1) //如果有颜色部分
			{
				grey=0;
				view(startline) ;//消除颜色 
			 } 
			i= checktxt(((MouseX-16)/8+1),((MouseY-24)/16+1),startline);
			if(i==1)//如果返回值是1,即这一行存在并且这个位置有字符，就移动光标到字符位置 
			{
				clrmous(MouseX,MouseY);
				delcursor();
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);
				cursorX=(MouseX-16)/8*8+17;
				cursorY=(MouseY-24)/16*16+25;
				imgflag=0;
			}
			else if(i==2)//如果返回值是2，即这一行存在但是这个位置没有字符，就移动光标到这一行最后一个位置 
			{
				q=startline;
				for(j=1;j<((MouseY-24)/16+1);j++)
					q=q->nextl;
				clrmous(MouseX,MouseY);	
				movecursor(getlinelen(q)+1,((MouseY-24)/16+1));				
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);
				imgflag = 0;
			}
			delay(100);
		}
		else if(mouse_press(9,25,615,455)==3)//右键点击 
		{
			bitmap2=malloc(imagesize(1,1,64,52));
			
			if(MouseX>17&&MouseX<=304&&MouseY>25&&MouseY<=216)//左上角 
			{
				mx=MouseX;
				my=MouseY;
				clrmous(MouseX,MouseY);
				getimage(mx,my,mx+63,my+51,bitmap2);
				drawwin(mx,my);
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);
			}
			else if(MouseX>304&&MouseX<624&&MouseY>25&&MouseY<=216)//右上角 
			{
				mx=MouseX-63;
				my=MouseY;
				clrmous(MouseX,MouseY);
				getimage(mx,my,mx+63,my+51,bitmap2);
				drawwin(mx,my);
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);
			}
			else if(MouseX>17&&MouseX<=304&&MouseY>216&&MouseY<456)//左下角 
			{
				mx=MouseX;
				my=MouseY-51;
				clrmous(MouseX,MouseY);
				getimage(mx,my,mx+63,my+51,bitmap2);
				drawwin(mx,my);
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);
			}
			else if(MouseX>304&&MouseX<624&&MouseY>216&&MouseY<456)//右下角 
			{
				mx=MouseX-63;
				my=MouseY-51;
				clrmous(MouseX,MouseY);
				getimage(mx,my,mx+63,my+51,bitmap2);
				drawwin(mx,my);
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);
			}
			while(1)
			{
				newmouse(&MouseX,&MouseY,&press);
				if(mouse_press(mx,my,mx+63,my+17)==1)//点击复制
				{
					putimage(mx,my,bitmap2,0);
					free(bitmap2);
					delcursor();
					view(startline);
					rcdflg=1;
					imgflag=0;
					delay(100); 
					break;
				} 
				else if(mouse_press(mx,my+18,mx+63,my+34)==1)//点击剪切 
				{
				 	putimage(mx,my,bitmap2,0);
					free(bitmap2);
					for(i=0;i<rcdlen;i++)
					{
						deltext(startline,((cursorY-24)/16+1),((cursorX-16)/8+1));
					}
					view(startline);
					rcdflg=1;
					delay(100);
					break;
				}
				else if(mouse_press(mx,my+35,mx+63,my+63)==1)//点击粘贴 
				{
					putimage(mx,my,bitmap2,0);
					free(bitmap2);
				 	if(rcdflg==1) //如果剪贴板有内容
					{
					paste(((cursorY-24)/16+1),((cursorX-16)/8+1),startline,rcdlen,rcdflg,rcd);
					view(startline); 
					rcdlen=0;
					delay(100);	
					sig=1;
					break;
				   }
				   else break; 
				}
				else if((mouse_press(17,25,mx-1,my+51)==1)||(mouse_press(mx-1,25,624,my)==1)
				||(mouse_press(17,my+52,mx+64,456)==1)||(mouse_press(mx+64,my,624,456)==1))//点击其他区域 
				{
					clrmous(MouseX,MouseY);
					putimage(mx,my,bitmap2,0);
					save_bk_mou(MouseX,MouseY); 
					drawmous(MouseX,MouseY);
					free(bitmap2);
					delay(100);
					break;
				}
				else if ((mouse_press(17, 25, mx - 1, my + 51) == 3) 
                || (mouse_press(mx - 1, 25, 624, my) == 3)
                || (mouse_press(17, my + 52, mx + 64, 456) == 3) 
                || (mouse_press(mx + 64, my, 624, 456) == 3))//右键点击其他区域
                {
                clrmous(MouseX, MouseY);
                putimage(mx, my, bitmap2, 0);
                save_bk_mou(MouseX, MouseY);
                drawmous(MouseX, MouseY);
                free(bitmap2);
                delay(100);
                bitmap2 = malloc(imagesize(1, 1, 64, 52));

                if (MouseX > 17 && MouseX <= 304 && MouseY > 25 && MouseY <= 216)//左上角 
                {
                    mx = MouseX;
                    my = MouseY;
                    clrmous(MouseX, MouseY);
                    getimage(mx, my, mx + 63, my + 51, bitmap2);
                    drawwin(mx, my);
                    save_bk_mou(MouseX, MouseY);
                    drawmous(MouseX, MouseY);
                }
                else if (MouseX > 304 && MouseX < 624 && MouseY>25 && MouseY <= 216)//右上角 
                {
                    mx = MouseX - 63;
                    my = MouseY;
                    clrmous(MouseX, MouseY);
                    getimage(mx, my, mx + 63, my + 51, bitmap2);
                    drawwin(mx, my);
                    save_bk_mou(MouseX, MouseY);
                    drawmous(MouseX, MouseY);
                }
                else if (MouseX > 17 && MouseX <= 304 && MouseY > 216 && MouseY < 456)//左下角 
                {
                    mx = MouseX;
                    my = MouseY - 51;
                    clrmous(MouseX, MouseY);
                    getimage(mx, my, mx + 63, my + 51, bitmap2);
                    drawwin(mx, my);
                    save_bk_mou(MouseX, MouseY);
                    drawmous(MouseX, MouseY);
                }
                else if (MouseX > 304 && MouseX < 624 && MouseY>216 && MouseY < 456)//右下角 
                {
                    mx = MouseX - 63;
                    my = MouseY - 51;
                    clrmous(MouseX, MouseY);
                    getimage(mx, my, mx + 63, my + 51, bitmap2);
                    drawwin(mx, my);
                    save_bk_mou(MouseX, MouseY);
                    drawmous(MouseX, MouseY);
                }
                 }	
			}
		}
		
		else if(mouse_press(616,25,640,40)==1)//点击上移按钮
		{
			up_page(Head,&startline);
			view(startline);
			delay(100);
		}
		else if(mouse_press(616,440,640,456)==1)//点击下移按钮
		{
			down_page(Head,&startline);
			view(startline);
			delay(100);
		}
		else if(mouse_press(616,40,639,440)==1)//点击拖动条
		{
			click_skbar(Head,&startline);
			view(startline);
			delay(100);
		}
		else if(mouse_press(616,0,640,24)==1)//点击关闭按钮结束程序 
		{
			closegraph(); 
			exit(0);
		}
		else if(mouse_press(97,1,177,24)==1)//点击文件按钮 
		{
			delcursor();
			delay(100);
			chosfile(&Head,&startline);
			highlight(startline);
			view(startline);
		}
		else if(mouse_press(274,1,354,24)==1)//点击编辑按钮 
		{
			delcursor();
			delay(100);
			chosedit(startline,bioget,rcd);  
		}
		else if(mouse_press(451,1,531,24)==1)//点击帮助按钮 
		{
			delcursor();
			delay(100);
			choshelp(Head);
			view(startline);
			imgflag=0;
		}
		else if (mouse_press(177, 1, 274, 24)==1)
		{
				delcursor();
				delay(100);
				choscompile(Head);
			}
			else if (mouse_press(354, 1, 451, 24) == 1)
			{
				delcursor();
				delay(100);
				chosview(Head);
			}
		//处理键盘输入事件	
		if (bioskey(1))//检测键盘输入 
		{
			a=ch=bioskey(0);//获取键入的键值 
			if(ch==0x4B00&&cursorX>=17)//光标左移 
			{
				if(cursorX!=17)
				{
					delcursor();
					cursorX-=8;
					imgflag=0;
				}
				else
				{
					if (((cursorY - 24) / 16) != 0)
					{
						q=startline;
						for(j=1;j<((cursorY-24)/16);j++)
							q=q->nextl;
						delcursor();
						movecursor(getlinelen(q) + 1, ((cursorY - 24) / 16));
						imgflag = 0;
					}
					
				}
			}
			else if(ch==0x4800&&cursorY>25)//光标上移 
			{
				i= checktxt(((cursorX-16)/8+1),((cursorY-24)/16),startline);
				if(i==1)//如果返回值是1，就移动光标 到上一行该位置 
				{
					delcursor();
					cursorY-=16;
					imgflag=0;
					newcursor();
				}
				else if(i==2)//如果返回值是2，移动光标到上一行最后一个位置 
				{
					q=startline;
					for(j=1;j<((cursorY-24)/16);j++)
						q=q->nextl;
					delcursor();
					movecursor(getlinelen(q)+1,((cursorY-24)/16));
					imgflag=0;
					newcursor();
				}	
			}
			else if(ch==0x4d00&&cursorX<616)//光标右移 
			{
				i= checktxt(((cursorX-16)/8+2),((cursorY-24)/16+1),startline);//检测下一个位置是否有值 
				if(i==1)//如果返回值1，右移光标 
				{
					delcursor();
					cursorX+=8;
					imgflag=0;
				}
				else if(i==2)//如果返回值2，且有下一行移动到下一行第一个位置 
				{
					q=startline;
					for(j=1;j<((cursorY-24)/16+2);j++)
						q=q->nextl;
					if(q!=NULL) 
						movecursor(1,((cursorY-24)/16+2));
					
						
				}
			}
			else if(ch==0x5000&&cursorY<440)//光标下移 
			{
				i= checktxt(((cursorX-17)/8+1),((cursorY-24)/16+2),startline);
				if(i==1)//如果返回值是1，就移动光标 到下一行该位置 
				{
					delcursor();
					cursorY+=16;
					imgflag=0;
					newcursor();
				}
				else if(i==2)//如果返回值是2，移动光标到下一行最后一个位置 
				{
					q=startline;
					for(j=1;j<((cursorY-24)/16+2);j++)
						q=q->nextl;
					delcursor();
					movecursor(getlinelen(q)+1,((cursorY-24)/16+2));
					imgflag=0;
					newcursor();
					
				}
			}
			else if(ch==F4)//按F4键进入汉语输入模式 
			{
				delcursor();
				while(1)
				{
					i=hz_put(cursorX,cursorY,((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
					if(i==1)
					{
					break;
					}
					cursorX+=16;
				}
				settextstyle(0,0,1);
				imgflag=0;
				newcursor();
			}
			else if(ch==F1)//按F1键打开文件菜单 
			{
				chosfile(&Head, &startline);
				highlight(startline);
				view(startline);
			}
			else if(ch==F2)//按F2键打开编辑菜单 
			{
				chosedit(startline,bioget,rcd);
			}
			else if(ch==F3)//按F3键打开帮助菜单 
			{
				delcursor();
				choshelp(Head);
				view(startline);
				imgflag=0;
			}
			else if(ch==F10)//按F10键刷新链表 
			{
				highlight(startline);
				view(startline);
			}
			else if(ch==0x1C0D)//回车键 
			{
				enter(((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
			} 
			else if(ch==CR)//用ctrl+加右移键选中文本 
			{
				int i ;
				Lnode* q1;
				node* p1;
				q1 = startline;
				for (i = 1; i < row; i++)
					q1 = q1->nextl;//循环使得q1移动到第m行 
				p1 = q1->next;//p1指向第m行的第一列
				for (i = 1; i < column; i++)
				{
					p1 = p1->next;
				}
				if(p1!=NULL) 
				{
					colorview(((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
					i=ctrlr(rcdlen, startline, rcd, row, column);
					if(i==0) 
					rcdlen++;
					else rcdlen+=2;
					delcursor();
					if(p1->sign==0)
				    cursorX+=8;
				    else cursorX+=16; 
					imgflag = 0;
			   }
			}
			
			else if(ch==Cc)//复制键 
			{
				delcursor();
				view(startline);
				rcdflg=1;
				imgflag=0;	
			}
			else if(ch==Cx)//剪切键 
			{
				
				
				for(i=0;i<rcdlen;i++)
				{
					deltext	(startline,((cursorY-24)/16+1),((cursorX-16)/8+1));
				}
				view(startline);
				rcdflg=1;
				sig=1;
			} 
			else if(ch==Cv)//粘贴键 
			{
				if(rcdflg==1)
				{
			    paste(((cursorY-24)/16+1),((cursorX-16)/8+1),startline,rcdlen,rcdflg,rcd);
				view(startline); 
				rcdlen=0;
				sig=1;
			   }
			   else break;
			}
			else if(ch==TAB) //TAB键入4空格 
			{
				sig=1;
				bioget[0]=' ';
				for(i=0;i<4;i++)
				{
					insert(bioget,((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
				}
			}
			else if(a>=32&&a<127) //输入数字，符号 
			{
				sig=1;
				bioget[0]=a;
				insert(bioget,((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
				match(bioget,startline);//检测是否需要匹配 
			}
			else if(ch==BACK)//退格键 
			{
				sig=1;
				if(rcdlen!=0) 
				{ 
					
					for(i=0;i<rcdlen;i++)
				  	  deltext(startline,((cursorY-24)/16+1),((cursorX-16)/8+1));
				  	rcdlen=0;
				  	
				  	
				} 
				else
					deltext(startline,((cursorY-24)/16+1),((cursorX-17)/8+1));
			}
			else if(ch==DEL)//DEL键 
			{
				sig=1;
				delcursor();
				cursorX+=8;
				imgflag=0; 
				newcursor();
				deltext(startline,((cursorY-24)/16+1),((cursorX-16)/8+1));
			}
			if((highlight(startline)==0)&&(sig==1))
			{
				view(startline);
				sig=0;
			}
		}
		 
	}
	
}

//用于执行选择编辑按钮的操作 
int chosedit(Lnode* startline,char* bioget,char *rcd)
{
	int i;
	void *geti; 
	geti=malloc(imagesize(274,25,354,163));
	clrmous(MouseX,MouseY);
	getimage(274,25,354,163,geti);
    drawedit();
	save_bk_mou(MouseX,MouseY); 
	drawmous(MouseX,MouseY);
	while(1)//检测点击循环 
	{
	    newmouse(&MouseX,&MouseY,&press);
		if((mouse_press(10,24,274,456)==1)
			||(mouse_press(274,140,354,456)==1)
			||(mouse_press(354,24,624,456)==1) 
			|| (mouse_press(1, 1, 274, 24) == 1)
			|| (mouse_press(354, 1,622 , 24) == 1))//点击空白区域或者退出
		{
			clrmous(MouseX, MouseY);
			putimage(274,25,geti,0);
			free(geti);
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			break;
		}
		else if (mouse_press(274, 1, 354, 24) == 1)//点击编辑按钮
		{
			delay(100);
			clrmous(MouseX, MouseY);
			putimage(274, 25, geti, 0);
			free(geti);
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			break;
		}
		else if(mouse_press(274,25,354,48)==1)//点击复制 
		{
			putimage(274,25,geti,0);
			free(geti);
			delcursor();
			view(startline);
			rcdflg=1;
			imgflag=0;
			break;
		}
		else if(mouse_press(274,49,354,71)==1)//点击粘贴
		{
			putimage(274,25,geti,0);
			free(geti);
			if(rcdflg==1) //如果剪贴板有内容
				{
				paste(((cursorY-24)/16+1),((cursorX-16)/8+1),startline,rcdlen,rcdflg,rcd);
				view(startline); 
				rcdlen=0;
				break; 
				}
				else
				break; 
		} 
		else if(mouse_press(274,72,354,94)==1)//点击替换 
		{
			replace(startline) ; 
			break;
		}
		else if(mouse_press(274,95,354,117)==1)//点击查找 
		{
			find(startline);
			grey=1;
			break;
		} 
		else if(mouse_press(274,118,354,140)==1)//点击剪切
		{
			putimage(274, 25, geti, 0);
			free(geti);
			for (i = 0; i < rcdlen; i++)
			{
				deltext(startline, ((cursorY - 24) / 16 + 1), ((cursorX - 16) / 8 + 1));
			}
			view(startline);
			rcdflg = 1;
			break;
		} 
		else if(mouse_press(616,0,640,24)==1)//点击关闭按钮结束程序 
		{
			closegraph(); 
			exit(0);
		} 
	}
	return 0;
}

//用于执行选择文件按钮的操作 
int chosfile(Lnode** Head,Lnode**startline)
{
	void *geti; //用于存放文件菜单栏的图像
	geti=malloc(imagesize(97,25,177,140));
	clrmous(MouseX,MouseY);
	getimage(97,25,177,140,geti);//存放文件菜单栏的图像
    drawfile();//绘制文件菜单栏
	save_bk_mou(MouseX,MouseY); 
	drawmous(MouseX,MouseY);
	while(1)//检测点击循环 
	{
	    newmouse(&MouseX,&MouseY,&press);
		if((mouse_press(10,24,97,456)==1)
			||(mouse_press(97,118,177,456)==1)
			||(mouse_press(177,24,624,456)==1) 
			|| (mouse_press(1, 1, 97, 24) == 1)
			|| (mouse_press(177, 1, 622, 24) == 1))//点击一般位置或者退出收起菜单栏 
		{
			clrmous(MouseX, MouseY);
			putimage(97,25,geti,0);
			free(geti);
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			return 0;
		}
		else if(mouse_press(97, 1,177, 24) == 1)//点击文件按钮
		{
			delay(100);
			clrmous(MouseX, MouseY);
			putimage(97, 25, geti, 0);
			free(geti);
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			return 0;
		}
		else if(mouse_press(97,25,177,48)==1)//点击新建 
		{
			
			putimage(97,25,geti,0);
			free(geti);
			newbuild(*Head,startline);
			*Head = *startline;
			clrmous(MouseX, MouseY);
			drawskbar(*Head);
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			delay(100);
			return 0;
		} 
		else if(mouse_press(97,49,177,71)==1)//点击打开 
		{
			putimage(97,25,geti,0);
			free(geti);
			opens(*Head,startline) ;
			*Head=*startline;
			clrmous(MouseX,MouseY);
			drawskbar(*Head);
			save_bk_mou(MouseX,MouseY); 
			drawmous(MouseX,MouseY);
			delay(100);
			return 0;
		} 
		else if(mouse_press(97,72,177,94)==1)//点击保存
		{
		
			putimage(97,25,geti,0);
			free(geti);
			save(*Head);
			*Head = *startline;
			clrmous(MouseX, MouseY);
			drawskbar(*Head);
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			view(startline) ;
			delay(100);
			return 0;
		}
		else if(mouse_press(97,95,177,117)==1)//点击另存为
		{	
			putimage(97,25,geti,0);
			free(geti);
			saveas(*Head);
			*Head = *startline;
			clrmous(MouseX, MouseY);
			drawskbar(*Head);
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			view(startline);
			delay(100);
			return 0;
		} 
		else if(mouse_press(616,0,640,24)==1)//点击关闭按钮结束程序 
		{
			closegraph(); 
			exit(0);
		}
	}
}
void choscompile(Lnode* Head)
{
	void* geti;
	geti = malloc(imagesize(177, 25, 274, 140));
	clrmous(MouseX, MouseY);
	getimage(177, 25, 274, 140, geti);
	drawcompile();
	save_bk_mou(MouseX, MouseY);
	drawmous(MouseX, MouseY);
	while (1)//检测点击循环 
	{
		newmouse(&MouseX, &MouseY, &press);
		if ((mouse_press(10, 24, 177, 456) == 1)
			|| (mouse_press(177, 118, 274, 456) == 1)
			|| (mouse_press(274, 24, 624, 456) == 1)
			|| (mouse_press(1, 1, 177, 24) == 1)
			|| (mouse_press(274, 1, 622, 24) == 1))//点击空白区域或者退出
		{
			clrmous(MouseX, MouseY);
			putimage(177, 25, geti, 0);
			free(geti);
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			break;
		}
	}
}
void chosview(Lnode* Head)
{
	void* geti;
	geti = malloc(imagesize(354, 25, 451, 140));
	clrmous(MouseX, MouseY);
	getimage(354, 25, 451, 140, geti);
	drawview();
	save_bk_mou(MouseX, MouseY);
	drawmous(MouseX, MouseY);
	while (1)//检测点击循环 
	{
		newmouse(&MouseX, &MouseY, &press);
		if ((mouse_press(10, 24, 354, 456) == 1)
			|| (mouse_press(354, 118, 451, 456) == 1)
			|| (mouse_press(451, 24, 624, 456) == 1)
			|| (mouse_press(1, 1, 354, 24) == 1)
			|| (mouse_press(451, 1, 622, 24) == 1))//点击空白区域或者退出
		{
			clrmous(MouseX, MouseY);
			putimage(354, 25, geti, 0);
			free(geti);
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			break;
		}
	}
}

// 用于执行选择帮助按钮的操作 
int choshelp(Lnode* Head)
{
	void* geti;
	geti = malloc(imagesize(451, 25, 531, 94));
	clrmous(MouseX, MouseY);
	getimage(451, 25, 531, 94, geti);
	drawhelp();
	save_bk_mou(MouseX, MouseY);
	drawmous(MouseX, MouseY);
	while (1)//检测点击循环 
	{
		newmouse(&MouseX, &MouseY, &press);
		if ((mouse_press(10, 24, 451, 456) == 1)
			|| (mouse_press(451, 71, 531, 456) == 1)
			|| (mouse_press(531, 24, 624, 456) == 1)
			|| (mouse_press(1, 1, 451, 24) == 1)
			|| (mouse_press(531, 1, 622, 24) == 1))//点击空白区域或者退出
		{
			clrmous(MouseX, MouseY);
			putimage(451, 25, geti, 0);
			free(geti);
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			break;
		}
		else if (mouse_press(451, 1, 531, 24) == 1)
		{
			delay(100);
			clrmous(MouseX, MouseY);
			putimage(451, 25, geti, 0);
			free(geti);
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			break;
		}
		else if (mouse_press(451, 25, 531, 48) == 1)//点击帮助
		{
			putimage(451, 25, geti, 0);
			free(geti);
			clrmous(MouseX, MouseY);
			help();
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			while (1)
			{
				newmouse(&MouseX, &MouseY, &press);
				if (mouse_press(5, 5, 61, 45) == 1)
					break;
			}
			delay(100);
			clrmous(MouseX, MouseY);
			drawmenu();
			drawskbar(Head);
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			break;
		}
		else if (mouse_press(451, 49, 531, 71) == 1)//点击关于 
		{

			putimage(451, 25, geti, 0);
			free(geti);
			clrmous(MouseX, MouseY);
			about();
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			while (1)
			{
				newmouse(&MouseX, &MouseY, &press);
				if (mouse_press(5, 5, 61, 45) == 1)
					break;
			}
			delay(100);
			clrmous(MouseX, MouseY);
			drawmenu();
			drawskbar(Head);
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			break;
		}
		if (mouse_press(616, 0, 640, 24) == 1)//点击关闭按钮结束程序 
		{
			closegraph();
			exit(0);
		}
	}
	return 0;
}
