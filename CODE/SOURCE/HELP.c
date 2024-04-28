#include<common.h>
#include<HELP.h>
/**************************
	【画图模块】
	编写人：贾沫晗
	该板块保存了汉化bc的帮助功能，显示该软件的主要功能
**************************/


void help()//帮助
{	
	int i;	
	delcursor();
	cleardevice();
	setfillstyle(1, WHITE);
	bar(0,0,640,480);
	setfillstyle(1, DARKGRAY);
	bar(5,5,61,45);
	puthz(17,17,"返回",16,16,WHITE);
	puthz(280,17,"欢迎使用",16,16,DARKGRAY);
	outtextxy(345,21,"BC");
	puthz(20,50,"鼠标点击屏幕位置，将移动光标；点击菜单栏，通过点击菜单弹出框进行对应操作。",16,16,DARKGRAY);
	puthz(20,70,"新建、打开文件：",16,16,DARKGRAY);
	puthz(49,90,"点击“文件”菜单，在菜单框中点击对应按钮，输入要打开或新建的文件路径及文",16,16,DARKGRAY);
	puthz(49,110,"件名，再按回车即可。",16,16,DARKGRAY);
	puthz(20,130,"保存文件：",16,16,DARKGRAY);
	puthz(49,150,"打开文件编辑之后，点击文件菜单，点击保存即可。",16,16,DARKGRAY);
	puthz(20,170,"另存为：",16,16,DARKGRAY);
	puthz(49,190,"点击文件菜单，点击另存为，输入另存为的路径与文件名按下回车即可。",16,16,DARKGRAY);
	puthz(20,210,"按普通按键：在光标位置输入字符",16,16,DARKGRAY);
	puthz(20,230,"按上下左右键：移动光标",16,16,DARKGRAY);
	outtextxy(20,256,"CTRL+");
	puthz(60,250,"右：向右选中一个文本",16,16,DARKGRAY);
	outtextxy(20,276,"CTRL+X");
	puthz(68,270,"：剪切键快捷键",16,16,DARKGRAY);
	outtextxy(20,296,"CTRL+C");
	puthz(68,290,"：复制键快捷键",16,16,DARKGRAY);
	outtextxy(20,316,"CTRL+V");
	puthz(68,310,"：粘贴键快捷键",16,16,DARKGRAY);
	puthz(20,330,"按",16,16,DARKGRAY);	
	outtextxy(36,334,"F4");
	puthz(53,330,"键进入汉字输入模式，按",16,16,DARKGRAY);	
	outtextxy(242,334,"ESC");
	puthz(270,330,"退出",16,16,DARKGRAY);	
	puthz(20,350,"查找：点击编辑菜单栏，点击“查找”，输入要查找的字符串，按回车键",16,16,DARKGRAY);
	puthz(20,370,"替换：点击编辑菜单栏，点击“替换”，输入要替换的字符串，按回车键，",16,16,DARKGRAY);
	puthz(66,390,"输入新的字符串，按回车即可",16,16,DARKGRAY);
	puthz(20,410,"单击鼠标右键可以从弹出框快捷选择复制、粘贴、剪切。",16,16,DARKGRAY);
	puthz(20,430,"也可以点击编辑菜单栏，在弹出框里进行复制、粘贴、剪切、查找",16,16,DARKGRAY);
	return;
}



void about()//关于
{
	int i;
	delcursor();
	cleardevice();
	setfillstyle(1, WHITE);
	bar(0,0,640,480);
	setfillstyle(1, DARKGRAY);
	bar(5,5,61,45);
	puthz(17,17,"返回",16,16,WHITE);
	puthz(235,17,"关于此汉化",16,16,DARKGRAY);
	outtextxy(316,22,"BorlandC++");
	puthz(395,17,"的说明",16,16,DARKGRAY);
	puthz(20,80,"鉴于传统的",16,16,DARKGRAY);
	outtextxy(100,85,"BorlandC++"); 
	puthz(181,80,"编辑器不支持中文",16,16,DARKGRAY);
	puthz(20,100,"我组编写的编辑器弥补了这一缺陷",16,16,DARKGRAY);
	puthz(20,120,"我们实现了在界面里显示和输入中文的功能",16,16,DARKGRAY);
	puthz(20,140,"另外在此编辑器中，用户可以做到诸如复制、粘贴、剪切等基本编辑操作",16,16,DARKGRAY);
	puthz(20,160,"我们还添加了文件的相关操作，如保存、另存为、打开文件等",16,16,DARKGRAY);
	puthz(20,180,"为了使得用户操作更方便，我们还添加了查找功能",16,16,DARKGRAY);
	puthz(20,220,"主题：",16,16,DARKGRAY); 
	outtextxy(68,224,"BorlandC++");
	puthz(150,220,"编辑器的汉化",16,16,DARKGRAY);
	puthz(20, 240, "班级：", 16, 16, DARKGRAY);
	puthz(69, 240, "自卓班", 16, 16, DARKGRAY);
	outtextxy(118, 244, "2301");
	puthz(151, 240, "班", 16, 16, DARKGRAY);
	puthz(20,260,"小组成员：",16,16,DARKGRAY);
	puthz(107,260,"贾沫晗",16,16,DARKGRAY);
	puthz(164,260,"桂熙严",16,16,DARKGRAY);
	return; 
 } 

