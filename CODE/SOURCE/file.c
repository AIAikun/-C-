#include<common.h>
#include"file.h"
char filename[40]={0};//����ȫ�ֱ���filename 

/**************************
	���ļ�ģ�顿
	��д�ˣ������� 
**************************/
int FreeAll(Lnode* p) //ɾ��p��������нڵ�ͽڵ� 
{
	if (p->next) 
	Freenode(p->next);  
	if (p->nextl) 
	FreeAll(p->nextl);  
	free(p);  
	return;  
}  

int Freenode(node* p)  //ɾ��p��ڵ� 
{  
	if (p->next) Freenode(p->next);  
	free(p);  
	return;  
}  

	
Lnode* opens(Lnode *Hp,Lnode **startline)  //���ļ� �ĺ��� 
{  
    FILE* fp;  //�ļ�ָ�� 
    Lnode* q1, * q2;
    node* p1, * p2; //��������ָ�룬�ڽ�����ǰ�� 
    int temp; //temp���ڽ��մ��ļ��л�õ��ַ� 
	int Hflg=0;
	int Hflg2=0; //Hflg��Hflg2�����ж��Ƿ��ǵ�һ�� 
    int count = 0; //count���ڼ�¼ĳ���Ѿ�������ַ���������Ŀ 
	int flags = 1;//������� 
	int i = 0;  
    cleardevice();//����
	drawmenu(); 		
	delcursor();//ɾ����꣬׼�������ʾ 
	puthz(30,210,"����һ���ļ���",16,16,WHITE);  
	setcolor(WHITE);
	outtextxy(140,215,"(e.g. c:\\test.c):") ;//���ļ�ʾ�� 
	gettxtname(filename,280,215);//��ȡָ��·���µ��ļ����� ����filename �������洢�� 
	setcolor(WHITE); 
    fp = fopen(filename, "r");//��ֻ����ʽ���ļ�������Ϊfilename��filename����Ҫ����  
    if (fp == NULL)//���ļ�ʧ�� 
    {   
	    cleardevice();  //����������Ļ 
		puthz(288,232,"��ʧ��", 16, 16,WHITE);
	    getch(); //�ȴ��û������ַ� 
	    drawmenu();//���»�ͼ 
	    return Hp;  //���ص�һ��ָ�� 
    }  
   else
    {  
	    FreeAll(Hp->nextl);  //�ͷſռ䣬׼�����ļ��������� �����ﴫ����Hp����һ�� ,
	    Hp->next = NULL;  //�ֶ�������һ�У���ֹ��һ��ͷ�����ʧ 
	    Hp->nextl = NULL;  
	 
	while (!feof(fp))  //��ȡ�ַ�,feof��fp���ļ���������0����֮����  ���ж��ļ��Ƿ���� ����ѭ�� 
	{  
    	count = 0; //�ַ����� 
		flags = 1;  
	    q2 = (Lnode*)malloc(sizeof(Lnode));//�½�һ���е�����
	    p1= (node*)malloc(sizeof(node)); //�½�һ���е������еĽڵ�
		q2->next = p1;
		p1->next=NULL; 
		q2->nextl = NULL; 
		if(Hflg==0)//�����ж��Ƿ����ڶ���һ�У���һ�в�����������ִ�д��в��� 
	    {
	    	Hp=q2;//��q2��Ϊ��һ�� 
	        Hflg=1;//��ʾ�Ѿ����ǵ�һ���� 
		}
		temp = fgetc(fp); 	 //��ʼ����ļ��е��ַ�
		 
	    while ((temp != 10 )&& (temp != 13)&& (count <= 600) && (!feof(fp))) //����ѭ����������ʱ���� 
		//��ѭ����������˵���ڵ�������һ�д�����ϣ���˿�ʼ����  �����е����� 
	    {    
	        if (flags == 1) //flags==1˵���ڵ�һ���ڵ�����     
			{ 
				if (temp == 0x09) //�����⵽tab������ȫ���滻�ɿո� 
	            {  
	            	p1->txt[0] = ' '; //�ӵ�һ�е�һ���ڵ㿪ʼ 
					p1->txt[1]='\0';
	 			    p1->sign=0;//��¼Ϊ�ַ�״̬ 
	 			    count+=8;//�����Ѿ�8���ַ����� 
	                for (i = 0; i < 3; i++)  //����3���ո� 
	                {   
						p2 = (node*)malloc(sizeof(node));  //���½�һ���ڵ� 
	                	p2->txt[0] =' ';
						p2->txt[1]='\0';  
	                    p2->next = NULL;  
	                    p1->next = p2; 
						p2=p2->next; 
	                    p1 = p1->next;                     
	                    count+=8;  
	                }  
	            	temp = fgetc(fp);//��ȡ��һ�� 
	            	
	            }
				else//δ��⵽tab�� 
				{
					if((temp & 0x80)==0)//temp��0x80���룬����ֵΪ0����ʾ�Ƿ������ַ� 
					{
						p1->txt[0] = temp;  
				        p1->txt[1]='\0';
				        p1->sign=0;
				        p1->flag=WHITE;
			         	p1->next = NULL;  
			         	count+=8;
					}
					else if((temp & 0x80)!=0)//��ֵ��Ϊ0����ʾ�������ַ� 
					{
						p1->txt[0]=temp;			        						
						temp = fgetc(fp);
						p1->txt[1]=temp;
						p1->txt[2]='\0';				        												
						p1->sign=1;
			        	p1->next = NULL;  
			        	count+=16;  //һ�������ַ�ռ�����ֽ� 
					}
					temp = fgetc(fp);//�ض�		
				}
				flags=0; //��ǲ��ڵ�һ�� 
			}
			else if(flags==0) //���ڵ�һ���ڵ����� 
	        {
		
	        	if (temp == 0x09) /*�����⵽tab������ȫ���滻�ɿո�*/  
	            {  
	            	p2 = (node*)malloc(sizeof(node));
	                for (i = 0; i < 4; i++)  //4���ո�� 
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
	            	temp = fgetc(fp);//���� 
	            }  
	            else 
	            {
					if((temp & 0x80)==0)//temp��0x80���룬����ֵΪ0����ʾ�Ƿ������ַ� 
					{
						p2 = (node*)malloc(sizeof(node));
						p2->txt[0] = temp;  
				        p2->txt[1]='\0';
				        p2->sign=0;
				        p2->flag=WHITE;
			         	p2->next = NULL;  
			         	p1->next = p2; 
						p1 = p2; //���ؽ�����ʵ�ֵ��� 
			         	count+=8;
					}
					else if((temp & 0x80)!=0)//��ֵ��Ϊ0����ʾ�������ַ� 
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
			        	count+=16;  //һ�������ַ�ռ�����ֽ� 
					}
					temp = fgetc(fp);
		    	}  
	        } 
		}
		if(count==0)//���У�p1δ�䶯 
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
				q1 = q2; //�еĵ��ƹ�ϵ 
			}		 
			
		}
	    if (count > 0)  //һ�н����Ҳ��ǿ��� ��p1��ʱ����β 
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
				q1 = q2; //�еĵ��ƹ�ϵ 
			}		 
	    }  
      }
    view(Hp);//��������ʾ�ڿ����뷶Χ�� 	
	*startline=Hp;	//startlineָ�������ͷ 
	return Hp;
	}
}

/************************************************************************
������newbuild
���ܣ��½�һ���ļ���ͨ�� fp = fopen(filename, "wb+")ʵ��
      ��������ļ��Ѵ��ڣ�����ʾ���ļ����ڣ���ֱ�Ӵ򿪴��ļ� 
����������Lnode*Hp 
************************************************************************/	     
int newbuild(Lnode* Hp,Lnode **startline) 
{  
    FILE* fp;  
    Lnode* q1, * q2;
    node* p1, * p2;  
    int temp;
	int Hflg=0;
	int Hflg2=0; //Hflg��Hflg2�����ж��Ƿ��ǵ�һ�� 
    int count = 0; 
	int flags = 1;
	int i = 0;  
    cleardevice();//����
	drawmenu(); 		
	delcursor();//ɾ����꣬׼�������ʾ 
	puthz(30,210,"�����������½��ļ����ļ���",16,16,WHITE);  
	setcolor(WHITE);
	outtextxy(241, 215, ":");
	gettxtname(filename,250,215);
	setcolor(WHITE); 
    fp = fopen(filename, "r");//�ﵽ"��û������ļ�������һ���ļ�"��Ŀ��
if (fp == NULL)//�����ڸ��ļ� 
    {   
	    cleardevice();//����
		drawmenu(); 		  
		setcolor(WHITE);  
    	fp = fopen(filename, "wb+");//�ö�д��һ���������ļ��ļ�		 
    }  
else//�ļ��Ѿ����� ����ȡ 
	{  
	    cleardevice();//����
		drawmenu(); 		
		delcursor();//ɾ����꣬׼�������ʾ 
		setcolor(WHITE);
		puthz(222,202,"�½�ʧ��",16,16,WHITE);
		puthz(222,218,"��Ϊ���ļ��Ѿ�����",16,16,WHITE);
		puthz(222,234,"����Ϊ���򿪸��ļ�",16,16,WHITE);
		puthz(222,250,"���Ժ�",16,16,WHITE);
		outtextxy(270,254,".");
		delay(500); 
		outtextxy(286,254,".");
		delay(500);
		outtextxy(302,254,".");
		delay(500);
		outtextxy(318,254,".");
		delay(500);//��ʱ����ʾ�����ļ� 
	    fp = fopen(filename, "r");//��ֻ����ʽ���ļ���filename����Ҫ����  
		FreeAll(Hp->nextl);   
		Hp->next = NULL;  
		Hp->nextl = NULL;  
	while (!feof(fp))  //��ȡ�ַ�,feof��fp���ļ���������0����֮����  ���ж��ļ��Ƿ���� ����ѭ�� 
	{  
    	count = 0; //�ַ����� 
		flags = 1;  
	    q2 = (Lnode*)malloc(sizeof(Lnode));//�½�һ���е�����
	    p1= (node*)malloc(sizeof(node)); //�½�һ���е������еĽڵ�
		q2->next = p1;
		p1->next=NULL; 
		q2->nextl = NULL; 
		if(Hflg==0)//�����ж��Ƿ����ڶ���һ�У���һ�в�����������ִ�д��в��� 
	    {
	    	Hp=q2;//��q2��Ϊ��һ�� 
	        Hflg=1;//��ʾ�Ѿ����ǵ�һ���� 
		}
		temp = fgetc(fp); 	 //��ʼ����ļ��е��ַ�
		 
	   while ((temp != 10 )&& (temp != 13)&& (count <= 600) && (!feof(fp))) //����ѭ����������ʱ���� 
		//��ѭ����������˵���ڵ�������һ�д�����ϣ���˿�ʼ����  �����е����� 
	    {    
	        if (flags == 1) //flags==1˵���ڵ�һ���ڵ�����     
			{ 
				if (temp == 0x09) //�����⵽tab������ȫ���滻�ɿո� 
	            {  
	            	p1->txt[0] = ' '; //�ӵ�һ�е�һ���ڵ㿪ʼ 
					p1->txt[1]='\0';
	 			    p1->sign=0;//��¼Ϊ�ַ�״̬ 
	 			    count+=8;//�����Ѿ�8���ַ����� 
	                for (i = 0; i < 3; i++)  //����3���ո� 
	                {   
						p2 = (node*)malloc(sizeof(node));  //���½�һ���ڵ� 
	                	p2->txt[0] =' ';
						p2->txt[1]='\0';  
	                    p2->next = NULL;  
	                    p1->next = p2; 
						p2=p2->next; 
	                    p1 = p1->next;                     
	                    count+=8;  
	                }  
	            	temp = fgetc(fp);//��ȡ��һ�� 
	            	
	            }
				else//δ��⵽tab�� 
				{
					if((temp & 0x80)==0)//temp��0x80���룬����ֵΪ0����ʾ�Ƿ������ַ� 
					{
						p1->txt[0] = temp;  
				        p1->txt[1]='\0';
				        p1->sign=0;
				        p1->flag=WHITE;
			         	p1->next = NULL;  
			         	count+=8;
					}
					else if((temp & 0x80)!=0)//��ֵ��Ϊ0����ʾ�������ַ� 
					{
						p1->txt[0]=temp;			        						
						temp = fgetc(fp);
						p1->txt[1]=temp;
						p1->txt[2]='\0';				        												
						p1->sign=1;
			        	p1->next = NULL;  
			        	count+=16;  //һ�������ַ�ռ�����ֽ� 
					}
					temp = fgetc(fp);//�ض�		
				}
				flags=0; //��ǲ��ڵ�һ�� 
			}
			else if(flags==0) //���ڵ�һ���ڵ����� 
	        {
		
	        	if (temp == 0x09) /*�����⵽tab������ȫ���滻�ɿո�*/  
	            {  
	            	p2 = (node*)malloc(sizeof(node));
	                for (i = 0; i < 4; i++)  //4���ո�� 
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
	            	temp = fgetc(fp);//���� 
	            }  
	            else 
	            {
					if((temp & 0x80)==0)//temp��0x80���룬����ֵΪ0����ʾ�Ƿ������ַ� 
					{
						p2 = (node*)malloc(sizeof(node));
						p2->txt[0] = temp;  
				        p2->txt[1]='\0';
				        p2->sign=0;
				        p2->flag=WHITE;
			         	p2->next = NULL;  
			         	p1->next = p2; 
						p1 = p2; //���ؽ�����ʵ�ֵ��� 
			         	count+=8;
					}
					else if((temp & 0x80)!=0)//��ֵ��Ϊ0����ʾ�������ַ� 
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
			        	count+=16;  //һ�������ַ�ռ�����ֽ� 
					}
					temp = fgetc(fp);
		    	}  
	        } 
		}
		if(count==0)//���У�p1δ�䶯 
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
				q1 = q2; //�еĵ��ƹ�ϵ 
			}		 
		}
	    if (count > 0)  //һ�н����Ҳ��ǿ��� ��p1��ʱ����β 
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
				q1 = q2; //�еĵ��ƹ�ϵ 
			}
				 
	    }  
	    
	}
	 view(Hp);//��������ʾ�ڿ����뷶Χ�� 	
	*startline=Hp;	//startlineָ�������ͷ 
  }
}
/************************************************************************
������save 
���ܣ����޸ĵ��ַ�������������޸������Դﵽ�����ļ���Ŀ�� 
����������Lnode*Hp 
************************************************************************/
int save(Lnode* Hp)  
{ 
	FILE* fp;  
	Lnode* q;  
	node* p;
	q=Hp;//��һ�� 
	fp = fopen(filename, "w");//��ֻд��ʽ���Ѿ�����filename ���ļ� 
	if (fp == NULL)//���ļ�ʧ�� ���ļ���δ�½� ��filenameû���� 
    {   
	    cleardevice();  
		puthz(288,232,"��ʧ��", 16, 16,WHITE);//�������filename�����ڻ��ߴ���Żᱨ�� 
	    getch(); 
	    drawmenu();
	    return 0;  
    }
	do //���filename�ж��� 
	{
	    p = q->next; //ָ��node���͵�����
	    while (p != NULL)  
	    {  
	    	
	    	if(p->sign==0)
	        {
	        	if(p->txt[0]==13||p==NULL)
	        		fputc('\n', fp);//���з������ 
	        	else
	       	    	fprintf(fp,"%c",p->txt[0]) ;//����fprintд���ļ��� 
	      	      
	   		}
	   		else if(p->sign==1)//������� 
	   		{
	   			fprintf(fp,"%c",p->txt[0]) ;
	      	    fprintf(fp,"%c",p->txt[1]) ;//д�������ַ� 
			}
			p = p->next; //��һ�� 
			fflush(fp);//��ջ�������������������д���ļ� ȷ���������벻��Ӱ�� 
	    } 
		
	    q = q->nextl;  //һ��д���� 
	} while (q!=NULL);  

	fclose(fp); //�رմ��ļ�
	view(Hp);
 
    return; 

}

 //���Ϊ���� 
int saveas(Lnode* Hp)  
{  
    FILE* fp;  
	Lnode* q;  
	node* p;  
	char newname[15];//�ļ��� 
	setfillstyle(1, BLUE); 
	bar(17,25,623,455);
	puthz(30,210,"�������������Ϊ�ļ����ļ���",16,16,WHITE);  
	setcolor(WHITE);
	outtextxy(255, 215, ":");
	gettxtname(newname,265,215); 
	q=Hp;
	//ͨ�������޸����� 
	fp = fopen(newname, "w");//��ֻд��ʽ���ļ� �������ļ��������д�룬�������򴴽���д�� 
	if (fp == NULL)//���ļ�ʧ�� ��newname ������ 
    {   
	    cleardevice();  
		puthz(288,232,"��ʧ��", 16, 16,WHITE);
	    getch(); 
	    drawmenu();
	    return 0;  
    }
	do //д����ļ��� 
	{
	    p = q->next; 
	    while (p != NULL)  
	    {  
	    	
	    	if(p->sign==0)
	        {
	        	if(p->txt[0]==13)
	        		fputc('\n', fp);//���ļ�ָ�붨λ�ļ� 
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
	fclose(fp); //�رմ��ļ�
	view(Hp);
    return; 
}  

