#ifndef _GAME_H_
#define _GAME_H_

#define CIMA 'w'
#define BAIXO 's'
#define ESQUERDA 'a'
#define DIREITA 'd'
#define BOMBA 'b'

int acabou();
void fantasmas();
int direcaofantasma(int xatual, int yatual, int* xdestino, int* ydestino);
void explodepilula();
void explosaopilula(int x, int y, int direcaox, int direcaoy, int qntd);

#endif