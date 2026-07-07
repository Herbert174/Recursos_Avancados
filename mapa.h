#define HEROI '@'
#define FANTASMA 'F'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'
#define FANTASMAS_NO_MAPA 2

typedef struct mapa MAPA;  //Cria uma palavra reservada para que mapa possa ser instanciada apenas com a palavra MAPA
typedef struct posicao POSICAO;

void liberaMapa(MAPA* Mapa);
void leMapa(MAPA* Mapa);
void alocaMapa(MAPA* Mapa);
void imprimeMapa(MAPA* Mapa);
void copiaMapa(MAPA* destino, MAPA* origem);
int direcaoinvalida(char *direcao);
int posicaovalida(MAPA* Mapa, int proximox, int proximoy);
void movimentaPlayer(MAPA* Mapa, POSICAO* heroi, int proximox, int proximoy);
void movimentaFantasma(MAPA* Mapa, int origemx, int origemy, int destinox, int destinoy);

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