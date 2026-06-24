typedef struct mapa MAPA;  //Cria uma palavra reservada para que mapa possa ser instanciada apenas com a palavra MAPA
typedef struct posicao POSICAO;

void liberaMapa(MAPA* Mapa);
void leMapa(MAPA* Mapa);
void alocaMapa(MAPA* Mapa);
void imprimeMapa(MAPA* Mapa);

struct mapa{ //Declarando uma struct
    char** matriz; // ** para declarar a matriz
    int linhas;
    int colunas;
};

int encontraposicaoPlayer(MAPA* Mapa, POSICAO* heroi);
void move(char direcao);
void moveposicaoPlayer(MAPA* Mapa, char *direcao, POSICAO* heroi);

struct posicao{
    int x;
    int y;
};