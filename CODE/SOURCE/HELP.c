#include<common.h>
#include<HELP.h>
/**************************
	����ͼģ�顿
	��д�ˣ���ĭ��
	�ð�鱣���˺���bc�İ������ܣ���ʾ���������Ҫ����
**************************/


void help()//����
{	
	int i;	
	delcursor();
	cleardevice();
	setfillstyle(1, WHITE);
	bar(0,0,640,480);
	setfillstyle(1, DARKGRAY);
	bar(5,5,61,45);
	puthz(17,17,"����",16,16,WHITE);
	puthz(280,17,"��ӭʹ��",16,16,DARKGRAY);
	outtextxy(345,21,"BC");
	puthz(20,50,"�������Ļλ�ã����ƶ���ꣻ����˵�����ͨ������˵���������ж�Ӧ������",16,16,DARKGRAY);
	puthz(20,70,"�½������ļ���",16,16,DARKGRAY);
	puthz(49,90,"������ļ����˵����ڲ˵����е����Ӧ��ť������Ҫ�򿪻��½����ļ�·������",16,16,DARKGRAY);
	puthz(49,110,"�������ٰ��س����ɡ�",16,16,DARKGRAY);
	puthz(20,130,"�����ļ���",16,16,DARKGRAY);
	puthz(49,150,"���ļ��༭֮�󣬵���ļ��˵���������漴�ɡ�",16,16,DARKGRAY);
	puthz(20,170,"���Ϊ��",16,16,DARKGRAY);
	puthz(49,190,"����ļ��˵���������Ϊ���������Ϊ��·�����ļ������»س����ɡ�",16,16,DARKGRAY);
	puthz(20,210,"����ͨ�������ڹ��λ�������ַ�",16,16,DARKGRAY);
	puthz(20,230,"���������Ҽ����ƶ����",16,16,DARKGRAY);
	outtextxy(20,256,"CTRL+");
	puthz(60,250,"�ң�����ѡ��һ���ı�",16,16,DARKGRAY);
	outtextxy(20,276,"CTRL+X");
	puthz(68,270,"�����м���ݼ�",16,16,DARKGRAY);
	outtextxy(20,296,"CTRL+C");
	puthz(68,290,"�����Ƽ���ݼ�",16,16,DARKGRAY);
	outtextxy(20,316,"CTRL+V");
	puthz(68,310,"��ճ������ݼ�",16,16,DARKGRAY);
	puthz(20,330,"��",16,16,DARKGRAY);	
	outtextxy(36,334,"F4");
	puthz(53,330,"�����뺺������ģʽ����",16,16,DARKGRAY);	
	outtextxy(242,334,"ESC");
	puthz(270,330,"�˳�",16,16,DARKGRAY);	
	puthz(20,350,"���ң�����༭�˵�������������ҡ�������Ҫ���ҵ��ַ��������س���",16,16,DARKGRAY);
	puthz(20,370,"�滻������༭�˵�����������滻��������Ҫ�滻���ַ��������س�����",16,16,DARKGRAY);
	puthz(66,390,"�����µ��ַ��������س�����",16,16,DARKGRAY);
	puthz(20,410,"��������Ҽ����Դӵ�������ѡ���ơ�ճ�������С�",16,16,DARKGRAY);
	puthz(20,430,"Ҳ���Ե���༭�˵������ڵ���������и��ơ�ճ�������С�����",16,16,DARKGRAY);
	return;
}



void about()//����
{
	int i;
	delcursor();
	cleardevice();
	setfillstyle(1, WHITE);
	bar(0,0,640,480);
	setfillstyle(1, DARKGRAY);
	bar(5,5,61,45);
	puthz(17,17,"����",16,16,WHITE);
	puthz(235,17,"���ڴ˺���",16,16,DARKGRAY);
	outtextxy(316,22,"BorlandC++");
	puthz(395,17,"��˵��",16,16,DARKGRAY);
	puthz(20,80,"���ڴ�ͳ��",16,16,DARKGRAY);
	outtextxy(100,85,"BorlandC++"); 
	puthz(181,80,"�༭����֧������",16,16,DARKGRAY);
	puthz(20,100,"�����д�ı༭���ֲ�����һȱ��",16,16,DARKGRAY);
	puthz(20,120,"����ʵ�����ڽ�������ʾ���������ĵĹ���",16,16,DARKGRAY);
	puthz(20,140,"�����ڴ˱༭���У��û������������縴�ơ�ճ�������еȻ����༭����",16,16,DARKGRAY);
	puthz(20,160,"���ǻ�������ļ�����ز������籣�桢���Ϊ�����ļ���",16,16,DARKGRAY);
	puthz(20,180,"Ϊ��ʹ���û����������㣬���ǻ�����˲��ҹ���",16,16,DARKGRAY);
	puthz(20,220,"���⣺",16,16,DARKGRAY); 
	outtextxy(68,224,"BorlandC++");
	puthz(150,220,"�༭���ĺ���",16,16,DARKGRAY);
	puthz(20, 240, "�༶��", 16, 16, DARKGRAY);
	puthz(69, 240, "��׿��", 16, 16, DARKGRAY);
	outtextxy(118, 244, "2301");
	puthz(151, 240, "��", 16, 16, DARKGRAY);
	puthz(20,260,"С���Ա��",16,16,DARKGRAY);
	puthz(107,260,"��ĭ��",16,16,DARKGRAY);
	puthz(164,260,"������",16,16,DARKGRAY);
	return; 
 } 

