#include<common.h>
 
/**************
��main������
��д�ˣ���ĭ��
**************/



void main()
{   


	int gd=VGA;
	int gm=VGAHI;
	initgraph(&gd,&gm,"C:\\BORLANDC\\BGI");
	cleardevice();
	mouseinit();//������ 
	mainloop();//������ѭ�� 
	return 0;
}
