#ifndef _SEEKBAR_H_
#define _SEEKBAR_H_

void drawskbar(Lnode* Head);
int up_page(Lnode* Head,Lnode **startline);
int down_page(Lnode* Head,Lnode **startline);
int newskbar(Lnode* Head,int r);
int click_skbar(Lnode* Head,Lnode **startline);
extern int countdown; 
#endif
