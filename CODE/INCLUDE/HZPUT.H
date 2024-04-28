#ifndef _HZPUT_H_
#define _HZPUT_H_

int hz_put(int cursorX,int cursorY,int m,int n,Lnode* startline);
int input_method(int x,int y,char *str,int value,char *py);
void pyFrm(int x1,int y1,int x2,int y2);
char *itostr(int a,char *s);
int xouttextxy(int x,int y,char *s,int color);
int hz_input(int x1,int y1,int x2,int y2,char *s,int len,int color,int color2, int size);
#endif
