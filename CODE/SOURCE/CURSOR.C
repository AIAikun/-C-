#include<common.h>
#include<cursor.h>
int cursorX=17;
int cursorY=25;
char bitmap[30];//用于储存光标的图像 
int imgflag=0;

/****************************
【光标模块】
编写人：贾沫晗
drawcursor用于绘制光标
getcsim用于保存光标下的图像防止留痕
delcursor用于删除当前光标
newcursor用于更新光标
movecursor用于将光标移动到第y行x列的位置
************************/

void drawcursor()    //光标绘制函数 
{
	static int i=0;//循环检测,画出白线和蓝线，白线显示光标，蓝线删除光标 。 
	setlinestyle(0,0,1);
	//画白线
	if(i<50)       
	{
	setcolor(WHITE);
	line(cursorX,cursorY,cursorX,cursorY+16);
	}
	//画蓝线
	if(i==50) putimage(cursorX,cursorY,bitmap,0);\
	//画出一次白线和蓝线后，i清零，重新开始循环
	if(i==100) i=0;
	i++;
}

//删除当前光标
void delcursor()
{
	putimage(cursorX,cursorY,bitmap,0);
}

//用于获取光标处的图像
void getcsim() 
{
	getimage(cursorX,cursorY,cursorX,cursorY+16,bitmap);
} 

//更新光标 
void newcursor()
{
	if(imgflag==0)//如果还没有储存光标的图像，就储存，防止光标掩盖屏幕内容 
	{	
		clrmous(MouseX,MouseY);
		getcsim();
		save_bk_mou(MouseX,MouseY); 
		drawmous(MouseX,MouseY);
		imgflag=1;
	}
	drawcursor();//绘制光标 
}

//移动光标到x列,y行 
void movecursor(int x,int y)
{
	delcursor();
	cursorX=17+8*(x-1);
	cursorY=25+16*(y-1);
	imgflag=0;
}

