char desenhoparede[4][7] = {
	{"......" },
	{"......" },
	{"......" },
	{"......" }
};

char desenhofantasma[4][7] = {
	{" .-.  " },
	{"| OO| " },
	{"|   | " },
	{"'^^^' " }
};

char desenhoheroi[4][7] = {
	{" .--. "  },
	{"/ _.-'"  },
	{"\\  '-." },
	{" '--' "  }
};

char desenhopilula[4][7] = {
	{"      "},
	{" .-.  "},
	{" '-'  "},
	{"      "}
};

char desenhovazio[4][7] = {
	{"      "},
	{"      "},
	{"      "},
	{"      "}
};

void imprimeparte(char desenho[4][7], int parte){
    printf("%s", desenho[parte]);
}

void imprimeMapa(MAPA* Mapa){
    for(int i = 0; i < Mapa->linhas; i++){
        for(int parte = 0; parte < 4; parte++){
            for(int j = 0; j < Mapa->colunas; j++){
                switch(Mapa->matriz[i][j]){
                    case FANTASMA:
                        imprimeparte(desenhofantasma, parte);
                        break;

                    case HEROI:
                        imprimeparte(desenhoheroi, parte);
                        break;

                    case PILULA:
                        imprimeparte(desenhopilula, parte);
                        break;

                    case PAREDE_HORIZONTAL:
                    case PAREDE_VERTICAL:
                        imprimeparte(desenhoparede, parte);
                        break;

                    case VAZIO:
                        imprimeparte(desenhovazio, parte);
                        break;
                }
            }
            printf("\n");
        }
    }
}