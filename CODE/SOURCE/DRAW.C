#include<common.h>
#include<draw.h>
/**************************
	【画图模块】
	编写人：贾沫晗
**************************/
void drawmenu()
{
	cleardevice();
	setbkcolor(BLUE);
	setfillstyle(1, LIGHTGRAY);
	bar(1, 1, 640,24);
	bar(1, 456, 640, 480);
	bar(1, 1, 10, 480);
	bar(97,1,177,24);
	bar(274,1,354,24);
	bar(451,1,533,24);
	//bar(624, 25, 640, 455);
	setcolor(DARKGRAY);
	line(97,1,97,24);
    line(177,1,177,24);
    line(274,1,274,24);
    line(354,1,354,24);
    line(451,1,451,24);
    line(531,1,531,24);
	setcolor(RED);
    line(618,7,630,19);
    line(618,19,630,7);
	puthz(121,5,"文件", 16, 16,DARKGRAY);
	puthz(210,5,"编译",16, 16,DARKGRAY);
	puthz(298,5,"编辑", 16, 16,DARKGRAY);
	puthz(386,5,"视图", 16, 16,DARKGRAY);
	puthz(475,5,"帮助", 16, 16,DARKGRAY);
	puthz(24,458,"行", 16, 16,DARKGRAY);
    puthz(100,458,"列", 16, 16,DARKGRAY);
}

void drawfile()    //点击“文件”显示的子菜单 
{
    setcolor(LIGHTGRAY);
    bar(97,25,177,140);
    setcolor(DARKGRAY);
    line(97,25,177,25);//新建按钮 
    line(97,48,177,48);//打开按钮 
    line(97,71,177,71);//保存按钮 
    line(97,94,177,94);//另存为按钮 
	line(97, 117, 177, 117);//退出按钮
    puthz(121,29,"新建", 16, 16,DARKGRAY);
    puthz(121,52,"打开", 16, 16,DARKGRAY);
    puthz(121,75,"保存", 16, 16,DARKGRAY);
    puthz(117,98,"另存为", 16, 16,DARKGRAY);
	puthz(121, 121, "退出", 16, 16, DARKGRAY);
}

void drawedit()//点击“编辑”显示的子菜单
{
    setcolor(LIGHTGRAY);
    bar(274,25,354,163);
    setcolor(DARKGRAY);
    line(274,25,354,25);//复制按钮 
    line(274,48,354,48);//粘贴按钮 
    line(274,71,354,71);//替换按钮 
    line(274,94,354,94);//查找按钮 
    line(274,117,354,117);//剪切按钮 
	line(274, 140, 354, 140);//退出按钮
    puthz(298,29,"复制", 16, 16,DARKGRAY);
    puthz(298,52,"粘贴", 16, 16,DARKGRAY);
    puthz(298,75,"替换", 16, 16,DARKGRAY);
    puthz(298,98,"查找", 16, 16,DARKGRAY);
    puthz(298,121,"剪切", 16, 16,DARKGRAY);
	puthz(298, 144, "退出", 16, 16, DARKGRAY);
 } 
 
 void drawhelp()    //点击“帮助”显示的子菜单 
{
    setcolor(LIGHTGRAY);
    bar(451,25,531,94);
    setcolor(DARKGRAY);
    line(451,25,531,25);//关于按钮 
    line(451,48,531,48);//帮助按钮 
	line(451, 71, 531, 71);//退出按钮
    puthz(475,29,"帮助",16, 16,DARKGRAY);
    puthz(475,52,"关于", 16, 16,DARKGRAY);
	puthz(475, 75, "退出", 16, 16, DARKGRAY);
} 
 void drawview()    //点击“视图”显示的子菜单
 {
	 setcolor(LIGHTGRAY);
	 bar(386, 25, 451, 94);
	 setcolor(DARKGRAY);
	 line(386, 25, 451, 25);//全屏按钮 
	 line(386, 48, 451, 48);//放大按钮 
	 line(386, 71, 451, 71);//缩小按钮 
	 line(386, 94, 451, 94);//退出按钮 
	 puthz(410, 29, "全屏", 16, 16, DARKGRAY);
	 puthz(410, 52, "放大", 16, 16, DARKGRAY);
	 puthz(410, 75, "缩小", 16, 16, DARKGRAY);
 }
 void drawcompile()    //点击“编译”显示的子菜单
 {
	 setcolor(LIGHTGRAY);
	 bar(210, 25, 274, 94);
	 setcolor(DARKGRAY);
	 line(210, 25, 274, 25);//编译按钮 
	 line(210, 48, 274, 48);//运行按钮 
	 line(210, 71, 274, 71);//调试按钮 
	 line(210, 94, 274, 94);//退出按钮 
	 puthz(234, 29, "编译", 16, 16, DARKGRAY);
	 puthz(234, 52, "运行", 16, 16, DARKGRAY);
	 puthz(234, 75, "调试", 16, 16, DARKGRAY);
 }
void drawrc(int r, int c)//显示行数和列数
{
	char row[3];
	char col[3];
	itoa(r,row,10);
	itoa(c,col,10);
	setfillstyle(1, LIGHTGRAY);
	bar(40, 458, 90, 474);
	bar(116, 458, 166, 474);
	settextstyle(0,0,1);
	setcolor(WHITE);
	outtextxy(48,464,row);
	outtextxy(124,464,col);
}

void drawwin(int x,int y)//鼠标右键点击时显示的复制剪切粘贴
{
	setfillstyle(1, LIGHTGRAY);
	bar(x,y,x+63,y+51);
	setcolor(DARKGRAY);
	line(x,y,x+63,y);
	line(x+63,y,x+63,y+51);
	line(x,y+51,x+63,y+51);
	line(x,y,x,y+51);
	line(x,y+17,x+63,y+17);
	line(x,y+34,x+63,y+34);
	puthz(x+16,y+1,"复制", 16, 16,DARKGRAY);
	puthz(x+16,y+18,"剪切", 16, 16,DARKGRAY);
	puthz(x+16,y+35,"粘贴", 16, 16,DARKGRAY);
	
}

void full_skbar()//画一个全覆盖的拖动条 
{
	setfillstyle(1, LIGHTGRAY);
	bar(628,25,640,41);//上移按钮 
	bar(628,440,640,456);//下移按钮 
	setcolor(WHITE);
	line(634,25,628,33);
	line(634,25,640,33);
	line(634,25,634,41);//组成向上箭头
	line(634,456,628,448);
	line(634,456,640,448);
	line(634,456,634,440);//组成向下箭头 
	setfillstyle(1, DARKGRAY);
	bar(628,41,640,440);//拖动条占满预留位置 	
}


