#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "mapa.h"
#include "mapa.c"
#include "ui.h"
#include "ui.c"

MAPA Mapa; //Instanciando uma struct
POSICAO heroi;
int Pilula = 0;
int Fantasmas_no_Mapa = 2;

int direcaofantasma(int xatual, int yatual, int* xdestino, int* ydestino){
    int opcoes[4][2] = {
        {xatual, yatual+1},
        {xatual+1, yatual},
        {xatual, yatual-1},
        {xatual-1, yatual}
    };

    srand(time(0));
    int valido = 0;
    for(int i = 0; i < 10; i++){
        int posicao = rand() % 4;
        if(posicaovalida(&Mapa, opcoes[posicao][0], opcoes[posicao][1])){
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];
            return 1;
            //valido = 1;
        }
    }
    return 0;
}

void fantasmas(){
    /*MAPA copia;
    copiaMapa(&Mapa, &copia);*/
    int fantasmas = 1;
    for(int i = 0; i < Mapa.linhas; i++){
        for(int j = 0; j < Mapa.colunas; j++){
            if(Mapa.matriz[i][j] == FANTASMA){
                int xdestino;
                int ydestino;
                int encontrou = direcaofantasma(i, j, &xdestino, &ydestino);
                if(encontrou){
                    movimentaFantasma(&Mapa, i, j, xdestino, ydestino);
                    fantasmas++;
                    if(fantasmas > Fantasmas_no_Mapa)
                        return;
                }
            }
        }
    }
    //liberaMapa(&copia);
}

int acabou(){
    int heroivivo = encontraposicaoPlayer(&Mapa, &heroi);
    return !heroivivo;
}

void move(char direcao){
    //encontraposicaoPlayer(&Mapa, &heroi);
    moveposicaoPlayer(&Mapa, &direcao, &heroi, &Pilula);
}

void explodepilula(){
    if(!Pilula)
        return;
    explosaopilula(heroi.x, heroi.y, 0, 1, 3);
    explosaopilula(heroi.x, heroi.y, 0, -1, 3);
    explosaopilula(heroi.x, heroi.y, 1, 0, 3);
    explosaopilula(heroi.x, heroi.y, -1, 0, 3);

    Pilula = 0;
}

void explosaopilula(int x, int y, int direcaox, int direcaoy, int qntd){
    int novox = x + direcaox;
    int novoy = y + direcaoy;
    if(!posicaovalidaexplosao(&Mapa, novox, novoy))
        return;
    if(qntd == 0)
        return;
    Mapa.matriz[novox][novoy] = VAZIO;
    explosaopilula(novox, novoy, direcaox, direcaoy, qntd-1);//Função recursiva é uma função que chama ela mesma       
}

int main(){
    //char Mapa[5][10+1]; //Matriz 5 x 10 o +1 é por causa da posição final que tem o /0 indicando que é o final
    //Mapa[0][0] = '|'; //Primeiro endereço matriz
    //Mapa[4][9] = '@'; //Ultimo endereço matriz
    //printf("%c %c", Mapa[0][0], Mapa[4][9]);

    //int* v = malloc(sizeof(int) * 50); //declarando uma variavel V cujo tamanho a ser alocado será definido
                                         //dinamicamente, utilizando o malloc para alocar e o sizeof com o int
                                         //para entender o quanto de memoria alocar para esta variavel
                                         //podemos também multiplicar por um valor quando queremos alocar memoria
                                         //para um array, no exemplo um array de 50 posições

    //*v = 10;                         //Utilizando o * para acessar o valor do ponteiro

    //int** v = malloc(sizeof(int*) * 5); //Adicionando ** você consegue declarar uma matriz ou seja um ponteiro de
                                         //ponteiros, adicionando tambem o * no int dentro do malloc sizeof
                                         //garantimos agora que seja reservado o tamanho de cada ponteiro e não
                                         //somente de um int multiplicado pelo numero 5 

    /*for(int i = 0; i < 5; i++){
        v[i] = malloc(sizeof(int) * 10); //Agora com o loop podemos percorrer cada ponteiro dessa matriz e alocar
                                         //a memoria necessaria que precisamos para cada ponteiro, no caso 10 (colunas)
    }*/

    //v[0] = 10;
    //v[1] = 15;

    //v[0][0] = 10;
    //v[1][2] = 12;

    //printf("inteiro(s) alocado %d %d\n", v[0][0], v[1][2]);

    /*for(int i = 0; i < 5; i++){
        free(v[i]);               //Percorrendo cada ponteiro da matriz que havia sido alocado memoria para liberar
    }

    free(v);*/                    //Liberando a memoria alocada com o free e apontando a variavel

    leMapa(&Mapa);
    encontraposicaoPlayer(&Mapa, &heroi);

    do{
        printf("Tem pilula: %s\n", (Pilula ? "SIM" : "NAO"));
        imprimeMapa(&Mapa);

        char comando;
        scanf(" %c", &comando);
        move(comando);
        if(comando == BOMBA)
            explodepilula();

        fantasmas();
    }while(!acabou());

    liberaMapa(&Mapa);
}