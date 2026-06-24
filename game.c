#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "mapa.h"
#include "mapa.c"

MAPA Mapa; //Instanciando uma struct
POSICAO heroi;

int acabou(){
    return 0;
}

void move(char direcao){
    //encontraposicaoPlayer(&Mapa, &heroi);
    moveposicaoPlayer(&Mapa, &direcao, &heroi);
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
        imprimeMapa(&Mapa);

        char comando;
        scanf(" %c", &comando);
        move(comando);
    }while(!acabou());

    liberaMapa(&Mapa);
}