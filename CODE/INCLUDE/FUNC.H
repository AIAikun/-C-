#ifndef _FUNC_H_
#define _FUNC_H_ 

void find(Lnode*startline);
void replace(Lnode*startline);
int ctrlr(int rcdlen,Lnode*startline,char *rcd,int m,int n);
int highlight(Lnode *startline);
int changecolor(char* str,int slen,Lnode*startline);
int changeflag(int m,int n,Lnode*startline,int color);
int colorview(int m,int n,Lnode*startline); 
void paste(int m,int n,Lnode*startline,int rcdlen,int rcdflg,char*rcd) ; 
#endif
