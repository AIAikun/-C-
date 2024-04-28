#ifndef _MAINLOOP_H_
#define _MAINLOOP_H_

void mainloop();
int chosedit(Lnode* startline,char* bioget,char *rcd);
int chosfile(Lnode **Head,Lnode **startline);
int choshelp();
void choscompile(Lnode* Head);
void chosview(Lnode* Head);
 
#endif
