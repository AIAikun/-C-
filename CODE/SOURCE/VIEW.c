//��д�ˣ���ĭ��
#include<common.h>
#include<view.h>

//��ӡһ�ε�ǰ��Ļ��ʾ����Ĵ��� ,��ʾ����ͼ�� 
void view(Lnode* startline)
{
	int x=17,y=25,r=1,c=1;
	node* p; 
	Lnode* q; 
	clrmous(MouseX,MouseY);  //������ 
	setfillstyle(1, BLUE); 
	bar(17,25,623,455);//�ַ��������ɫ����ʾȫ��ͼ�ο� 
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
				setcolor(p->flag);//ѡ����ɫ 
				settextstyle(0,0,1);
				outtextxy(x,y+6,p->txt);
				x+=8;
			}
			p = p->next; //��ָ��ָ����һ���ڵ�
		} 
		x=17;
		y+=16; //������һ�е�һ�� 
		q = q->nextl; //��ָ��ָ����һ���ڵ㣬������һ��			
	}
	save_bk_mou(MouseX,MouseY); 
	drawmous(MouseX,MouseY);//��ԭ 
}



 
//��XYλ������һ���ַ��������ַ������� ,����ָ��λ�������ļ����ȹ��� ��������Ҫ�����ļ��������� 
int gettxtname(char* s,int x,int y)
{
	
	char a;//�����ַ���������������һ��һ������� 
	char bio[2];//�������� 
	int i=0;
	while(1)
	{
		if (bioskey(1))//���������� 
			{
				a=bioskey(0);//��ȡ��ֵ 
				if(a>=32&&a<127)
				{
					bio[0]=a;
					bio[1]='\0';
					setcolor(WHITE);
					settextstyle(0,0,1);
					outtextxy(x,y,bio);//ָ��λ������ַ� 
					x+=8;//�ƶ�һ���ַ���� 
					s[i]=a;
					s[i+1]='\0';//��ʱ�Ľ�β 
					i++;
				}
				else if(a==8)//���˸� �������ķ�ʽɾ�� 
				{
					if (i > 0)//������ַ���ɾ�� 
					{
						setfillstyle(1, BLUE);
						bar(x - 8, y, x - 1, y + 16);
						i--;
						x -= 8;
					}
				}
				else if(a==13)//���س��������� 
				{
					break;
				}
			}
	
	}
	return i+1; 
}

//����:���ĳ������λ���Ƿ����ַ������ڵ��Ƿ�Ϊ�� ,����0Ϊ�գ�����1Ϊ�ǿգ� �����������ʶ�� 
int checktxt(int x,int y,Lnode* startline)
{
	int i=0;
	Lnode* q1;
	node* p1;
	q1=startline;
	for(i=1;i<y;i++)
	{
		q1=q1->nextl;
		if(q1==NULL)//�����һ�в����ڷ���0 ���������Ч 
			return 0;
		
	}
	p1=q1->next; 
	for(i=1;i<x;i++)
	{
		if(p1==NULL)//�����һ�д��ڵ������λ��û���ַ�����2 ���ҵ��������һ���ַ������������Ǹ�λ�� 
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

//���ܣ����һ���ж����в��������� 
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
 
