#include<common.h>
 
/**************
【main函数】
编写人：贾沫晗
**************/



void main()
{   


	int gd=VGA;
	int gm=VGAHI;
	initgraph(&gd,&gm,"C:\\BORLANDC\\BGI");
	cleardevice();
	mouseinit();//鼠标更新 
	mainloop();//进入主循环 
	return 0;
}
