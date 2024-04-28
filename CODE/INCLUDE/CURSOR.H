#ifndef _CURSOR_H_
#define _CURSOR_H_

void drawcursor();
void delcursor();
void movecursor(int x,int y);
void getcsim();
void newcursor();
extern int cursorX;
extern int cursorY; 
extern char bitmap[30];
extern int imgflag;
#endif