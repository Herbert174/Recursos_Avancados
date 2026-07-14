extern int Fantasmas_no_Mapa;

void liberaMapa(MAPA* Mapa){
    for(int i = 0; i < (*Mapa).linhas; i++){  //(*Mapa).linhas ou Mapa->linhas ambos funcionam para acessar o valor
                                              //da struct de um ponteiro
            free(Mapa->matriz[i]);
        }
    free(Mapa->matriz); //Mapa.matriz acessando a matriz presente dentro da struct Mapa
}

void alocaMapa(MAPA* Mapa){
    Mapa->matriz = malloc(sizeof(char*) * Mapa->linhas); //Alocando para a matriz a memoria necessária para conter todos ponteiros
                                           //presentes no mapa, que são a quantidade de linhas

    for(int i = 0; i < Mapa->linhas; i++){
        Mapa->matriz[i] = malloc(sizeof(char) * (Mapa->colunas + 1)); //Percorrendo cada linha alocamos o espaço de um char + 1
                                                            //para cada coluna do mapa
    }
}

void leMapa(MAPA* Mapa){
    FILE* f;
    f = fopen("Mapa.txt", "r");

    if(f == 0){
        printf("Erro na leitura do mapa\n");
        exit(1);
    }

    fscanf(f, "%d %d", &(Mapa->linhas), &(Mapa->colunas)); //Lê a quantidade de linhas e colunas a ser setado nas variaveis
    //printf("linhas %d colunas %d\n", linhas, colunas);

    alocaMapa(Mapa);

    for(int i = 0; i < Mapa->linhas; i++){
        fscanf(f, "%s", Mapa->matriz[i]); //Lê linha por linha e guarda na matriz Mapa
    }

    fclose(f);
}

void copiaMapa(MAPA* destino, MAPA* origem){
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;

    alocaMapa(destino);
    for(int i = 0; i < origem->linhas; i++){
        strcpy(destino->matriz[i], origem->matriz[i]);//strcpy função que copia uma string de uma variavel a outra

        //memcpy(&aniche, &mauricio, sizeof(CONTATO));//assim como o strcpy a memcpy copia porém não se limitando
        //a apenas uma string e sim uma struct inteira, porem nesse caso é necessario passar o destino, origem
        //e a quantidade de memoria necessaria, para isso usamos o sizeof e passamos a struct declarada

        //memset(&marcelo, 0, sizeof(CONTATO));//uma boa pratica é limparmos a memoria das variaveis que
        //queremos utilizar como struct, utilizando o memset, passando a struct, o valor 0 e o tamanho da
        //struct declarada
    }
}

int encontraposicaoPlayer(MAPA* Mapa, POSICAO* heroi){
    for(int i = 0; i < Mapa->linhas; i++){
        for(int j = 0; j < Mapa->colunas; j++){
            if(Mapa->matriz[i][j] == HEROI){ //HEROI atribuido pois é uma constante representando o caracter @
                heroi->x = i;
                heroi->y = j;
                return 1;
            }
        }
    }
    return 0;
}

int direcaoinvalida(char *direcao){
    if(*direcao != ESQUERDA && *direcao != CIMA && *direcao != BAIXO && *direcao != DIREITA){
        return 1; //return garante que a função termine ali e não continue mais
    }else 
        return 0;         
}

int posicaovalida(MAPA* Mapa, int proximox, int proximoy){
    if(proximox >= Mapa->linhas)
        return 0;

    if(proximoy >= Mapa->colunas)
        return 0;

    if(Mapa->matriz[proximox][proximoy] == PAREDE_VERTICAL || Mapa->matriz[proximox][proximoy] == PAREDE_HORIZONTAL)
        return 0;

    if(Mapa->matriz[proximox][proximoy] == FANTASMA)
        return 0;

    return 1;
}

int posicaovalidaexplosao(MAPA* Mapa, int alcancex, int alcancey){
    if(alcancex >= Mapa->linhas)
        return 0;

    if(alcancey >= Mapa->colunas)
        return 0;

    if(Mapa->matriz[alcancex][alcancey] == PAREDE_VERTICAL || Mapa->matriz[alcancex][alcancey] == PAREDE_HORIZONTAL)
        return 0;

    if(Mapa->matriz[alcancex][alcancey] == FANTASMA)
        Fantasmas_no_Mapa--;

    return 1;
}

void movimentaFantasma(MAPA* Mapa, int origemx, int origemy, int destinox, int destinoy){
    Mapa->matriz[destinox][destinoy] = FANTASMA;
    Mapa->matriz[origemx][origemy] = VAZIO;
}

void movimentaPlayer(MAPA* Mapa, POSICAO* heroi, int proximox, int proximoy){
    Mapa->matriz[proximox][proximoy] = HEROI;
    Mapa->matriz[heroi->x][heroi->y] = VAZIO;
    heroi->x = proximox;
    heroi->y = proximoy;
}

void moveposicaoPlayer(MAPA* Mapa, char *direcao, POSICAO* heroi, int *Pilula){
    if(direcaoinvalida(direcao))
        return;

    int proximox = heroi->x;
    int proximoy = heroi->y;

    switch((*direcao)){
        case ESQUERDA:
            proximoy--;
            break;
        
        case CIMA:
            proximox--;
            break;

        case BAIXO:
            proximox++;
            break;

        case DIREITA:
            proximoy++;
            break;
    }

    if(!posicaovalida(Mapa, proximox, proximoy))
        return;

    if(Mapa->matriz[proximox][proximoy] == PILULA)
        *Pilula = 1;

    movimentaPlayer(Mapa, heroi, proximox, proximoy);
}