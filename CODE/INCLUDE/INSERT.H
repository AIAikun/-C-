#ifndef _INSERT_H_
#define _INSERT_H_

int insert(char* bioget,int m,int n,Lnode* startline);
void enter(int m,int n,Lnode* startline);
int deltext(Lnode* Chead,int r,int c);
int del(int flg,node* p);
int movepic(int x1,int y1,int l,int x2);
int getlen(node* p);
void match(char* bioget,Lnode* Chead);
int getlinelen(Lnode *q); 
node* endofline(Lnode*q);
node*lastendline(Lnode*q);
int getline(Lnode*q); 
#endif 
