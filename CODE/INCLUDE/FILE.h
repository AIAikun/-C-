#ifndef _FILE_H_
#define _FILE_H_

int save(Lnode* Hp);
int saveas(Lnode* Hp);
int FreeAll(Lnode* p);
int Freenode(node* p) ;
Lnode* opens(Lnode* Hp,Lnode **startline);
int newbuild(Lnode* Hp,Lnode **startline);
#endif
