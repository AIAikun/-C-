#include<common.h>
#include "mainloop.h"
/*************************************
����ѭ��������
��д�ˣ���ĭ��
 mainloopΪ��ѭ������
chosedit��Ӧ����༭�˵�����Ĳ��� 
chosfile��Ӧ����ļ��˵�����Ĳ��� 
choshelp��Ӧ��������˵�����Ĳ��� 
**************************************/
char rcd[80];//���ڴ�ż����������
int rcdlen=0;//���ڴ��������ĳ��� 
int rcdflg=0; //����ָʾ�������Ƿ��Ѿ����� 
int grey=0;//��¼�Ƿ��л�ɫ���֣����ڴ�����ҵ� 
//��ѭ������ 
void mainloop()
{
	//��ʼ������ ������ 
	int ch,row=1,column=1,o,i=0,mx,my,j,sig;
	char a;
	char bioget[2];//���ڴ�ŵ�ǰ�ļ�ֵ 
	void *bitmap2;//���ڴ������Ҽ��˵��ڵ�ס�ĵ�ͼ��
	node* p1,p2;
	Lnode* Head, * q, *startline, * temp;//���ڴ����������ͷָ��
	Head=(Lnode*)malloc(sizeof(Lnode));//Ϊ�е������׽ڵ����ռ� 
	q=Head;	Head->nextl=NULL;	
	q->next=NULL;
	startline=Head;
	drawmenu();
	full_skbar();
	//��ѭ�� 
	while(1)
	{
		newmouse(&MouseX, &MouseY, &press);
		memset(bioget,'\0',2);
		row=(cursorY-24)/16+1;
		column=(cursorX-16)/8+1;
		drawrc(row+countdown,column);
		newcursor();//�����û�д������ͼ�񣬾ʹ��棬��ֹ����ڸ���Ļ����
		//�ж������ 
		if(mouse_press(9,25,615,455)==1)//����������Ļλ�ã��ƶ���굽����λ�� 
		{
			if((rcdlen!=0)&&(rcdflg==0))//��������������ݣ�����û�и��ƻ��߼��У�����ռ�����
			{
				rcdlen=0;
				view(startline);
			}
			if (grey==1) //�������ɫ����
			{
				grey=0;
				view(startline) ;//������ɫ 
			 } 
			i= checktxt(((MouseX-16)/8+1),((MouseY-24)/16+1),startline);
			if(i==1)//�������ֵ��1,����һ�д��ڲ������λ�����ַ������ƶ���굽�ַ�λ�� 
			{
				clrmous(MouseX,MouseY);
				delcursor();
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);
				cursorX=(MouseX-16)/8*8+17;
				cursorY=(MouseY-24)/16*16+25;
				imgflag=0;
			}
			else if(i==2)//�������ֵ��2������һ�д��ڵ������λ��û���ַ������ƶ���굽��һ�����һ��λ�� 
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
		else if(mouse_press(9,25,615,455)==3)//�Ҽ���� 
		{
			bitmap2=malloc(imagesize(1,1,64,52));
			
			if(MouseX>17&&MouseX<=304&&MouseY>25&&MouseY<=216)//���Ͻ� 
			{
				mx=MouseX;
				my=MouseY;
				clrmous(MouseX,MouseY);
				getimage(mx,my,mx+63,my+51,bitmap2);
				drawwin(mx,my);
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);
			}
			else if(MouseX>304&&MouseX<624&&MouseY>25&&MouseY<=216)//���Ͻ� 
			{
				mx=MouseX-63;
				my=MouseY;
				clrmous(MouseX,MouseY);
				getimage(mx,my,mx+63,my+51,bitmap2);
				drawwin(mx,my);
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);
			}
			else if(MouseX>17&&MouseX<=304&&MouseY>216&&MouseY<456)//���½� 
			{
				mx=MouseX;
				my=MouseY-51;
				clrmous(MouseX,MouseY);
				getimage(mx,my,mx+63,my+51,bitmap2);
				drawwin(mx,my);
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);
			}
			else if(MouseX>304&&MouseX<624&&MouseY>216&&MouseY<456)//���½� 
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
				if(mouse_press(mx,my,mx+63,my+17)==1)//�������
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
				else if(mouse_press(mx,my+18,mx+63,my+34)==1)//������� 
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
				else if(mouse_press(mx,my+35,mx+63,my+63)==1)//���ճ�� 
				{
					putimage(mx,my,bitmap2,0);
					free(bitmap2);
				 	if(rcdflg==1) //���������������
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
				||(mouse_press(17,my+52,mx+64,456)==1)||(mouse_press(mx+64,my,624,456)==1))//����������� 
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
                || (mouse_press(mx + 64, my, 624, 456) == 3))//�Ҽ������������
                {
                clrmous(MouseX, MouseY);
                putimage(mx, my, bitmap2, 0);
                save_bk_mou(MouseX, MouseY);
                drawmous(MouseX, MouseY);
                free(bitmap2);
                delay(100);
                bitmap2 = malloc(imagesize(1, 1, 64, 52));

                if (MouseX > 17 && MouseX <= 304 && MouseY > 25 && MouseY <= 216)//���Ͻ� 
                {
                    mx = MouseX;
                    my = MouseY;
                    clrmous(MouseX, MouseY);
                    getimage(mx, my, mx + 63, my + 51, bitmap2);
                    drawwin(mx, my);
                    save_bk_mou(MouseX, MouseY);
                    drawmous(MouseX, MouseY);
                }
                else if (MouseX > 304 && MouseX < 624 && MouseY>25 && MouseY <= 216)//���Ͻ� 
                {
                    mx = MouseX - 63;
                    my = MouseY;
                    clrmous(MouseX, MouseY);
                    getimage(mx, my, mx + 63, my + 51, bitmap2);
                    drawwin(mx, my);
                    save_bk_mou(MouseX, MouseY);
                    drawmous(MouseX, MouseY);
                }
                else if (MouseX > 17 && MouseX <= 304 && MouseY > 216 && MouseY < 456)//���½� 
                {
                    mx = MouseX;
                    my = MouseY - 51;
                    clrmous(MouseX, MouseY);
                    getimage(mx, my, mx + 63, my + 51, bitmap2);
                    drawwin(mx, my);
                    save_bk_mou(MouseX, MouseY);
                    drawmous(MouseX, MouseY);
                }
                else if (MouseX > 304 && MouseX < 624 && MouseY>216 && MouseY < 456)//���½� 
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
		
		else if(mouse_press(616,25,640,40)==1)//������ư�ť
		{
			up_page(Head,&startline);
			view(startline);
			delay(100);
		}
		else if(mouse_press(616,440,640,456)==1)//������ư�ť
		{
			down_page(Head,&startline);
			view(startline);
			delay(100);
		}
		else if(mouse_press(616,40,639,440)==1)//����϶���
		{
			click_skbar(Head,&startline);
			view(startline);
			delay(100);
		}
		else if(mouse_press(616,0,640,24)==1)//����رհ�ť�������� 
		{
			closegraph(); 
			exit(0);
		}
		else if(mouse_press(97,1,177,24)==1)//����ļ���ť 
		{
			delcursor();
			delay(100);
			chosfile(&Head,&startline);
			highlight(startline);
			view(startline);
		}
		else if(mouse_press(274,1,354,24)==1)//����༭��ť 
		{
			delcursor();
			delay(100);
			chosedit(startline,bioget,rcd);  
		}
		else if(mouse_press(451,1,531,24)==1)//���������ť 
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
		//������������¼�	
		if (bioskey(1))//���������� 
		{
			a=ch=bioskey(0);//��ȡ����ļ�ֵ 
			if(ch==0x4B00&&cursorX>=17)//������� 
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
			else if(ch==0x4800&&cursorY>25)//������� 
			{
				i= checktxt(((cursorX-16)/8+1),((cursorY-24)/16),startline);
				if(i==1)//�������ֵ��1�����ƶ���� ����һ�и�λ�� 
				{
					delcursor();
					cursorY-=16;
					imgflag=0;
					newcursor();
				}
				else if(i==2)//�������ֵ��2���ƶ���굽��һ�����һ��λ�� 
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
			else if(ch==0x4d00&&cursorX<616)//������� 
			{
				i= checktxt(((cursorX-16)/8+2),((cursorY-24)/16+1),startline);//�����һ��λ���Ƿ���ֵ 
				if(i==1)//�������ֵ1�����ƹ�� 
				{
					delcursor();
					cursorX+=8;
					imgflag=0;
				}
				else if(i==2)//�������ֵ2��������һ���ƶ�����һ�е�һ��λ�� 
				{
					q=startline;
					for(j=1;j<((cursorY-24)/16+2);j++)
						q=q->nextl;
					if(q!=NULL) 
						movecursor(1,((cursorY-24)/16+2));
					
						
				}
			}
			else if(ch==0x5000&&cursorY<440)//������� 
			{
				i= checktxt(((cursorX-17)/8+1),((cursorY-24)/16+2),startline);
				if(i==1)//�������ֵ��1�����ƶ���� ����һ�и�λ�� 
				{
					delcursor();
					cursorY+=16;
					imgflag=0;
					newcursor();
				}
				else if(i==2)//�������ֵ��2���ƶ���굽��һ�����һ��λ�� 
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
			else if(ch==F4)//��F4�����뺺������ģʽ 
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
			else if(ch==F1)//��F1�����ļ��˵� 
			{
				chosfile(&Head, &startline);
				highlight(startline);
				view(startline);
			}
			else if(ch==F2)//��F2���򿪱༭�˵� 
			{
				chosedit(startline,bioget,rcd);
			}
			else if(ch==F3)//��F3���򿪰����˵� 
			{
				delcursor();
				choshelp(Head);
				view(startline);
				imgflag=0;
			}
			else if(ch==F10)//��F10��ˢ������ 
			{
				highlight(startline);
				view(startline);
			}
			else if(ch==0x1C0D)//�س��� 
			{
				enter(((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
			} 
			else if(ch==CR)//��ctrl+�����Ƽ�ѡ���ı� 
			{
				int i ;
				Lnode* q1;
				node* p1;
				q1 = startline;
				for (i = 1; i < row; i++)
					q1 = q1->nextl;//ѭ��ʹ��q1�ƶ�����m�� 
				p1 = q1->next;//p1ָ���m�еĵ�һ��
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
			
			else if(ch==Cc)//���Ƽ� 
			{
				delcursor();
				view(startline);
				rcdflg=1;
				imgflag=0;	
			}
			else if(ch==Cx)//���м� 
			{
				
				
				for(i=0;i<rcdlen;i++)
				{
					deltext	(startline,((cursorY-24)/16+1),((cursorX-16)/8+1));
				}
				view(startline);
				rcdflg=1;
				sig=1;
			} 
			else if(ch==Cv)//ճ���� 
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
			else if(ch==TAB) //TAB����4�ո� 
			{
				sig=1;
				bioget[0]=' ';
				for(i=0;i<4;i++)
				{
					insert(bioget,((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
				}
			}
			else if(a>=32&&a<127) //�������֣����� 
			{
				sig=1;
				bioget[0]=a;
				insert(bioget,((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
				match(bioget,startline);//����Ƿ���Ҫƥ�� 
			}
			else if(ch==BACK)//�˸�� 
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
			else if(ch==DEL)//DEL�� 
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

//����ִ��ѡ��༭��ť�Ĳ��� 
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
	while(1)//�����ѭ�� 
	{
	    newmouse(&MouseX,&MouseY,&press);
		if((mouse_press(10,24,274,456)==1)
			||(mouse_press(274,140,354,456)==1)
			||(mouse_press(354,24,624,456)==1) 
			|| (mouse_press(1, 1, 274, 24) == 1)
			|| (mouse_press(354, 1,622 , 24) == 1))//����հ���������˳�
		{
			clrmous(MouseX, MouseY);
			putimage(274,25,geti,0);
			free(geti);
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			break;
		}
		else if (mouse_press(274, 1, 354, 24) == 1)//����༭��ť
		{
			delay(100);
			clrmous(MouseX, MouseY);
			putimage(274, 25, geti, 0);
			free(geti);
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			break;
		}
		else if(mouse_press(274,25,354,48)==1)//������� 
		{
			putimage(274,25,geti,0);
			free(geti);
			delcursor();
			view(startline);
			rcdflg=1;
			imgflag=0;
			break;
		}
		else if(mouse_press(274,49,354,71)==1)//���ճ��
		{
			putimage(274,25,geti,0);
			free(geti);
			if(rcdflg==1) //���������������
				{
				paste(((cursorY-24)/16+1),((cursorX-16)/8+1),startline,rcdlen,rcdflg,rcd);
				view(startline); 
				rcdlen=0;
				break; 
				}
				else
				break; 
		} 
		else if(mouse_press(274,72,354,94)==1)//����滻 
		{
			replace(startline) ; 
			break;
		}
		else if(mouse_press(274,95,354,117)==1)//������� 
		{
			find(startline);
			grey=1;
			break;
		} 
		else if(mouse_press(274,118,354,140)==1)//�������
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
		else if(mouse_press(616,0,640,24)==1)//����رհ�ť�������� 
		{
			closegraph(); 
			exit(0);
		} 
	}
	return 0;
}

//����ִ��ѡ���ļ���ť�Ĳ��� 
int chosfile(Lnode** Head,Lnode**startline)
{
	void *geti; //���ڴ���ļ��˵�����ͼ��
	geti=malloc(imagesize(97,25,177,140));
	clrmous(MouseX,MouseY);
	getimage(97,25,177,140,geti);//����ļ��˵�����ͼ��
    drawfile();//�����ļ��˵���
	save_bk_mou(MouseX,MouseY); 
	drawmous(MouseX,MouseY);
	while(1)//�����ѭ�� 
	{
	    newmouse(&MouseX,&MouseY,&press);
		if((mouse_press(10,24,97,456)==1)
			||(mouse_press(97,118,177,456)==1)
			||(mouse_press(177,24,624,456)==1) 
			|| (mouse_press(1, 1, 97, 24) == 1)
			|| (mouse_press(177, 1, 622, 24) == 1))//���һ��λ�û����˳�����˵��� 
		{
			clrmous(MouseX, MouseY);
			putimage(97,25,geti,0);
			free(geti);
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			return 0;
		}
		else if(mouse_press(97, 1,177, 24) == 1)//����ļ���ť
		{
			delay(100);
			clrmous(MouseX, MouseY);
			putimage(97, 25, geti, 0);
			free(geti);
			save_bk_mou(MouseX, MouseY);
			drawmous(MouseX, MouseY);
			return 0;
		}
		else if(mouse_press(97,25,177,48)==1)//����½� 
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
		else if(mouse_press(97,49,177,71)==1)//����� 
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
		else if(mouse_press(97,72,177,94)==1)//�������
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
		else if(mouse_press(97,95,177,117)==1)//������Ϊ
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
		else if(mouse_press(616,0,640,24)==1)//����رհ�ť�������� 
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
	while (1)//�����ѭ�� 
	{
		newmouse(&MouseX, &MouseY, &press);
		if ((mouse_press(10, 24, 177, 456) == 1)
			|| (mouse_press(177, 118, 274, 456) == 1)
			|| (mouse_press(274, 24, 624, 456) == 1)
			|| (mouse_press(1, 1, 177, 24) == 1)
			|| (mouse_press(274, 1, 622, 24) == 1))//����հ���������˳�
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
	while (1)//�����ѭ�� 
	{
		newmouse(&MouseX, &MouseY, &press);
		if ((mouse_press(10, 24, 354, 456) == 1)
			|| (mouse_press(354, 118, 451, 456) == 1)
			|| (mouse_press(451, 24, 624, 456) == 1)
			|| (mouse_press(1, 1, 354, 24) == 1)
			|| (mouse_press(451, 1, 622, 24) == 1))//����հ���������˳�
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

// ����ִ��ѡ�������ť�Ĳ��� 
int choshelp(Lnode* Head)
{
	void* geti;
	geti = malloc(imagesize(451, 25, 531, 94));
	clrmous(MouseX, MouseY);
	getimage(451, 25, 531, 94, geti);
	drawhelp();
	save_bk_mou(MouseX, MouseY);
	drawmous(MouseX, MouseY);
	while (1)//�����ѭ�� 
	{
		newmouse(&MouseX, &MouseY, &press);
		if ((mouse_press(10, 24, 451, 456) == 1)
			|| (mouse_press(451, 71, 531, 456) == 1)
			|| (mouse_press(531, 24, 624, 456) == 1)
			|| (mouse_press(1, 1, 451, 24) == 1)
			|| (mouse_press(531, 1, 622, 24) == 1))//����հ���������˳�
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
		else if (mouse_press(451, 25, 531, 48) == 1)//�������
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
		else if (mouse_press(451, 49, 531, 71) == 1)//������� 
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
		if (mouse_press(616, 0, 640, 24) == 1)//����رհ�ť�������� 
		{
			closegraph();
			exit(0);
		}
	}
	return 0;
}
