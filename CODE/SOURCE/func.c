#include<common.h>
#include"func.h" 

/************************************
		���༭����ģ�顿
		��д�ˣ������� 
 find���ڲ��Ҳ������ʾ
 replace�����滻�ַ��� 
 ctrlr��turnp���ڴ���ѡ���ַ��Ĺ���
  highlight��changecolor��changeflagһ����ؼ��ִ������ 
************************************/ 

//���ã����Ҳ�����ض����ַ��� ,һ���п��Զ�γ��� 
void find(Lnode*startline)
{
	int i,j,k,slen,r=1,c=1;
	char row[80];//���ڴ����ÿһ��ȡ�����ַ��� 
	char *str,*s0,*s1;
	Lnode *q;
	node *p1;
	q=startline;
	str=(char*)malloc(10);//����10���ַ����� ,������ʱ����Ҫ���ҵ��ַ��� 
	setfillstyle(1, BLUE); 
	bar(17,25,623,455);//�ַ��������ɫ
	 puthz(150,200,"������Ҫ���ҵ��ַ�����", 16, 16,WHITE);
	slen=gettxtname(str,326,206)-1;//��¼�ַ������� ������ȡ����str 
	view(startline); 
	for(i=1;(q!=NULL)&&(i<=27);i++)//ѭ�����ÿ�� ��һ��ҳ���� 
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
		//�����������Ƿ���ƥ����ַ��� 
		s0=row;//��row��ַ����s0�� 
		//����������ַ�����s0���ϸı�λ��ָ���ض��ַ���һλ��s1ָ���ض��ַ���������colorvie�����ʾ���ҵ��ַ����� 
        //��str�Ƿ���s0�����ַ��� ,����str��һ�γ��ֵ�λ�� 
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
		memset(row,'\0',sizeof(row)) ;//����row 
		r++;
		q=q->nextl;
   } 
   free(str); 
}
//���ã����Ҳ��滻�ض��ַ��� 
void replace(Lnode* startline) 
{
	int i,j,k,alen,blen,c=1,r=1;
	char row[80];
	char *astr,*s0,*s1,*s2,*bstr,temp[2];//astrΪԭ�����ַ���bstrΪ���ڵ��ַ� 
	Lnode *q;
	node *p1;
	q=startline;
	astr=(char*)malloc(10);//ԭ���� 
	bstr=(char*)malloc(76);//���ڵ� 
	setfillstyle(1, BLUE); 
	bar(17,25,623,455);//�ַ��������ɫ 
	puthz(150,200,"����Ҫ�滻���ַ�����", 16, 16,WHITE);	
	alen=gettxtname(astr,326,206)-1;//��¼�ַ������� 
	bar(17,25,623,455);
	puthz(150,200,"�����µ��ַ�����", 16, 16,WHITE);
	blen=gettxtname(bstr,278,206)-1;//��¼�ַ�������
	view(startline); 
	for(i=1;(q!=NULL)&&(i<=27);i++)//ѭ�����ÿ�� 
	{
		c=1;
		p1=q->next;
		for(j=0;p1!=NULL&&p1->txt[0]!=13;j++) //ѭ�����������ݶ�������
		{
			if(p1->sign==1)//����������ִ���λʹ������ 
			{
				row[j]=p1->txt[0];
				j++;
				row[j]=p1->txt[1];
			 } 
			row[j]=p1->txt[0];
			p1=p1->next;	
		} 
		row[j]='\0';
		//�����������Ƿ���ƥ����ַ��� 
		s0=row;
		do
		{
			s1=strstr(s0,astr);//��������һ�λ�ɾ�����ʲ��ö�s0���� 
			if(s1!=NULL) 
			{
				c=s1-s0+alen+1;
				movecursor(c+1,r);
				for(k=0;k<alen;k++)//���for����ִ��ɾ��ԭ�����ַ� ,����Ϊalen 
				{
					deltext(startline,r,c);
					c--;
				}
				s2=s1+alen;
				strcpy(s1,s2);//ִ���ַ����ϵ��޸� ��row ����ɾ��ԭ�ַ��� 
				for(k=0;k<blen;k++)//�������ִ�в����е��ַ��� 
				{
					temp[0]=bstr[k];//Ϊ������insert����һ�������Ҫ�� 
					temp[1]='\0';
					insert(temp,r,c,startline);//����c��s1λ�ô� 
					c++;
				} 
				//���������ʵ�ֲ���
				 
				strcat(bstr,s1);//s1����bstr���� 
				
				strcpy(s1,bstr);//��bstr�е��ַ��s1λ�� 
				//����ʵ�������м���� 
				
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

//���ã��������ѡ��һ���ַ� ����¼�� 
int ctrlr(int rcdlen,Lnode* startline,char *rcd,int m,int n)
{
	int i;
	Lnode* q1;//��ָ��Ϊָ��һ�����ݵ�ָ�� 
	node*p1;//��ָ��Ϊָ��һ�����ݽڵ��ָ�� 
	q1=startline;//q1ָ��ǰ��ʾ����ĵ�һ�� 
	for(i=1;i<m;i++)
		q1=q1->nextl;//ѭ��ʹ��q1�ƶ�����m�� 
	p1=q1->next;//p1ָ���m�еĵ�һ�� 
	for(i=1;i<n;i++)//ѭ������n��
		{
			if(p1->sign==1)	i++;//����������֣������к���һλ (��Ϊ����ռ���� 
			p1=p1->next;
		}
	if(p1->sign==0)
	{
	rcd[rcdlen]=p1->txt[0];//rcdlen��¼�Ѿ��е��ַ����� 
	rcd[rcdlen+1]='\0';//��ʱ������ַ���Ϊ��β 
	return 0; 
     }  
     else //���� 
	 {
	 rcd[rcdlen]=p1->txt[0];
	rcd[rcdlen+1]=p1->txt[1];
	rcd[rcdlen+2]='\0';
	return 1;
   }  
 } 
 
 //���ã�ʵ��ճ������
 void paste(int m,int n,Lnode*startline,int rcdlen,int rcdflg,char*rcd) 
 {
 	int i,j,count=0;//��־�е�λ���Լ��ַ���Ŀ 
 	char bioget[3];
	Lnode* q1,*q2;//��ָ��Ϊָ���е�ָ�� 
	node*p1,*p2,*p3;//��ָ��Ϊָ��һ�����ݽڵ��ָ�� 
	q1=startline;//q1ָ��ǰ��ʾ����ĵ�һ�� 
	for(i=1;i<m;i++)
		q1=q1->nextl;//ѭ��ʹ��q1�ƶ�����m�� 
	p1=q1->next;//p1ָ���m�еĵ�һ�� 
	for(i=1;i<n-1;i++)//ѭ������n-1��,ָ���Ѿ������λ��
		{
			p1=p1->next; 
			if(p1->sign==1)	i++;	//����������֣������к���һλ (��Ϊ����ռ���� ������Ҫ��2���ַ�λ�ô����в��� 
		}//p1�ڹ�꿪ʼλ�� 
		p3=p1; 
 	if(rcdflg==1) //���������������
	{
		for(i=0;i<rcdlen;i++)
		{
			  if((rcd[i]&0x80)==0)//Ӣ���ַ�
			  {
			  	bioget[0]=rcd[i];
			  	bioget[1]='\0';
			  	insert(bioget,((cursorY-24)/16+1),((cursorX-16)/8+1),startline) ;
			  	count++;
			  	memset(bioget,'\0',sizeof(bioget));
			   } 
			   
			 else//����
			{
			 	p1=p3;
			 	
			  if(p1==NULL&&q1->next!=NULL) 
			  {
			     p1=q1->next;
			     for(j=1;j<count;j++)
			 	{
			 		p1=p1->next;
				 }//�ƶ� 
				 
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
		      
			  else if(p1==NULL&&q1->next==NULL)//��һ�������� 
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
				 }//�ƶ� 
				 
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
		q1=q1->nextl;//ѭ��ʹ��q1�ƶ�����m�� 
	p1=q1->next; 
	for(i=0;i<n-1;i++)
	{
		if(p1->sign==1)
		i++;
		p1=p1->next;
	}//����ָ���ַ�λ�� 
if(p1!=NULL)
{
   if(p1->sign==0) //�����Ӣ���ַ� 
   {
	delcursor();
	clrmous(MouseX,MouseY);
	setfillstyle(1,LIGHTGRAY);
	bar(17+8*(n-1),25+16*(m-1),24+8*(n-1),40+16*(m-1));//��ɻ�ɫ�ײ� 
	settextstyle(0,0,1);
	setcolor(WHITE);
	p1->txt[1]='\0';
	outtextxy(17+8*(n-1),31+16*(m-1),p1->txt);//���´�ӡ�ַ� 
	imgflag=0;
	save_bk_mou(MouseX,MouseY); 
	drawmous(MouseX,MouseY);
	newcursor();
  }
  else //������������ַ� 
  {
  	delcursor();
	clrmous(MouseX,MouseY);
	setfillstyle(1,LIGHTGRAY);
	bar(17+8*(n-1),25+16*(m-1),34+8*(n-1),40+16*(m-1));//��ɻ�ɫ�ײ� 
	setcolor(WHITE);
	puthz(17+8*(n-1),25+16*(m-1),p1->txt,16, 16,WHITE); 
	imgflag=0;
	save_bk_mou(MouseX,MouseY); 
	drawmous(MouseX,MouseY);
	newcursor();
  }
}
else if(p1==NULL)//����ĩβ 
{
    delcursor();
	clrmous(MouseX,MouseY);
	imgflag=0;
	save_bk_mou(MouseX,MouseY); 
	drawmous(MouseX,MouseY);
	newcursor();
}
}

 

//����ִ��ѭ�������� 
int highlight(Lnode *startline)
{	//���屣���� 
	static char* c[32]={"long","short","float","double","char",
	"unsigned","signed","const","void","volatile","enum",
	"struct","union","if","else","goto","switch","case",
	"do","while","for","continue","break","return","default",
	"typedef","auto","register","extern","static","sizeof","int",};
	static int clen[32]={4,5,5,6,4,8,6,5,4,8,4,6,5,2,4,4,6,4,2,5,3,8,5,6,7,7,4,8,6,6,6,3};//��¼���б����ַ��ĳ��� 
	int i,sig;
	for(i=0;i<32;i++)
		sig=changecolor(c[i],clen[i],startline);//ѭ���������еı����� 
	return sig;
}


//���ڲ��Ҳ��ı��ַ�������ɫ 
int changecolor(char* str,int slen,Lnode *startline)
{
	int i,j,k,c=1,r=1,sig=1;
	char row[80];
	char *s0,*s1,ch1,ch2;//ch1,ch2���ڼ�¼������ǰ��ͺ�����ַ��жϱ������Ƿ񵥶����� 
	Lnode *q;
	node *p1;
	q=startline;
	for(i=1;(q!=NULL)&&(i<=27);i++)//ѭ�����ÿ�� 
	{
		c=1;
		p1=q->next;
		for(j=0;p1!=NULL;j++) //ѭ�����������ݶ�������
		{
			if(p1->sign==1)//����������ִ���λʹ������ 
			{
				row[j]=p1->txt[0];
				j++;
				row[j]=p1->txt[1];
			 } 
			row[j]=p1->txt[0];
			p1=p1->next;	
		} 
		row[j]='\0';
		//�����������Ƿ���ƥ����ַ��� 
		s0=row;
		//���ҹ̶����ַ�����s0���ϸı�λ��ָ���ض��ַ���һλ��s1ָ���ض��ַ��� 
		do
		{
			s1=strstr(s0,str);
			c=c+(s1-s0);
			if(s1!=NULL) //������ҵ�
			{ 
				ch1=*(s1-1);//ǰһ���ַ� 
				ch2=*(s1+slen);//��һ���ַ� 
				//���������Ƿ񵥶����� 
				if(!((ch1>='0'&&ch1<='9')||(ch1>='A'&&ch2<='Z')||(ch1>='a'&&ch1<='z')||(ch1=='_')||
				(ch2>='0'&&ch2<='9')||(ch2>='A'&&ch2<='Z')||(ch2>='a'&&ch2<='z')||(ch2=='_')))//���ǰ����ߺ���û���ַ�����ֻ�пո� 
				{
					for(k=0;k<slen;k++)
					{
						changeflag(r,c,startline,YELLOW);
						c++;//ʵ�ִ������ 
					}
					sig=0;//��ʾ�Ѿ����� 
				}
				else
				{
					for(k=0;k<slen;k++)
					{
						changeflag(r,c,startline,WHITE);
						c++;//���� ��Ϊ��ɫ 
					}
					sig=0;
				}
			} 
			s0=s1+slen;//�ټ��һ�� 
			
		}while(s1!=NULL);
		r++;
		q=q->nextl;
	}
	return sig;//���ر�ǣ�0��ʾ�Ѿ����� ���� 
}	

//���ã��ı�m��n�е���ɫ	  
int changeflag(int m,int n,Lnode *startline,int color)
{
	int i,j;
	Lnode* q1;//��ָ��Ϊָ��һ�����ݵ�ָ�� 
	node*p1;//��ָ��Ϊָ��һ�����ݽڵ��ָ�� 
	q1=startline;//q1ָ��ǰ��ʾ����ĵ�һ�� 
	for(i=1;i<m;i++)
		q1=q1->nextl;//ѭ��ʹ��q1�ƶ�����m�� 
	p1=q1->next;//p1ָ���m�еĵ�һ�� 
	for(i=1;i<n;i++)//ѭ������n��
	{
		p1=p1->next;
		if(p1->sign==1)	i++;	//����������֣������к���һλ (��Ϊ����ռ���� 
	}
	p1->flag=color;
 } 

