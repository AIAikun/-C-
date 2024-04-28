#ifndef __INIT_H__  
#define __INIT_H__  
#define LEFT 0x4b00   /*←：光标左移*/   
#define RIGHT 0x4d00  /*→：光标右移*/  
#define DOWN 0x5000    /*↓：光标下移*/
#define UP 0x4800     /*↑：光标上移*/  
#define ESC 0x011b    /*ESC键：取消菜单打开操作*/  
#define ENTER 0x1c0d  /*回车键：换行*/
#define TAB 0x0f09    /*TAB键：插入四个空格*/  
#define DEL 21248     /*DEL键：删除当前字符*/  
#define BACK 3592     /*BackSpace键：删除当前光标位置前一个字符*/   
#define CL 29440      /*ctrl+←键：从右至左，选定文本*/ 
#define CR 29696      /*ctrl+→键：从左到右，选定文本*/    
#define Cc 11779      /*ctrl+c 键：将选定文本，复制一份到剪贴板中*/  
#define Cv 12054      /*ctrl+v 键：将剪贴板中的内容复制到当前位置*/  
#define Cx 11544      /*ctrl+x 键：对选定文本，执行剪切操作*/  
#define F1 15104       /*F1键：打开文件菜单*/  
#define F2 15360      /*F2键：打开编辑菜单*/ 
#define F3 15616      /*F3键：打开帮助菜单*/  
#define F4 15872      /*F4键：汉化菜单*/   
#define F10 17408     /*F10键:刷新*/
#define SPACE 0x3920	//空格键 
#define FIRST 0x0231
#define SECOND 0x0332
#define THIRD 0x0433
#define FOURTH 0x0534
#define FIFTH 0x00635
#define SIXTH 0x0736
#define SEVENTH 0x0837
#define EIGHTH 0x0938
#define NINTH 0x0A39
#define ZIERO 0x0B30
#define MAXPY 7
#define SUCCESS 1
#define FAIL 0
#define LASTLINE 0x4800
#define NEXTLINE 0x5000
#define kuandu 600

typedef struct node
{	
	char txt[3];
	int flag;//颜色 
	unsigned short sign;		//用于指示节点储存的是中文还是英文：英文为0，汉字为1。
	struct node*next;
}node;

typedef struct Lnode
{
	node* next;
	struct Lnode*nextl;
}Lnode;


#endif 
