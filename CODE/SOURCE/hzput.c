#include<common.h>
#include<HZPUT.h> 
extern int cursorX;
/************************
���������뷨��
 hz_put��������
  input_method����Ϊ�û��ṩ����ѡȡ 
************************/ 
int hz_put(int cursorX,int cursorY,int m,int n,Lnode*startline)//������λ�� ,������ 
{ 
	int asc,pylen,kbget=0,i,maxhz,len;//��¼��ֵ ;
	int barx1,barx2,bary1,bary2;
	int method=-1;//���뷨���ط�ʽ��1.��SPACE���������뺺�� 2.��ENTER����������Ӣ�� 3.�˸�����ز�����
	void *image;//ͼ��ָ�� 
	char *p,temp ;
	Lnode* q1,*q2;
	node*p1,*p2,*p3;
	char str[3]={'\0','\0','\0'};//����һ������ 
	char py[12]={'\0','\0','\0','\0','\0','\0','\0','\0',
	            '\0','\0','\0','\0'};//ƴ���ַ���(�����ַ���)
	q1=startline;//q1ָ��ǰ��ʾ����ĵ�һ�� 
	for(i=1;i<m;i++)
		q1=q1->nextl;//ѭ��ʹ��q1�ƶ�����m�� 
	len=getline(q1);
	if(q1->next==NULL)//�����һ�л�û�б�����
	 {
	 	p2=(node*)malloc(sizeof(node));//�½�һ���ڵ� 
	     q1->next=p2;
		 p2->sign=1;
	 }
	 else //��һ����Ԫ�� 
	{
	if((kuandu-len)<16)//�п��� 
	{
			p1=q1->next;//p1ָ���m�еĵ�һ�� 
	      for(i=1;i<n-1;i++)//ѭ������n-1��
		   {
			p1=p1->next;
			if(p1->sign==1)	i++;//����������֣�����к���һλ (��Ϊ����ռ���� 
		   }  
	      p3=(node*)malloc(sizeof(node));//�½�һ���ڵ� 
	      p3->sign=0;
	      p3->txt[0] =13;
	      p3->txt[1]='\0';
	      p1->next=p3;
	      p3->next=NULL;
	      p2=(node*)malloc(sizeof(node));//�½�һ���ڵ� 
	      p2->sign=1;	//��¼�ڵ�̬Ϊ���� 
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
	else //�п��㹻 
	{
	
	   p1=q1->next;//p1ָ���m�еĵ�һ�� 
	   for(i=1;i<n-1;i++)//ѭ������n-1��
		{
			p1=p1->next;
			if(p1->sign==1)	i++;//����������֣�����к���һλ (��Ϊ����ռ���� 
		}  
	   p2=(node*)malloc(sizeof(node));//�½�һ���ڵ� 
	   p2->sign=1;	//��¼�ڵ�̬Ϊ���� 
	   if(p1->next!=NULL)//����һ�� 
	   {
		p3=p1->next;
		p2->next=p3;
		p1->next=p2;
		                                                                                                                                                                                                                                              
       }
	    else//p1����û�� ����β 
	   {   
	    p1->next=p2;
		p2->next=NULL;
       }
    }
	}     
	settextjustify(LEFT_TEXT,CENTER_TEXT);//����������ʽ �����뷽ʽ 
	clrmous(MouseX, MouseY);//������

	while(bioskey(1))//������̻�����  ��ֹ������
	{
		bioskey(0);
	}
	if((image=malloc(8241))==NULL)//��ȡһ��ͼ�� ʧ�� 
	{
		closegraph();
		printf("error!,hz_input");
		getch(); 
		exit(1);
	}
	while(1)
	{
		if(kbhit())//������޼������룬�з��ط�0 ��ÿ�μ��һ������ 
		{
			kbget=bioskey(0);//��¼��ֵ ;
		
			/*���뺺�����뷨*/																
			asc=kbget&0xff;//ȡ���� 
			if(asc>=97&&asc<=122)
			{
				barx1=(cursorX+8-50>0)?(cursorX+8-50):0;       //�������뷨λ��  �����������Ͻ��Ҳ������Ļ
	    		barx2=(barx1+200<630)?(barx1+200):(barx1=430,630);
				bary1=cursorY+40;
				bary2=(bary1+40<480)?(bary1+40):(bary1=cursorY-80,bary1+40);
				getimage(barx1,bary1,barx2,bary2,image);//������򴦵�ԭ��ͼ�񱣴棬��ֹ���ǵ��µĶ�ʧ 
				pyFrm(barx1,bary1,barx2,bary2);//��λ��������� 
				setfillstyle(1,RED);
				method=input_method(barx1,bary1,str,kbget,py);// ѡ��ʽ 
				switch(method)//ѡ���ط�ʽ 
				{
					case 1://�����ּ���ո���˳����뷨  ���뺺��
					    if(strlen(str))//�����ַ�������Ϊ��
						{
							strcpy(p,str);//���صĸ���p ��һ���� 
							strcpy(p2->txt,p);
						}
							puthz(cursorX,cursorY,str,16,16,WHITE);
						putimage(barx1,bary1,image,0);
						free(image); 
						settextjustify(0,2);
					    return 0;
					case 2://�ɻس����˳����뷨 ���������ģ�
						pylen=strlen(py);//��¼���볤�� 
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
					case 3://����ɾ��Ϊ0�Զ��˳����뷨 �����������ո� 
						putimage(barx1,bary1,image,0);
						free(image);
					    break;
					case 4:
						putimage(barx1,bary1,image,0);
						free(image);
						settextjustify(0,2);//�ı��Ķ��뷽ʽ���� 
						return 1;
				}
				kbget=0;
				method=-1;
			}
			else if(asc>31&&asc<127)//�ַ�����
			{
				continue;//����ѭ�� 
			}
			else if(kbget==ESC)
			{
				settextjustify(0,2);
				return 1;
			}
			memset(py,'\0',12);//�������ã���ĳ���ڴ��趨Ϊָ����ֵ �����¸�0 
			memset(str,'\0',3);
		}
		
		
	}
}

//������ѧ������ 
/***********************************************************************
FUNCTION:input_method
DESCRIPTION: �������뷨����
INPUT:x,y,str,value,py
RETURN:1:������֣�2�������ĸ��3������ո�
************************************************************************/

int input_method(int x,int y,char *str,int value,char *py)//����һ���������������ʽ ����������İ���ֵ 
{
	FILE *fp=NULL,*oldfp=NULL;//�����ļ� 
	int fJudge=FAIL;
	char *p=py;//py��p���� ����ʱ����Ҫ����ķ��������޸� 
	int trigger=1;//����ʱ���������־
	char temphz[5][3]={{'\0','\0','\0'},{'\0','\0','\0'},
	                   {'\0','\0','\0'},{'\0','\0','\0'},
					   {'\0','\0','\0'}},temp[3];//����5������Ϊ3���ַ����ַ��������ڴ��溺��
	int fposition=0;//���ο��λ���λ�ã�ƴ���ļ������λ�� 
	int hznow=0,hznum=0;//��¼��ǰ���ֵ�λ�� 
	int asc,i;
	int PyStartx=x+8,PyStarty=y+4;
	int HzStartx=x+8,HzStarty=y+22;
	char *ABpath="pinyin\\";//����ƴ��������׼·������ǰ·���µ�pinyin�ļ� 
	char pypath[45];					//����ƴ���������·��
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	strcpy(pypath,"pinyin\\");//���ļ�·������pypath 
	while(1)
	{
		if(trigger||kbhit())//��һ�ν����Զ����� �Ժ�������
		{
			clrmous(MouseX,MouseY);
			trigger=0;//����δ����״̬ 
			if(kbhit()) value=bioskey(0);//�м������룬¼��value 
			asc=value&0xff;
			/*���ⰴ������*/
			switch(value)
			{
				case ESC:
					return 4;//�������� 
				case BACK://�˸�� 
					p--;
					*p='\0';//ɾ��һ���Ѿ�����ķ��� 
					if(py[0]=='\0')//���ɾ�����ˣ��˳����� 
					{
						if(oldfp) fclose(oldfp);
						if(fp) fclose(fp);
						return 3;
					}
					break;
				case SPACE://�ո�� ���뺺�� 
					strcpy(str,temphz[hznow]);//������λ�õĺ����ַ�������str�ȴ���� 
					if(oldfp) fclose(oldfp);
					if(fp) fclose(fp);
					return 1;
				case ENTER://������룬��ӡ����Ļ�� 
					if(oldfp) fclose(oldfp);
					if(fp) fclose(fp);//�ر��Ѿ��򿪵��ļ� 
					return 2;
				case LASTLINE://���¼� 
					if(fposition>=8)//�������ض�λ�ļ�ָ��ǰ�˸��ֽڣ��ƶ��ĸ����֣� ���ĸ�����ռ��һ��ҳ�� 
					{
						fposition-=8;
					}
					break;
				case NEXTLINE:
					if(!feof(fp))//�������ض�λ�ļ�ָ���˸��ֽڣ��ĸ����֣�
					{
						fposition+=8;
					}
					break;
				case LEFT://���ƶ�һ��
					if(hznow)
					{
						hznow--;
					}
					else if(fposition>=8)//��Ҫ��ҳ
					{
						fposition-=8;
						hznow=3;
					}
					break;
				case RIGHT:
					if(hznow<hznum-1)//ͬ��
					{
						hznow++;
					}
					else if(!feof(fp))
					{
						fposition+=8;
						hznow=0;
					}
					break;
					/*�����ּ�ѡ�����뺺��*/
				case FIRST:
					strcpy(str,temphz[0]);//ѡ��һ��������Ԫ�ظ���str������� 
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
			/*�����ַ�����*/
			if(asc>31&&asc<127&&strlen(py)<MAXPY&&asc!='['&&asc!=']')    //��Ч����ʱ��λ
			{
				*p=asc;//��asc��ֵ������p�� 
				p++;//�ƶ�p����һ�� 
				fposition=0;
				hznow=0;
			}
			pyFrm(x,y,x+200,y+40);
			setfillstyle(1,WHITE);
			settextstyle(1,0,2);
			outtextxy(PyStartx,PyStarty,py);        //ƴ������
		    strcat(pypath,py);//��pinyin�ļ���·����py�ַ����� 
		    strcat(pypath,".txt");//����.TXT�ĺ�׺�� ,pypath��Ϊ�������ļ�·�� 
		    if(fJudge) //����ǰ�ļ�ָ�뱣�� ͬʱ�ر���һ���ļ�  Ϊ���������ַ�׼��
			{
				if(oldfp)
				{
					fclose(oldfp);
				}
				oldfp=fp;
			}
		    if((fp=fopen(pypath,"r"))==NULL)//�����ַ�����  ������һ���ļ��������
		    {
		    	fJudge=FAIL;
		    	fp=oldfp;
			}
			else
			{
				fJudge=SUCCESS;
			}
			if(fp)//����ֻ����ʽ�������txt�ļ� 
			{
				fseek(fp,fposition,SEEK_SET);//�ҵ�ָ��λ�õ��ļ����� 
		  		for(i=0;i<5;i++)
		    	{
		    		fread(temphz[i],2,1,fp);//����һ�����֣�������temphz�� 
		    		if(feof(fp))//�����ļ�β
		    		{
		    			hznum=i;//������˴��ļ�β���һ�� ��Ҫ��һ  Ȼ���˴�����һ��Ч������
		    			break;
					}
				}
				if(!feof(fp))//δ�����ļ�β ȫ�Ժ���
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
				puthz(HzStartx+hznow*50+16,HzStarty,temphz[hznow],16,16,CYAN);//��ʾѡ�к���
			}
		}
		strcpy(pypath,ABpath);          //����·����ԭ�������٣���ֻͣ����ƴ�����ļ��еĲ㼶 �������´�ʹ�� 
		value=0;
	}
}

/************************************************************************
FUNCTION:pyFrm
DESCRIPTION: ���뷨С��
INPUT:x1,y1,x2,y2
RETURN:��
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

int xouttextxy(int x,int y,char *s,int color)//8x16�����ֿ����� 
{
	FILE *asc=NULL;
	int i,j,k;
	char *mat,*temp;
	int len;
	long offset;
	int mask;

	len=strlen(s);//��¼s�ĳ��� 
	if(!len) return 0;//���ַ�����ִ�в���
	if((asc=fopen("HZK\\ASC16","rb"))==NULL)//�򿪺��ֿ���ļ� ���ļ�ָ��ָ��ͷ�� �������ʧ�ܾͱ��� 
	{
		closegraph();
		printf("outtextxy can't open asc16!,xouttextxy");
		delay(3000);
		exit(1);
	}
	if((mat=(char *)malloc(16*sizeof(char)*len))==NULL)//��ŵ���
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
		offset=(long)16*s[i];//�����ַ����ļ�ƫ��
		fseek(asc,offset,SEEK_SET);
		fread(temp,sizeof(char),16,asc);//�������ַ��������mat
		temp+=16;
	}
	fclose(asc);//�ر��ļ� 
	for(i=0;i<len;i++)//ͨ���ŵ���ʾ�ַ�
	{
		for(j=0;j<16;j++)
		{
			mask=0x80;
			for(k=0;k<8;k++)
			{
				if(mat[i*16+j]&mask)
				putpixel(x+8*i+k,y+j,color);//������ַ���㺯�� 
				mask>>=1;
			}
		}
	}
	free(mat);
	return len;
}

/************************************************************************
FUNCTION:itostr
DESCRIPTION: ���ֱ��
INPUT:a,s
RETURN:����s
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


