#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// J O G O   S N A K E 

// FUNCIONALIDADES DO JOGO
// >   inicializar o jogo
// >   jogar/realizar o jogo
// >   gerar arquivo resumo das jogadas
// >   gerar arquivo de ranking
// >   gerar arqiovo de estatisticas
// >   gerar arquivo de heatMap
// >   trantar os tuneis


// CAMPO DE JOGO
#define FRUTINHA '*'      // comida
#define PAREDE '#'        // parede
#define DINHEIRO '$'      // dinheiro
#define TUNEIS '@'        // tuneis
#define TELA_VAZIA ' '    // Espaco vazio do jogo
#define FRUTINHA_PONTO 1  // quantidade de pontos dada por uma comida(*)
#define DINHEIRO_PONTO 10 // quantidade de pontos dado por um dinheiro($)

// CORPO DA COBRINHA
#define CORPO 'o'  // corpo da cobrinha viva
#define MORREU 'X' // corpo da cobrinha morta
// MOVIMENTOS DA COBRINHA
#define MOV_HORARIO 'h'     // horario
#define MOV_ANTIHORARIO 'a' // anti-horario
#define MOV_CONTINUE 'c'    // continuar (em frente)
// CABECA DA COBRINHA
#define CABECA_DIREITA '>'  // Virada p/ a direita
#define CABECA_ESQUERDA '<' // Virada p/ a esquerda
#define CABECA_CIMA '^'     // Virada p/ cima
#define CABECA_BAIXO 'v'    // Virada p/ baixo

// MAPA DE JOGO

typedef struct {
    char mapa[100][101];
    char heatMap[100][101];
    int linhas;
    int colunas;
} tMapa;

tMapa CriaMapa(tMapa mapa, char diretorio[]); // le um arquivo de mapa e insere no jogo
tMapa InicializaHeatMap(tMapa mapa); // inicializa o heatMap
tMapa LimpaMapa(tMapa mapa, int coluna, int linha); // Esvazia o mapa numa dada posicao
int NovaCelulaDestino(tMapa mapa, int i, int j);
char ExtraiCelulaDoMapa(tMapa mapa, int i, int j); // retorna uma celula do mapa 
int HaComida(tMapa mapa); // verifica se ainda ha comida no mapa de jogo
void GeraArquivoHeatMap(tMapa mapa, char diretorio[]); // cria o arquivo de heatMap com as informacoes coletadas
int TrataCoordenadas(int posicao, int limite); // garante que a cobrinha nao estrapolarah os limites do mapa

// RANKING DE POSICOES MAIS FREQUENTADAS

typedef struct {
    int i; // linha (coordenada Y)
    int j; // coluna (coordenada X)
    int qtdVzsPassadas; // numero de vezes que a cabeca da cobra passou pela posicao
} tRanking;

void Ranking(tMapa mapa, char diretorio[]); // cria um arquivo de ranking com as informacoes coletadas
int CopiaRanking(tRanking ranking[], int tam, tMapa mapa); // copia todas as posicoes frequentadas ao menos uma vez do heatMap
void OrdenaDecrescente(tRanking ranking[], int tam); // ordena os dados coletados em ordem decrescente das posicoes
int Ehmaior(tRanking anterior, tRanking seguinte); // funcao auxiliar (verifica se a posicao seguinte vem antes da outra, retorna sim(1) ou nao(0))
int EhMaiorQ(int a, int b); // funcao auxiliar , verifica se eh maior
int EhMenorQ(int a, int b); // funcao auxiliar , verifica se eh menor
int EhIgual(char a, char b);

//ESTATISTICAS DO JOGO

typedef struct {
    int nMovimentos; // numero de movimentos dentro do jogo
    int nMovDireita; // numero de movimentos para a direita
    int nMovEsquerda; // ... para a esquerda
    int nMovBaixo; // ... para baixo
    int nMovCima; // ... para cima
    int nMovSemPontuar; // ... sem pontuar
} tEstatisticas;
// ATUALIZAM AS ESTATISTICAS DE UMA DETERMINADA JOGADA
tEstatisticas AtualizaEstatisticasQtddMovCima(tEstatisticas estatisticas);
tEstatisticas AtualizaEstatisticasQtddMovBaixo(tEstatisticas estatisticas);
tEstatisticas AtualizaEstatisticasQtddMovDireita(tEstatisticas estatisticas);
tEstatisticas AtualizaEstatisticasQtddMovEsquerda(tEstatisticas estatisticas);
tEstatisticas ResetaEstatisticas(tEstatisticas estatisticas);
tEstatisticas AtualizaEstatisticasQtddMovSemPontuar(tEstatisticas estatisticas);
tEstatisticas AtualizaEstatisticasQtddMovimentos(tEstatisticas estatisticas);
int ExtraiNumMovimentos(tEstatisticas estatisticas); // funcao auxiliar, retorna um numero inteiro da qtdd de movimentos
void Estatisticas(tEstatisticas estatisticas, char diretorio[]); // cria um arquivo de estatisticas
tEstatisticas BackupDeEstatisticas(tEstatisticas estatisticas); // faz backup das estatisticas salvando elas em uma variavel do tipo estatisticas
// INFORMACOES DO STATUS ATUAL DO JOGO

typedef struct {
    int ponto; // Quantidade de pontos da partida
    char jogada;
    char Frutinha;
    char Dinheiro;
    int viva;
    int cresceu;
} tStatus;
tStatus AtualizaStatusDeCrescimento(tStatus status); // funcao auxiliar, seta que a cobrinha cresceu(1)
int CresceuCobrinha(tStatus status); // funcao auxiliar, retorna verdadeiro se a cobrinha cresceu
tStatus ResetaStatus(tStatus status); // reseta todos os status do jogo, com excessao dos pontos
tStatus ResetaPontos(tStatus status); // reseta os pontos do jogo
tStatus LeJogada(tStatus status); // Le e retorna uma jogada valida
char RecebeJogada(char recebeJogada, char jogada); // funcao auxiliar, insere o caracter de jogada nos status
int EhValidaJogada(char jogada); // funcao auxiliar, retorna verdadeiro se a jogada eh valida
char ExtraiJogada(tStatus status); // funcao auxiliar, retorna o character de jogada
int AchouDinheiro(char celula); // funcao auxiliar, retorna verdadeiro se a celula for um dinheiro
int AchouFrutinha(char celula); // funcao auxiliar, retorna verdadeiro se a celula for uma frutinha
int MorreuCobrinha(char celula); // funcao auxiliar, retorna verdadeiro se a celula for uma parede
int EstaViva(tStatus status); // funcao auxiliar, retorna verdadeiro se a cobrinha estiver viva
tStatus RetiraVida(tStatus status); // seta a vida em 0 (mata a cobrinha)
int ComeuDinheiro(tStatus status); // funcao auxiliar, retorna verdadeiro se o status de dinheiro for verdadeiro(1)
int ComeuFrutinha(tStatus status); // funcao auxiliar, retorna verdadeiro se o status de frutinha for verdadeiro(1)
tStatus AumentaPontuacaoFrutinha(tStatus status); // aumenta pontuacao
tStatus AumentaPontuacaoDinheiro(tStatus status); // aumenta pontuacao
void ImprimePontuacao(tStatus status); // imprime a pontuacao atual
char SalvaJogadaJogo(tStatus status);
tStatus ResetaJogadaJogo(tStatus status, char jogada);

// CABECA E CORPO DA COBRINHA

typedef struct {
    int x;
    int y;
} tCobrinha;
//Retorna o par de coordenadas da posicao anterior da cobrinha
void RecebeCoordenadaYAnterior(tCobrinha cobrinha[], int tam);
void RecebeCoordenadaXAnterior(tCobrinha cobrinha[], int tam);
int ExtraiCorpoCobrinhaX(tCobrinha cobrinha[], int i); // retorna as coordenadas de uma posicao do corpo da cobrinha
int ExtraiCorpoCobrinhaY(tCobrinha cobrinha[], int i);
// CABECA DA COBRINHA 

typedef struct {
    int x; // posicao x
    int y; // posicao y
    char cabeca; // caractere atual da cabeca da cobrinha
} tCabeca;
tCabeca MoveCobraParaOProximoTunel(tMapa mapa, tCabeca cabeca); // muda as coordenadas da cabeca da cobrinha para o proximo tunel
tMapa AtualizaHeatMap(tMapa mapa, tCabeca cabeca);
int CabecaCobrinhaX(tCabeca cabeca); // funcao auxiliar, retorna a coordenada da cabeca da cobrinha
int CabecaCobrinhaY(tCabeca cabeca);
tCabeca ResetaCabecaCobrinha(tCabeca cabeca); // funcao auxiliar, seta a cabeca da cobrinha para o lado direito
char ExtraiCabeca(tCabeca cabeca); // funcao auxiliar, retorna ocaracter da cabeca da cobrinha
tCabeca AtualizaDirecaoDaCabeca(tCabeca cabeca, char novaCabeca); //altera a direcao da cabeca da cobrinha
// funcao auxiliar a movimentacao da cobrinha, incrementa ou decrementa em um a coordenada da cobrinha
tCabeca DesceCobrinhaY(tCabeca cabeca, tMapa mapa);
tCabeca SobeCobrinhaY(tCabeca cabeca, tMapa mapa);
tCabeca DireitaCobrinhaX(tCabeca cabeca, tMapa mapa);
tCabeca EsquerdaCobrinhaX(tCabeca cabeca, tMapa mapa);
tMapa InsereCabecaNoMapa(tMapa mapa, tCabeca cabeca);
tCobrinha NovaCoordenadaDaCabecaDaCobrinha(tCobrinha cobrinha, tCabeca cabeca);
tMapa InsereCorpoNaNovaCoordenada(tMapa mapa, tCobrinha cobrinha[], int tam);
tMapa InsereXNaCobrinha(tMapa mapa, tCobrinha cobrinha[], int i); // quando a cobrinha morre, altera o corpo da cobrinha p 'X'
tCabeca ReconheceCobrinha(tCabeca cabeca, tMapa mapa, tCobrinha cobrinha[]); // encontra a cabeca da cobrinha
void SalvaInicializacao(tMapa mapa, char diretorio[], tCabeca cabeca); // cria um arquivo de inicializacao


//TRATA TUNEIS
int ACobraEstaNoTunel(tMapa mapa, int i, int j, int y, int x);
int AchouTunel(char celula);

typedef struct {
    char diretorio[1000]; // Endereco do diretorio
    tMapa mapa; // informacoes do mapa 
    tCabeca cabeca; // dados de posicao e caractere da cabeca da cobrinha
    tCobrinha cobrinha[100]; // posicao de cada parte do corpo da cobrinha
    int tamCobrinha; // tamanho atual da cobrinha
    char celulaDestino; // celula que a cobrinha ira apos a jogada
    tStatus status; // informacoes de status do jogo
    tEstatisticas estatisticas; // estatisticas dos movimentos do jogo
} tJogo;
tJogo TeleportaCobrinha(tJogo jogo);
void SalvaDiretorio(char diretorio[], char copy[]); // armazena o diretorio
tJogo AbreArquivoJogo(int argc, char *argv[]); // verifica se o diretorio eh valido
tJogo CriaJogo(tJogo jogo); // cria o ambiente de jogo
tJogo ResetaJogo(tJogo jogo); // zera as informacoes do jogo
tJogo JogaJogo(tJogo jogo); // processa as jogadas
void ImprimeJogo(tJogo jogo); // imprime o estado atual do jogo e a pontuacao
char CelulaDestino(tJogo jogo); // retorna qual sera a celula que a cobrinha irah

//MOVIMENTACAO DA COBRINHA
tJogo MoveCobrinha(tJogo jogo); // define que direcao a cabeca seguira
// prepara o caminho para a cobrinha andar
tJogo AndaCobrinhaBaixo(tJogo jogo);
tJogo AndaCobrinhaCima(tJogo jogo);
tJogo AndaCobrinhaDireita(tJogo jogo);
tJogo AndaCobrinhaEsquerda(tJogo jogo);
tJogo AndaCobrinha(tJogo jogo); // move o corpo inteiro da cobrinha

tJogo MataCobrinha(tJogo jogo); // se a cobrinha morreu, prepara a morte
tJogo AumentaTamanhoCobrinha(tJogo jogo);
tJogo CresceCobrinha(tJogo jogo);
int ResetaTamanhoCobrinha(int tamCobrinha); // seta 1 para o tamanho  da cobrinha
int TamanhoCobrinha(tJogo jogo);
int NaoEhOFim(tJogo jogo); // verifica se eh o fim do jogo, retorna verdadeiro ou falso
void ImprimeResultado(tJogo jogo);
void FinalizaJogo(tJogo jogo); // chama as funcoes que geram arquivos
//RESUMO DAS JOGADAS
void ApagaArquivosAntigosDeResumo(tJogo jogo); // reseta se existir um arquivo de resumo
void Resumo(tJogo jogo); // cria um arquivo de resumo a cada jogada

int main(int argc, char *argv[]) {
    tJogo jogo;
    jogo = AbreArquivoJogo(argc, argv);
    jogo = CriaJogo(jogo);

    do {
        jogo = JogaJogo(jogo); // Processa as jogadas
        ImprimeJogo(jogo);
        Resumo(jogo); // atualiza o arquivo de resumo

    } while (NaoEhOFim(jogo));

    FinalizaJogo(jogo);


    return EXIT_SUCCESS;
}
//INICIALIZACAO DO JOGO

tJogo AbreArquivoJogo(int argc, char *argv[]) {
    char diretorio[1000];
    tJogo jogo;
    if (argc == 1) {
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        exit(1);
    }
    // ve se eh possivel abrir o arquivo de mapa
    sprintf(diretorio, "%s/mapa.txt", argv[1]);
    FILE *arq = fopen(diretorio, "r");
    if (arq == NULL) {
        printf("ERRO: Nao foi possivel abrir o diretorio %s\n", diretorio);
        exit(1);
    }
    fclose(arq);
    // Salva diretorio
    SalvaDiretorio(jogo.diretorio, argv[1]);
    return jogo;
}

void SalvaDiretorio(char diretorio[], char copy[]) {
    strcat(diretorio, copy);
}
// reseta todas as veriaveis quantitativas possiveis e prepara o ambiente de jogo

tJogo CriaJogo(tJogo jogo) {
    jogo = ResetaJogo(jogo);
    jogo.mapa = CriaMapa(jogo.mapa, jogo.diretorio);
    jogo.mapa = InicializaHeatMap(jogo.mapa);
    jogo.cabeca = ReconheceCobrinha(jogo.cabeca, jogo.mapa, jogo.cobrinha);
    SalvaInicializacao(jogo.mapa, jogo.diretorio, jogo.cabeca);
    jogo.mapa = AtualizaHeatMap(jogo.mapa, jogo.cabeca);
    ApagaArquivosAntigosDeResumo(jogo);
    return jogo;
}

tMapa CriaMapa(tMapa mapa, char diretorio[]) {
    int i, j;
    char map[1100];
    // Abre o arquivo de mapa e prepara o ambiente de jogo
    sprintf(map, "%s/mapa.txt", diretorio);

    FILE *arq = fopen(map, "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo%s\n", map);
        exit(1);
    }

    // Le o Mapa de jogo do arquivo
    fscanf(arq, "%d %d", &mapa.linhas, &mapa.colunas);
    fscanf(arq, "%*c");
    for (i = 0; i < mapa.linhas; i++) {
        for (j = 0; j < mapa.colunas; j++) {
            fscanf(arq, "%c", &mapa.mapa[i][j]);
        }
        fscanf(arq, "%*c");
    }
    fclose(arq);

    return mapa;
}

tMapa InicializaHeatMap(tMapa mapa) {
    // coloca zeros em todas as posicoes do heatMap 
    int i, j;
    for (i = 0; i < mapa.linhas; i++) {
        for (j = 0; j < mapa.colunas; j++) {
            mapa.heatMap[i][j] = 0;
        }
    }
    return mapa;
}

tEstatisticas ResetaEstatisticas(tEstatisticas estatisticas) {
    estatisticas.nMovBaixo = 0;
    estatisticas.nMovCima = 0;
    estatisticas.nMovDireita = 0;
    estatisticas.nMovEsquerda = 0;
    estatisticas.nMovSemPontuar = 0;

    return estatisticas;
}

tJogo ResetaJogo(tJogo jogo) {
    jogo.estatisticas = ResetaEstatisticas(jogo.estatisticas);
    jogo.status = ResetaStatus(jogo.status);
    jogo.status = ResetaPontos(jogo.status);
    jogo.tamCobrinha = ResetaTamanhoCobrinha(jogo.tamCobrinha);
    jogo.cabeca = ResetaCabecaCobrinha(jogo.cabeca);
    return jogo;
}

tCabeca ResetaCabecaCobrinha(tCabeca cabeca) {
    cabeca.cabeca = CABECA_DIREITA;
    return cabeca;
}

tStatus ResetaPontos(tStatus status) {
    status.ponto = 0;
    return status;
}

int ResetaTamanhoCobrinha(int tamCobrinha) {
    tamCobrinha = 1;
    return tamCobrinha;
}

tStatus ResetaStatus(tStatus status) {
    status.Frutinha = 0;
    status.Dinheiro = 0;
    status.cresceu = 0;
    status.viva = 1;
    return status;
}

void SalvaInicializacao(tMapa mapa, char diretorio[], tCabeca cabeca) {
    char inicializacao[1100];
    // cria um arquivo de inicializacao com a copia do mapa
    sprintf(inicializacao, "%s/saida/inicializacao.txt", diretorio);
    FILE *arq = fopen(inicializacao, "w");
    int i, j;
    for (i = 0; i < mapa.linhas; i++) {
        for (j = 0; j < mapa.colunas; j++) {
            fprintf(arq, "%c", mapa.mapa[i][j]);
        }
        fprintf(arq, "\n");
    }
    fprintf(arq, "A cobra comecara o jogo na linha %d e coluna %d\n",
            cabeca.y + 1, cabeca.x + 1);
    fclose(arq);
}

tCabeca ReconheceCobrinha(tCabeca cabeca, tMapa mapa, tCobrinha cobrinha[]) {
    int i, j;
    // varre o mapa e procura pela cabeca da cobrinha '>'
    for (i = 0; i < mapa.linhas; i++) {
        for (j = 0; j < mapa.colunas; j++) {
            if (EhIgual(mapa.mapa[i][j], CABECA_DIREITA)) {
                cabeca.x = j;
                cabeca.y = i;
                cobrinha[0].x = j;
                cobrinha[0].y = i;
            }
        }
    }
    return cabeca;
}

// IMPRESSAO DO JOGO

void ImprimeJogo(tJogo jogo) {
    // Imprime mapa de jogo
    int i, j;
    printf("\n");
    printf("Estado do jogo apos o movimento '%c':\n", jogo.status.jogada);

    for (i = 0; i < jogo.mapa.linhas; i++) {
        for (j = 0; j < jogo.mapa.colunas; j++) {
            printf("%c", jogo.mapa.mapa[i][j]);
        }
        printf("\n");
    }
    printf("Pontuacao:");
    ImprimePontuacao(jogo.status); // pontuacao atual
}

void ImprimeResultado(tJogo jogo) {
    // Imprime o resultado em relacao a vitorio ou a derrota
    if (EstaViva(jogo.status)) {
        printf("Voce venceu!\n");
    } else {
        printf("Game over!\n");
    }
    printf("Pontuacao final:");
    ImprimePontuacao(jogo.status);
}

void ImprimePontuacao(tStatus status) {
    printf(" %d\n", status.ponto);
}

// REALIZACAO DO JOGO E PROCESSAMENTO DAS JOGADAS

tJogo JogaJogo(tJogo jogo) {
    jogo.status = ResetaStatus(jogo.status); // eh resetado p/ n afetar o jogo
    int cobrinhaX = ExtraiCorpoCobrinhaX(jogo.cobrinha, jogo.tamCobrinha - 1);
    int cobrinhaY = ExtraiCorpoCobrinhaY(jogo.cobrinha, jogo.tamCobrinha - 1);
    jogo.mapa = LimpaMapa(jogo.mapa, cobrinhaX, cobrinhaY); // eh limpo p/ n afetar o jogo

    // Le uma jogada valida
    jogo.status = LeJogada(jogo.status);

    jogo = MoveCobrinha(jogo); // verifica qual sera a proxima posicao da cobrinha e atualiza umas informacoes
    // ATENCAO : a movimentacao real da cobrinha acontece na funcao ANDACOBRINHA
    jogo.estatisticas = AtualizaEstatisticasQtddMovimentos(jogo.estatisticas); // incrementa qtdd de movimentos

    char destinoCobrinha = CelulaDestino(jogo); // a celula que a cobrinha irah ao move-la
    if (AchouTunel(destinoCobrinha)) {
        jogo = TeleportaCobrinha(jogo);
    }
    
    destinoCobrinha = CelulaDestino(jogo);// atualiza a celula destino

    if (AchouFrutinha(destinoCobrinha)) { // se essa celula for uma fruta, cresce a pontuacao e a cobrinha        
        jogo = CresceCobrinha(jogo);
        jogo.status = AumentaPontuacaoFrutinha(jogo.status);

    } else if (AchouDinheiro(destinoCobrinha)) { // se a celula for um dinheiro, cresce a pontuacao
                jogo.status = AumentaPontuacaoDinheiro(jogo.status);

    } else { // se a celula for uma tela vazia somente incrementa as estatisticas        
        jogo.estatisticas = AtualizaEstatisticasQtddMovSemPontuar(jogo.estatisticas);

    }

    // DESLOCAMENTO DO CORPO DA COBRINHA
    jogo = AndaCobrinha(jogo);
    jogo.mapa = AtualizaHeatMap(jogo.mapa, jogo.cabeca); // Incrementa a posicao frequentada 

    // TRATA A MORTE DA COBRINHA
    if (MorreuCobrinha(destinoCobrinha)) {
        jogo = MataCobrinha(jogo);
        return jogo;
    }


    return jogo;
}

tStatus LeJogada(tStatus status) {
    // le e retorna uma jogada valida
    char jogada;
    do {
        scanf("%c", &jogada);
        scanf("%*[^\n]");
        scanf("%*c");
    } while (!EhValidaJogada(jogada));

    status.jogada = RecebeJogada(status.jogada, jogada);

    return status;
}

char RecebeJogada(char recebeJogada, char jogada) {
    recebeJogada = jogada;
    return recebeJogada;
}

int EhValidaJogada(char jogada) {
    return (jogada == MOV_ANTIHORARIO || jogada == MOV_HORARIO || jogada == MOV_CONTINUE);
}

//MOVIMENTACAO DA COBRINHA

tJogo MoveCobrinha(tJogo jogo) {
    char cabecaCobrinha = ExtraiCabeca(jogo.cabeca);
    char jogada = ExtraiJogada(jogo.status);

    // Se a cabeca da cobrinha estiver voltada para cima
    if (cabecaCobrinha == CABECA_CIMA) {
        if (jogada == MOV_HORARIO) { // Se o movimento for horario
            jogo = AndaCobrinhaDireita(jogo);
        } else if (jogada == MOV_ANTIHORARIO) { // Se o movimento for antiHorario
            jogo = AndaCobrinhaEsquerda(jogo);
        } else if (jogada == MOV_CONTINUE) { // Se o movimento for continue
            jogo = AndaCobrinhaCima(jogo);
        }
    }// Se a cabeca da cobrinha estiver voltada para baixo
    else if (cabecaCobrinha == CABECA_BAIXO) {
        if (jogada == MOV_HORARIO) { // Se o movimento for horario
            jogo = AndaCobrinhaEsquerda(jogo);
        } else if (jogada == MOV_ANTIHORARIO) { // Se o movimento for antiHorario
            jogo = AndaCobrinhaDireita(jogo);
        } else if (jogada == MOV_CONTINUE) { // Se o movimento for continue
            jogo = AndaCobrinhaBaixo(jogo);
        }
    }// Se a cabeca da cobrinha estiver voltada para a direita
    else if (cabecaCobrinha == CABECA_DIREITA) {
        if (jogada == MOV_HORARIO) { // Se o movimento for horario
            jogo = AndaCobrinhaBaixo(jogo);
        } else if (jogada == MOV_ANTIHORARIO) { // Se o movimento for antiHorario
            jogo = AndaCobrinhaCima(jogo);
        } else if (jogada == MOV_CONTINUE) { // Se o movimento for continue
            jogo = AndaCobrinhaDireita(jogo);
        }
    }// Se a cabeca da cobrinha estiver voltada para a esquerda
    else if (cabecaCobrinha == CABECA_ESQUERDA) {
        if (jogada == MOV_HORARIO) { // Se o movimento for horario
            jogo = AndaCobrinhaCima(jogo);
        } else if (jogada == MOV_ANTIHORARIO) { // Se o movimento for antiHorario
            jogo = AndaCobrinhaBaixo(jogo);
        } else if (jogada == MOV_CONTINUE) { // Se o movimento for continue
            jogo = AndaCobrinhaEsquerda(jogo);
        }
    }
    return jogo;
}

tJogo AndaCobrinhaBaixo(tJogo jogo) {
    jogo.cabeca = AtualizaDirecaoDaCabeca(jogo.cabeca, CABECA_BAIXO);
    jogo.cabeca = DesceCobrinhaY(jogo.cabeca, jogo.mapa); // Aumenta a posicao y da cobrinha
    int cobrinhaX = CabecaCobrinhaX(jogo.cabeca);
    int cobrinhaY = CabecaCobrinhaY(jogo.cabeca);
    jogo.celulaDestino = NovaCelulaDestino(jogo.mapa, cobrinhaY, cobrinhaX); // atualiza a nova celula de destino da cobrinha
    jogo.estatisticas = AtualizaEstatisticasQtddMovBaixo(jogo.estatisticas); // incrementa as estatisticas
    return jogo;
}

tJogo AndaCobrinhaCima(tJogo jogo) {
    jogo.cabeca = AtualizaDirecaoDaCabeca(jogo.cabeca, CABECA_CIMA);
    jogo.cabeca = SobeCobrinhaY(jogo.cabeca, jogo.mapa); // Diminui a coordenada y da cobrinha
    int cobrinhaX = CabecaCobrinhaX(jogo.cabeca);
    int cobrinhaY = CabecaCobrinhaY(jogo.cabeca);
    jogo.celulaDestino = NovaCelulaDestino(jogo.mapa, cobrinhaY, cobrinhaX); // atualiza a nova celula de destino da cobrinha 
    jogo.estatisticas = AtualizaEstatisticasQtddMovCima(jogo.estatisticas); // incrementa as estatisticas
    return jogo;
}

tJogo AndaCobrinhaDireita(tJogo jogo) {
    jogo.cabeca = AtualizaDirecaoDaCabeca(jogo.cabeca, CABECA_DIREITA);
    jogo.cabeca = DireitaCobrinhaX(jogo.cabeca, jogo.mapa); // Aumenta a coordenada x da cobrinha
    int cobrinhaX = CabecaCobrinhaX(jogo.cabeca);
    int cobrinhaY = CabecaCobrinhaY(jogo.cabeca);
    jogo.celulaDestino = NovaCelulaDestino(jogo.mapa, cobrinhaY, cobrinhaX); // atualiza a nova celula de destino da cobrinha
    jogo.estatisticas = AtualizaEstatisticasQtddMovDireita(jogo.estatisticas); // incrementa as estatisticas
    return jogo;
}

tJogo AndaCobrinhaEsquerda(tJogo jogo) {
    jogo.cabeca = AtualizaDirecaoDaCabeca(jogo.cabeca, CABECA_ESQUERDA);
    jogo.cabeca = EsquerdaCobrinhaX(jogo.cabeca, jogo.mapa); // Diminui a coordenada x da cobrinha
    int cobrinhaX = CabecaCobrinhaX(jogo.cabeca);
    int cobrinhaY = CabecaCobrinhaY(jogo.cabeca);
    jogo.celulaDestino = NovaCelulaDestino(jogo.mapa, cobrinhaY, cobrinhaX); // atualiza a nova celula de destino da cobrinha
    jogo.estatisticas = AtualizaEstatisticasQtddMovEsquerda(jogo.estatisticas); // incrementa as estatisticas
    return jogo;
}

tCabeca AtualizaDirecaoDaCabeca(tCabeca cabeca, char novaCabeca) {
    cabeca.cabeca = novaCabeca; // novo caractere de cabeca
    return cabeca;
}
// incrementarao ou decrementarao a posicao da cabeca da cobrinha

tCabeca DesceCobrinhaY(tCabeca cabeca, tMapa mapa) {
    cabeca.y += 1;
    cabeca.y = TrataCoordenadas(cabeca.y, mapa.linhas);
    return cabeca;
}

tCabeca SobeCobrinhaY(tCabeca cabeca, tMapa mapa) {
    cabeca.y -= 1;
    cabeca.y = TrataCoordenadas(cabeca.y, mapa.linhas);
    return cabeca;
}

tCabeca DireitaCobrinhaX(tCabeca cabeca, tMapa mapa) {
    cabeca.x += 1;
    cabeca.x = TrataCoordenadas(cabeca.x, mapa.colunas);
    return cabeca;
}

tCabeca EsquerdaCobrinhaX(tCabeca cabeca, tMapa mapa) {
    cabeca.x -= 1;
    cabeca.x = TrataCoordenadas(cabeca.x, mapa.colunas);
    return cabeca;
}

int TrataCoordenadas(int posicao, int limite) {
    // Garante que a cobrinha NUNCA estrapolarah os limites do campo
    // Se ultrapasou ao limite maximo, entao reseto a posicao para o inicio
    if (posicao == limite) {
        posicao = 0;
        // se ultrapassou ao limite minimo, entao reseto a posicao para a ultima possivel
    } else if (posicao == -1) {
        posicao = limite - 1;
    }
    return posicao;
}

tMapa InsereCorpoNaNovaCoordenada(tMapa mapa, tCobrinha cobrinha[], int tam) {
    // coloca um caractere de corpo no mapa 'o'
    char corpo = CORPO;
    int cobrinhaX = ExtraiCorpoCobrinhaX(cobrinha, tam);
    int cobrinhaY = ExtraiCorpoCobrinhaY(cobrinha, tam);
    mapa.mapa[cobrinhaY][cobrinhaX] = corpo;
    return mapa;
}

tJogo AndaCobrinha(tJogo jogo) {
    int i, j, tam = jogo.tamCobrinha - 1;
    int cobrinhaX = ExtraiCorpoCobrinhaX(jogo.cobrinha, tam);
    int cobrinhaY = ExtraiCorpoCobrinhaY(jogo.cobrinha, tam);

    if (!CresceuCobrinha(jogo.status)) {
        jogo.mapa = LimpaMapa(jogo.mapa, cobrinhaX, cobrinhaY);
    } // se a cobrinha nao cresce limpo a ultima posicao
    // Altera TODAS as posicoes do corpo da cobrinha , substitui pela posicao anterior mais proxima da cabeca
    for (i = jogo.tamCobrinha - 1; i > 0; i--) {
        RecebeCoordenadaXAnterior(jogo.cobrinha, i);
        RecebeCoordenadaYAnterior(jogo.cobrinha, i);
        jogo.mapa = InsereCorpoNaNovaCoordenada(jogo.mapa, jogo.cobrinha, i);
    }
    jogo.cobrinha[0] = NovaCoordenadaDaCabecaDaCobrinha(jogo.cobrinha[0], jogo.cabeca);
    jogo.mapa = InsereCabecaNoMapa(jogo.mapa, jogo.cabeca);
    return jogo;
}

// TRATA A MORTE DA COBRINHA

tMapa InsereXNaCobrinha(tMapa mapa, tCobrinha cobrinha[], int i) {
    char morreu = MORREU;
    int cobrinhaX = ExtraiCorpoCobrinhaX(cobrinha, i);
    int cobrinhaY = ExtraiCorpoCobrinhaY(cobrinha, i);
    mapa.mapa[cobrinhaY][cobrinhaX] = morreu; // coloca x no mapa onde a cobrinha estah localizada
    return mapa;
}

tJogo MataCobrinha(tJogo jogo) {
    int i, j, tam = TamanhoCobrinha(jogo) - 1;
    jogo.status = RetiraVida(jogo.status);
    for (i = tam; i >= 0; i--) {
        jogo.mapa = InsereXNaCobrinha(jogo.mapa, jogo.cobrinha, i); // x em todas as posicoes da cobrinha
    }
    return jogo;
}

tStatus RetiraVida(tStatus status) {
    status.viva = 0;
    return status;
}

// TRATA O CRESCIMENTO DA COBRINHA

tJogo CresceCobrinha(tJogo jogo) {
    // aumenta o tamanho da cobrinha
    RecebeCoordenadaXAnterior(jogo.cobrinha, jogo.tamCobrinha);
    RecebeCoordenadaYAnterior(jogo.cobrinha, jogo.tamCobrinha);
    jogo = AumentaTamanhoCobrinha(jogo);
    jogo.status = AtualizaStatusDeCrescimento(jogo.status);
    return jogo;
}

tJogo AumentaTamanhoCobrinha(tJogo jogo) {
    jogo.tamCobrinha += 1; // auxiliar, incrementa tamanho
    return jogo;
}

int CresceuCobrinha(tStatus status) {
    return status.cresceu == 1;
}
// FUNCOES DE ARQUIVOS

void ApagaArquivosAntigosDeResumo(tJogo jogo) {
    char resumo[1100];
    sprintf(resumo, "%s/saida/resumo.txt", jogo.diretorio); // apaga p/ nao afetar a escrita do arquivo
    FILE *arq = fopen(resumo, "w");
    fclose(arq);
}

void Resumo(tJogo jogo) {
    char resumo[1100];
    char jogada = ExtraiJogada(jogo.status);
    int tamCobrinha = TamanhoCobrinha(jogo);
    int nMovimentos = ExtraiNumMovimentos(jogo.estatisticas);

    sprintf(resumo, "%s/saida/resumo.txt", jogo.diretorio);
    FILE *arq = fopen(resumo, "a");
    // se ela morre
    if (!EstaViva(jogo.status)) {
        fprintf(arq, "Movimento %d (%c) resultou no fim de jogo por conta de colisao\n", nMovimentos, jogada);
    }// se ela comeu uma fruta e o jogo ainda continua
    else if (ComeuFrutinha(jogo.status) && HaComida(jogo.mapa)) {
        fprintf(arq, "Movimento %d (%c) fez a cobra crescer para o tamanho %d\n", nMovimentos, jogada, tamCobrinha);
    }// se ela comeu um dinheiro 
    else if (ComeuDinheiro(jogo.status)) {
        fprintf(arq, "Movimento %d (%c) gerou dinheiro\n", nMovimentos, jogada);
    }// se ela comeu uma fruda e a comida acaba
    else if (ComeuFrutinha(jogo.status) && !HaComida(jogo.mapa)) {
        fprintf(arq, "Movimento %d (%c) fez a cobra crescer para o tamanho %d, terminando o jogo\n", nMovimentos, jogada, tamCobrinha);
    }
    fclose(arq);
}

void Estatisticas(tEstatisticas estatisticas, char diretorio[]) {
    char estatistics[1100];
    sprintf(estatistics, "%s/saida/estatisticas.txt", diretorio);
    FILE *arq = fopen(estatistics, "w");
    fprintf(arq, "Numero de movimentos: %d\n", estatisticas.nMovimentos);
    fprintf(arq, "Numero de movimentos sem pontuar: %d\n", estatisticas.nMovSemPontuar);
    fprintf(arq, "Numero de movimentos para baixo: %d\n", estatisticas.nMovBaixo);
    fprintf(arq, "Numero de movimentos para cima: %d\n", estatisticas.nMovCima);
    fprintf(arq, "Numero de movimentos para esquerda: %d\n", estatisticas.nMovEsquerda);
    fprintf(arq, "Numero de movimentos para direita: %d\n", estatisticas.nMovDireita);
    fclose(arq);
}

void GeraArquivoHeatMap(tMapa mapa, char diretorio[]) {
    char heatMap[1100];

    sprintf(heatMap, "%s/saida/heatmap.txt", diretorio);
    FILE *arq = fopen(heatMap, "w");

    int i, j;
    // copia o heatMap pro arquivo
    for (i = 0; i < mapa.linhas; i++) {
        for (j = 0; j < mapa.colunas; j++) {
            if (j == mapa.colunas - 1) {
                fprintf(arq, "%d", mapa.heatMap[i][j]);
            } else {
                fprintf(arq, "%d ", mapa.heatMap[i][j]);
            }
        }
        fprintf(arq, "\n");
    }

    fclose(arq);
}

void Ranking(tMapa mapa, char diretorio[]) {
    int tam = mapa.linhas * mapa.colunas, i;
    tRanking ranking[tam];

    tam = CopiaRanking(ranking, tam, mapa);
    OrdenaDecrescente(ranking, tam);

    char rank[1100];
    sprintf(rank, "%s/saida/ranking.txt", diretorio);
    FILE *arq = fopen(rank, "w");
    for (i = 0; i < tam; i++) {
        fprintf(arq, "(%d, %d) - %d\n", ranking[i].i, ranking[i].j, ranking[i].qtdVzsPassadas);
    }
    fclose(arq);
}

int CopiaRanking(tRanking ranking[], int tam, tMapa mapa) {
    int i, j, a = 0;
    for (i = 0; i < mapa.linhas; i++) {
        for (j = 0; j < mapa.colunas; j++) {
            // todas as posicoes visitadas (!=0) serao copiadas
            if (mapa.heatMap[i][j] != 0) {
                ranking[a].qtdVzsPassadas = mapa.heatMap[i][j];
                ranking[a].i = i;
                ranking[a].j = j;
                a++; // representa o tamanho da lista
            }
        }
    }

    return a;
}

int EhMenorQ(int a, int b) {
    return a < b;
}

int EhMaiorQ(int a, int b) {
    return a > b;
}

int EhIgual(char a, char b) {
    return a == b;
}

void OrdenaDecrescente(tRanking ranking[], int tam) {
    int i, j;
    tRanking aux;
    // averigua a lista completa
    for (i = 0; i < tam - 1; i++) { // posicao anterior
        for (j = i + 1; j < tam; j++) { // posicao seguinte
            // se a seguinte for maior que a anterior
            if (Ehmaior(ranking[i], ranking[j])) {
                // troca de posicao
                aux = ranking[j];
                ranking[j] = ranking[i];
                ranking[i] = aux;
            }
        }
    }
}

int Ehmaior(tRanking anterior, tRanking seguinte) {
    // ordem de prioridade numero de visitas em ordem decrescente
    // criterio de desempate ordem crescente do numero de linhas 
    // seguido da ordem crescente do numero de colunas

    if (EhMaiorQ(seguinte.qtdVzsPassadas, anterior.qtdVzsPassadas)) {
        // numero de visitas da seguinte maior que a anterior
        return 1;
    } else if (EhIgual(seguinte.qtdVzsPassadas, anterior.qtdVzsPassadas)) {
        // desempate : linhas da seguinte menor que a anterior
        if (EhMenorQ(seguinte.i, anterior.i)) {
            return 1;
        } else if (EhIgual(seguinte.i, anterior.i)) {
            // desempate: colunas da seguinte menor que a anterior
            if (EhMenorQ(seguinte.j, anterior.j)) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
    return 0;
}

// TRATA FIM DE JOGO

void FinalizaJogo(tJogo jogo) {
    ImprimeResultado(jogo);
    Estatisticas(jogo.estatisticas, jogo.diretorio);
    GeraArquivoHeatMap(jogo.mapa, jogo.diretorio);
    Ranking(jogo.mapa, jogo.diretorio);
}

int HaComida(tMapa mapa) {
    int i, j;
    char celula;
    for (i = 0; i < mapa.linhas; i++) {
        for (j = 0; j < mapa.colunas; j++) {
            celula = ExtraiCelulaDoMapa(mapa, i, j);
            if (AchouFrutinha(celula)) {
                return 1;
            }
        }
    }
    // se nao tem comida o jogo acaba
    return 0;
}

char ExtraiCelulaDoMapa(tMapa mapa, int i, int j) {
    return mapa.mapa[i][j]; // retorna uma celula escolhida
}

int NaoEhOFim(tJogo jogo) {
    // define se o jogo continua
    return (HaComida(jogo.mapa) && EstaViva(jogo.status));
}

// AUXILIARES DE STATUS

char ExtraiJogada(tStatus status) {
    return status.jogada;
}

int AchouDinheiro(char celula) {
    return celula == DINHEIRO;
}

int AchouFrutinha(char celula) {
    return celula == FRUTINHA;
}

int MorreuCobrinha(char celula) {
    return (celula == PAREDE || celula == CORPO);
}

int EstaViva(tStatus status) {
    return status.viva == 1;
}

int ComeuFrutinha(tStatus status) {
    return status.Frutinha == 1;
}

int ComeuDinheiro(tStatus status) {
    return status.Dinheiro == 1;
}

tStatus AumentaPontuacaoDinheiro(tStatus status) {
    status.ponto += DINHEIRO_PONTO;
    status.Dinheiro = 1;
    return status;
}

tStatus AumentaPontuacaoFrutinha(tStatus status) {
    status.ponto += FRUTINHA_PONTO;
    status.Frutinha = 1;
    return status;
}

// AUXILIARES DE MAPA

tMapa LimpaMapa(tMapa mapa, int coluna, int linha) {
    // esvazia uma coordenada
    char vazio = TELA_VAZIA;
    mapa.mapa[linha][coluna] = vazio;
    return mapa;
}

int NovaCelulaDestino(tMapa mapa, int i, int j) {
    return mapa.mapa[i][j]; // auxiliar para encontrar a celula destino
}

char CelulaDestino(tJogo jogo) {
    return jogo.celulaDestino;
}

tMapa AtualizaHeatMap(tMapa mapa, tCabeca cabeca) {
    // incrementa a posicao visitada
    int c = CabecaCobrinhaX(cabeca);
    int l = CabecaCobrinhaY(cabeca);
    mapa.heatMap[l][c]++;
    return mapa;
}


// AUXILIARES DE COBRINHA

int ExtraiCorpoCobrinhaX(tCobrinha cobrinha[], int i) {
    return cobrinha[i].x;
}

int ExtraiCorpoCobrinhaY(tCobrinha cobrinha[], int i) {
    return cobrinha[i].y;
}

char ExtraiCabeca(tCabeca cabeca) {
    return cabeca.cabeca;
}

int CabecaCobrinhaY(tCabeca cabeca) {
    return cabeca.y;
}

int CabecaCobrinhaX(tCabeca cabeca) {
    return cabeca.x;
}

tCobrinha NovaCoordenadaDaCabecaDaCobrinha(tCobrinha cobrinha, tCabeca cabeca) {
    // atualiza a coordenada da cabeca da cobrinha dentro do tipo cobrinha
    cobrinha.y = CabecaCobrinhaY(cabeca);
    cobrinha.x = CabecaCobrinhaX(cabeca);
    return cobrinha;
}

int TamanhoCobrinha(tJogo jogo) {
    return jogo.tamCobrinha;
}

tMapa InsereCabecaNoMapa(tMapa mapa, tCabeca cabeca) {
    int cobrinhaX = CabecaCobrinhaX(cabeca);
    int cobrinhaY = CabecaCobrinhaY(cabeca);
    char head = ExtraiCabeca(cabeca);
    mapa.mapa[cobrinhaY][cobrinhaX] = head; // modifica inserindo o caracter de cabeca escolhido no mapa
    return mapa;
}

void RecebeCoordenadaXAnterior(tCobrinha cobrinha[], int tam) {
    cobrinha[tam].x = cobrinha[tam - 1].x; // retorna uma coordenada anterior
}

void RecebeCoordenadaYAnterior(tCobrinha cobrinha[], int tam) {
    cobrinha[tam].y = cobrinha[tam - 1].y; // retorna uma coordenada anterior da cobrinha
}

tStatus AtualizaStatusDeCrescimento(tStatus status) {
    status.cresceu = 1;
    return status;
}
// AUXILIARES DE ESTATISTICAS

int ExtraiNumMovimentos(tEstatisticas estatisticas) {
    return estatisticas.nMovimentos;
}

tEstatisticas AtualizaEstatisticasQtddMovCima(tEstatisticas estatisticas) {
    estatisticas.nMovCima++;
    return estatisticas;
}

tEstatisticas AtualizaEstatisticasQtddMovDireita(tEstatisticas estatisticas) {
    estatisticas.nMovDireita++;
    return estatisticas;
}

tEstatisticas AtualizaEstatisticasQtddMovEsquerda(tEstatisticas estatisticas) {
    estatisticas.nMovEsquerda++;
    return estatisticas;
}

tEstatisticas AtualizaEstatisticasQtddMovBaixo(tEstatisticas estatisticas) {
    estatisticas.nMovBaixo++;
    return estatisticas;
}

tEstatisticas AtualizaEstatisticasQtddMovimentos(tEstatisticas estatisticas) {
    estatisticas.nMovimentos++;
    return estatisticas;
}

tEstatisticas AtualizaEstatisticasQtddMovSemPontuar(tEstatisticas estatisticas) {
    estatisticas.nMovSemPontuar++;
    return estatisticas;
}

//TRATA TUNEIS

char SalvaJogadaJogo(tStatus status) {
    return status.jogada;
}

tStatus ResetaJogadaJogo(tStatus status, char jogada) {
    status.jogada = jogada;
    return status;
}
tEstatisticas BackupDeEstatisticas(tEstatisticas estatisticas){
    return estatisticas;
}
tJogo TeleportaCobrinha(tJogo jogo) {
    jogo.cabeca = MoveCobraParaOProximoTunel(jogo.mapa, jogo.cabeca);
    char jogada = SalvaJogadaJogo(jogo.status); // faz backup da estatistica atual
    tEstatisticas backup = BackupDeEstatisticas(jogo.estatisticas); // faz backup da estatistica atual

    jogo.status = ResetaJogadaJogo(jogo.status, MOV_CONTINUE); // seta temporariamente o movimento de continue para o teleporte da cobrinha

    jogo = MoveCobrinha(jogo);
    jogo.estatisticas = BackupDeEstatisticas(backup); // Retorna ao valor da estatistica que era antes e da prosseguimento ao jogo
    jogo.status = ResetaJogadaJogo(jogo.status, jogada); // Retorna ao valor da jogada que era antes e da prosseguimento ao jogo
    return jogo;
}

int ACobraEstaNoTunel(tMapa mapa, int i, int j, int y, int x) {
    return mapa.mapa[i][j] == TUNEIS && (x != j || y != i); // Se for um tunel e a coordenada for diferente  

}

int AchouTunel(char celula) {
    return celula == TUNEIS;
}
// Encontra um outro tunel e atribui na cabeca da cobrinha

tCabeca MoveCobraParaOProximoTunel(tMapa mapa, tCabeca cabeca) {
    int i, j;
    int x = CabecaCobrinhaX(cabeca);
    int y = CabecaCobrinhaY(cabeca);

    for (i = 0; i < mapa.linhas; i++) {
        for (j = 0; j < mapa.colunas; j++) {

            if (ACobraEstaNoTunel(mapa, i, j, y, x)) {

                cabeca.x = j;
                cabeca.y = i;
            }
        }
    }

    return cabeca;
}


