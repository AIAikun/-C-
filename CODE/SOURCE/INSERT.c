#include<common.h>
#include"INSERT.h"

/*********************************************
	���ı������༭ģ�顿
	��д�ˣ������� 
insert����ִ���ַ����������
deltext����ִ��ɾ������ ��
enter����ִ�л��в�����
match����ִ����������ƥ������� 
movepic���ڸ��Ʋ��� 
*********************************************/

//���ã���x1,y1����Ϊl����ͼ�񱣴棬�ٷŵ�x2,y2�� �����ڸ��� 
int movepic(int x1,int y1,int l,int x2)
{
	void *pic;//ͼ��ָ�� 
	pic=malloc(imagesize(x1,y1,x1+7+l*8,y1+15));//��ȡ��С 
	getimage(x1,y1,x1+7+(l-1)*8,y1+15,pic);
	setcolor(WHITE); 
	putimage(x2,y1,pic,0);
	free(pic);
	return 0;
}
//��鴫���ָ������м����ڵ㲢�������ֵ 
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

//���ܣ����һ���ж����ַ����������ֵ ,�������س����� 
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
	for(i=0;(p->txt[0]!=13)&&(p!=NULL);i++)//ע�������ǽڵ㱾������� 
	{
		p=p->next;
	}
	return i;
	}
 } 
 //���ܣ��ҵ���һ�����һ���ڵ� 
node* endofline(Lnode*q){
		int i;
	node* p;
	p=q->next;
	for(i=0;(p->next->txt[0]!=13)&&(p!=NULL);i++)//ע�������ǽڵ㱾������� 
	{
		p=p->next;
	}
	return p;
}
//���ܣ��ҵ������ڶ����ڵ�
node*lastendline(Lnode*q){
	
	node*p;
	{
		for(p=q->next;(p->next->next!=NULL&&p->next->next->txt[0]!=13);p=p->next){;}
	}
	return p;
}
//��¼�������� 
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


int  insert(char* bioget,int m,int n,Lnode*startline)//��������ݰ�����ָ�����У��У�Ҫ����ַ���ָ�룬��ǰ��һ�е�ͷ��� ,�������Ӣ�ģ�������������
{
	int i,m1;//��־�е�λ�� 
	Lnode* q1,*q2,*q3;//��ָ��Ϊָ���е�ָ�� 
	node*p1,*p2,*p3,*p4;//��ָ��Ϊָ��һ�����ݽڵ��ָ�� 
	q1=startline;//q1ָ��ǰ��ʾ����ĵ�һ�� 
	for(i=1;i<m;i++)
		q1=q1->nextl;//ѭ��ʹ��q1�ƶ�����m�� 
	p1=q1->next;//p1ָ���m�еĵ�һ�� 
	for(i=1;i<n-1;i++)//ѭ������n-1��,ָ���Ѿ������λ��
		{
			p1=p1->next;
			if(p1->sign==1)	i++;	//����������֣������к���һλ (��Ϊ����ռ���� ������Ҫ��2���ַ�λ�ô����в��� 
		}
		//��ɳ�ʼ��
if(p1->next!=NULL)//�м�����
{
		if(n==1) //�����һ�в��� 
		{
			if(getline(q1)<kuandu) //һ��δ�� 
			{
				p2=(node*)malloc(sizeof(node));
				p2->txt[0]=bioget[0];p2->txt[1]='\0';p2->sign=0; p2->flag=WHITE;
				p2->next=p1;//��p1���� 
				q1->next=p2; //p2Ϊ�µ�ͷ��� 
				delcursor();//������ 
				clrmous(MouseX,MouseY);//������ 
				movepic(cursorX,cursorY,getlinelen(q1),cursorX+8);//����ƶ�
				setfillstyle(1, BLUE);
				bar(cursorX,cursorY,cursorX+7,cursorY+15);//�ѵ�һ������ 
				settextstyle(0,0,1);
				setcolor(WHITE);
				outtextxy(cursorX,cursorY+6,bioget); //������������ַ�������ʾ 
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);//�ػ� 
				cursorX+=8;//��¼����ƶ�8�����ص�λ�� 
				imgflag=0; 
				newcursor();//���¹��  
			}
			else if(getline(q1)==kuandu) //һ���Ѿ����� 
			 {
				p2=(node*)malloc(sizeof(node));
				p2->txt[0]=bioget[0];p2->txt[1]='\0';p2->sign=0;p2->flag=WHITE;
				p2->next=q1->next;
				q1->next=p2; //���������� 
			    p3=lastendline(q1);
			    p4=endofline(q1);
				if(q1->nextl==NULL)//�����һ���нڵ��ǿյģ��½�һ�� 
				{
					q2=(Lnode*)malloc(sizeof(Lnode));
					q2->next=p4;
					q2->nextl=NULL;
					q1->nextl=q2;
					p3->next=NULL;
					p4->next=NULL;
				}
			    else if(getline(q1->nextl)<kuandu)//��һ��û�� 
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
		//�����ڵ�һ�еĲ���
		    if(getline(q1)<kuandu)//����δ�� 
			{
				p2=(node*)malloc(sizeof(node));
				p2->txt[0]=bioget[0];p2->txt[1]='\0';p2->sign=0; p2->flag=WHITE;
			   p2->next=p1->next;
			   p1->next=p2;
			   delcursor();//������ 
				clrmous(MouseX,MouseY);//������ 
				movepic(cursorX,cursorY,getlen(p1),cursorX+8);
				setfillstyle(1, BLUE);
				bar(cursorX,cursorY,cursorX+7,cursorY+15);
				settextstyle(0,0,1);
				setcolor(WHITE);
				outtextxy(cursorX,cursorY+6,bioget); //������������ַ�������ʾ 
				save_bk_mou(MouseX,MouseY); 
				drawmous(MouseX,MouseY);//�ػ� 
				cursorX+=8;//��¼����ƶ�8�����ص�λ�� 
				imgflag=0; 
				newcursor();//���¹�� 
			   
			}
			else//�����Ѿ�����
			{
				p2=(node*)malloc(sizeof(node));
				p2->txt[0]=bioget[0];p2->txt[1]='\0';p2->sign=0; p2->flag=WHITE;
				p2->next=p1->next;
			   p1->next=p2;
				p4=endofline(q1);
				p3=lastendline(q1);
				if(q1->nextl==NULL)//��һ��δ����
				{	
					q2=(Lnode*)malloc(sizeof(Lnode));
					q2=q1->nextl;
					q2->nextl=NULL;
					q2->next=p4;
					p3->next=NULL;
				}
				else//��һ���Ѿ�����
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
   else//��ĩβ���루�����ϵ���ĩβ ,����һ��û�нڵ� 
    {
		if(n==1)//�����ڵ�һ��λ������ 
		{
			if(p1!=NULL)// �����ڵ�һ��λ���нڵ���������ʱ����Ҫ�½� 
			{
				p1->txt[0]=bioget[0];
				p1->txt[1]='\0';
				p1->sign=0;
				p1->next=NULL;
				p1->flag=WHITE;//������ͼ�β��� 
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
			else//�����ڵ�һ��λ��û�нڵ����� 
			{
				p1=(node*)malloc(sizeof(node));//�½� 
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
			
		}//�����ڵ�һ�е� ��β 
		else 
		{
		 if(getline(q1)==kuandu)//��������ĩβ���루�����β�� 
		 {			
			p2=(node*)malloc(sizeof(node));//�½�һ���ڵ� ������ 
			p2->txt[0]=bioget[0];
			p2->txt[1]='\0';
			p2->sign=0;
			p2->flag=WHITE;
		    p1->next=NULL; 
			if(q1->nextl==NULL)//�����һ���нڵ��ǿյģ��½�һ�� 
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
		else //�������м�������δ������β 
		{
			p2=(node*)malloc(sizeof(node));
			p2->txt[0]=bioget[0];p2->flag=WHITE;
			p2->txt[1]='\0';
			p2->sign=0;
			p2->next=NULL;
			p1->next=p2;
			delcursor();//˳�����꣬������ȷ����ɫ�Լ���ʽ����ʾ���֣��ظ�����Լ����� ���ظ���� 
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
//���ܣ�ִ��enter�Ļ��в�����
void enter(int m,int n,Lnode* startline)
{
	int i;
	Lnode* q1,*q2;//��ָ��Ϊָ��һ�����ݵ�ָ�� 
	node*p1,*p2,*p3;//��ָ��Ϊָ��һ�����ݽڵ��ָ�� 
	q1=startline;//q1ָ��ǰ��ʾ����ĵ�һ�� 

	for(i=1;i<m;i++)
		q1=q1->nextl;//ѭ��ʹ��q1�ƶ�����m�� 
	p1=q1->next;//p1ָ���m�еĵ�һ�� 
	for(i=1;i<n-1;i++)//ѭ������n-1��
		{
			p1=p1->next;
			if(p1->sign==1)	i++;//����������֣������к���һλ (��Ϊ����ռ���� 
			
		}
	p2=(node*)malloc(sizeof(node));
			p2->txt[0]=13;
			p2->txt[1]='\0';
			p2->sign=0;
	q2=(Lnode*)malloc(sizeof(Lnode));
	if(n==1)//������һ�п�ͷ����� 
	{	
		if(q1->nextl!=NULL) // ��һ���ж��� 
		{
			q2->nextl=q1->nextl;
			q1->nextl=q2;
			q2->next=p1;
			q1->next=p2;
			p2->next=NULL;
		}
		else//��һ�п� 
		{
			q2->next=p1;
			q1->next=p2;
			q1->nextl=q2;
			q2->next=NULL;
		}
	}
	else//������һ�п�ͷ����� 
	{
		if(q1->nextl!=NULL)//��������һ�е���� 
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
		else//����û����һ�е���� 
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
	 if(m==27)//���λ�õĻ���������Զ���ҳ���� 
	{
		down_page(startline,&startline);
		cursorY-=16;//���λ�ò������仯��������+16������ 
	}
	view(startline);
	cursorX=17;
	cursorY+=16;
	imgflag=0;			

}
 
//���ڼ���������Ų�������Ӧ��ƥ�� 
void match(char* bioget,Lnode* startline)
{
	char match[2]={'\0','\0'};
	if(bioget[0]-'('==0)//������ ���ü�ֵ��Ϊ0�б� 
	{
		match[0]=41;
		insert(match,((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
	}
	else if(bioget[0]-'{'==0)//������ 
	{
		match[0]=125;//��ֵΪ125 
		insert(match,((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
	}
	else if(bioget[0]==34)//pagedown ��λ 
	{
		insert(bioget,((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
	}
	else if(bioget[0]-'['==0)//������ 
	{
		match[0]=93;
		insert(match,((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
	}
	else if(bioget[0]-'<'==0)//�����Ǻ� 
	{
		match[0]=62;
		insert(match,((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
	}
	else if(bioget[0]==39)//�ҷ���� ������ 
	{
		insert(bioget,((cursorY-24)/16+1),((cursorX-16)/8+1),startline);
	}
}
//ɾ��ָ���ַ����� ��Ҳ���˸�ɾ����λ������Ч�� 
int deltext(Lnode*startline,int r,int c) //������ָ�룬������ڵ������Լ�������������del�Լ�backspace�Ĳ��� ��r��c�� 
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
	for(i=1;i<c-2;i++)//ѭ��������ǰ2�� 
		{
			p1=p1->next;
		if(p1->next->sign==1)	i++;//����������֣�����к���һλ 
		} 
	p2=p1->next;//��һ���ڵ� ���ǵ�ǰ�Ľڵ� 
if(c==1) //����
{
	if(r==1)//�ڵ�һ������
	{
		return 0; 
	}
	else//���ڵ�һ�п�ͷ 
	{
		if(getline(q2)==kuandu) //��һ������
		{
			p3=lastendline(q2);
			p4=endofline(q2);
			if(p4->sign==0)//��һ���ַ���β 
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
			else//��һ�к��ֽ�β 
			{
				if(p1->sign==1)//��һ�к��ֿ�ͷ 
				{
					cursorX=kuandu-16;
					free(p4);
			       p3->next=p1;
			       q1->next=p1->next;
		           p1->next=NULL;
				}
				else//��һ���ַ���ͷ 
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
		else//��һ��û��
		{
		  if(getline(q2)>=1)
		  {
			p3=endofline(q2);
			p3->next=p1;
			rest=kuandu-getline(q2);
			len=getline(q1);//���г��� 
			m=getline(q2);//��һ�г��� 
			
			
			 if(len<=rest)//��һ�еĳ����ܹ�������һ�е�ȫ��
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
			 else//���������ȫ���룬��ֻ��һ�����������ƶ�
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
		   else  if(q2->next==NULL||q2->next->txt[0]==13)//��һ�п� 
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
else//�м�ɾ��
    {  
	  if((p2->next==NULL)||(p2==NULL))//�����ĩβ�� 
		 {
			if(c==2&&p1->sign==0) //�������ڵڶ���Ԫ�ص�λ�ã�ɾ����һ���ַ� ����Ϊ�漰�������ڵĸı䣬�����Ҫ�������� 
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
			else//���ڵڶ���λ�� �������׺���λ�ã����漰������ı仯 
			{
				if(p2->sign==0)//������ַ�
				{
					p1->next=NULL;//p1����β ����һ�� 
					free(p2);//�ͷŽڵ� 
					delcursor();
					clrmous(MouseX,MouseY);
					setfillstyle(1, BLUE);
					bar(cursorX-8, cursorY, cursorX,cursorY+15);//����ɫ�����ʵ���ַ���ɾ�� 
					save_bk_mou(MouseX,MouseY); 
					drawmous(MouseX,MouseY);
					cursorX-=8;//�����ǰ�ƶ� 
					imgflag=0;
					newcursor();
				}
				else if(p2->sign==1)//����Ǻ���
				{
					
					p1->next=NULL;
					free(p2);
					delcursor();
					clrmous(MouseX,MouseY);
					setfillstyle(1, BLUE);
					bar(cursorX-16, cursorY, cursorX,cursorY+15);//�������ַ� 
					save_bk_mou(MouseX,MouseY); 
					drawmous(MouseX,MouseY);
					cursorX-=16;
					imgflag=0;
					newcursor();
				}  
			}
			
		}
		else//����½ڵ�ǿգ�ɾ���˴��ڵ㣬�������ͼ��ǰ�� 
		{
			if(c==2) //�������ڵڶ���λ�ã�ɾ����һ���ַ� 
			{
				q1->next=p2->next; 
				free(p2); 
				view(startline);//��ʼ��ʾ���� 
				cursorX-=8;
				imgflag=0;
				newcursor();
			}
			else//���ڵڶ���λ�� 
			{
				if(p2->sign==0)//������ַ�
				{
					p1->next=p2->next;
					free(p2);
					view(startline);
					cursorX-=8;
					imgflag=0;	
					newcursor();		
				}
				else if(p2->sign==1)//����Ǻ���
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
