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

    for(int i = 0; i < 5; i++){
        fscanf(f, "%s", Mapa->matriz[i]); //Lê linha por linha e guarda na matriz Mapa
    }

    fclose(f);
}

void imprimeMapa(MAPA* Mapa){
    for(int i = 0; i < 5; i++){
            printf("%s\n", Mapa->matriz[i]); //Imprime linha por linha as informações guardadas em Mapa
        }
}

int encontraposicaoPlayer(MAPA* Mapa, POSICAO* heroi){
    for(int i = 0; i < Mapa->linhas; i++){
        for(int j = 0; j < Mapa->colunas; j++){
            if(Mapa->matriz[i][j] == '@'){
                heroi->x = i;
                heroi->y = j;
                break;
            }
        }
    }
}

void moveposicaoPlayer(MAPA* Mapa, char *direcao, POSICAO* heroi){
    Mapa->matriz[heroi->x][heroi->y] = '.';
    switch((*direcao)){
        case 'a':
            Mapa->matriz[heroi->x][(heroi->y)-1] = '@';
            heroi->y--;
            break;
        
        case 'w':
            Mapa->matriz[(heroi->x)-1][heroi->y] = '@';
            heroi->x--;
            break;

        case 's':
            Mapa->matriz[(heroi->x)+1][heroi->y] = '@';
            heroi->x++;
            break;

        case 'd':
            Mapa->matriz[heroi->x][(heroi->y)+1] = '@';
            heroi->y++;
            break;
    }
}