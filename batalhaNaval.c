#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int tabuleiro[10][10];
int agua = 0, navio = 3;
int navios = 0;

void inicializarTabuleiro() {
    for (int i = 0; i < 10; i++) tabuleiro[i][i] = agua;
}

int cone[3][5] = {
    {0, 0, 5, 0, 0},
    {0, 5, 5, 5, 0},
    {5, 5, 5, 5, 5},
};

int octaedro[3][5] = {
    {0, 0, 5, 0, 0},
    {0, 5, 5, 5, 0},
    {0, 0, 5, 0, 0},
};

int cruz[3][5] = {
    {0, 0, 5, 0, 0},
    {5, 5, 5, 5, 5},
    {0, 0, 5, 0, 0},
};


void mostrarTabuleiro() {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) printf(" %i ", tabuleiro[y][x]);
        printf("\n");
    }
}

// insere um navio em uma coordenada e decide a orientação "manualmente".
void inserirNavio(int orientacao, int col, int linha, int tamanho, int segundaTentativa) {
    navios++;
    if (orientacao == 1) {
        for (int i = linha; i < linha + tamanho; i++) {
            // validação de posicionamento
            if (tabuleiro[i][col] == agua && linha + tamanho <= 9)
                tabuleiro[i][col] = navio;
            else if (segundaTentativa) {
                printf("\nPosição do Navio %i Inválida.\n", navios);
                navios--;
                break;
            }
            else {
                navios--;
                inserirNavio(0, col, linha, tamanho, 1);
                break;
            }
        }
    } else {
        for (int i = col; i < col + tamanho; i++) {
            if (tabuleiro[linha][i] == agua && col + tamanho <= 9)
                tabuleiro[linha][i] = navio;
            else if (segundaTentativa) {
                printf("\nPosição do Navio %i Inválida.\n", navios);
                navios--;
                break;
            }
            else {
                navios--;
                inserirNavio(1, col, linha, tamanho, 1);
                break;
            }
        }
    }
}

// insere um navio em uma coordenada e decide a orientação "manualmente", só que na diagonal.
void inserirNavioDiagonal(int orientacao, int col, int linha, int tamanho, int segundaTentativa) {
    navios++;
    if (orientacao == 1) {
        for (int i = linha, j = col; i < linha + tamanho; i++, j++) {
            // validação de posicionamento
            if (tabuleiro[i][j] == agua && linha + tamanho <= 9 && col + tamanho <= 9)
                tabuleiro[i][j] = navio;
            else if (segundaTentativa) {
                printf("\nPosição do Navio %i Inválida.\n", navios);
                navios--;
                break;
            }
            else {
                navios--;
                inserirNavioDiagonal(0, col, linha, tamanho, 1);
                break;
            }
        }
    } else {
        for (int i = linha, j = col; j < col + tamanho; i--, j++) {
            // validação de posicionamento
            if (tabuleiro[i][j] == agua && linha - tamanho + 1 >= 0 && col + tamanho <= 9)
                tabuleiro[i][j] = navio;
            else if (segundaTentativa) {
                printf("\nPosição do Navio %i Inválida.\n", navios);
                navios--;
                break;
            }
            else {
                navios--;
                inserirNavioDiagonal(1, col, linha, tamanho, 1);
                break;
            }
        }
    }
}

// insere um navio em uma coordenada e decide a orientação aleatóriamente.
void inserirNavioR(int col, int linha, int tamanho) {
    int rng = rand() % 2 == 0;
    // a cada dois navios um deles será diagonal
    if (navios % 2 != 0) inserirNavioDiagonal(rng, col, linha, tamanho, 0);
    else inserirNavio(rng, col, linha, tamanho, 0);
}

// insere uma matriz no tabuleiro
void inserirMatriz(int matriz[3][5], int linha, int col) {
    linha -= 1;
    col -= 2;
    
    // tentei achar uma forma de diretamente inserir uma matriz dentro da outra, mas dá erro.
    for (int i = 0, j = 0, l = linha, c = col; i < 3, j < 5, l < l + 3, c < c + 5; i++, j++, l++, c++) {
        if (tabuleiro[l][c] != navio) tabuleiro[l][c] = matriz[i][j]; // SEGMENTATION FAULT [???]
    }
}

void configurarNavios() {
    printf("\nQuantos navios gostaria de adicionar?\n");
    int quantidade;
    scanf(" %i", &quantidade);

    printf("Ok, hora de posicionar os navios.\n");

    for (int i = 0; i < quantidade; i++) {
        int col, linha, tamanho;

        printf("\nNAVIO %i :.\n", i + 1);
        printf("Coluna: ");
        scanf(" %d", &col);
        printf("Linha: ");
        scanf(" %d", &linha);
        printf("Tamanho: ");
        scanf(" %d", &tamanho);

        inserirNavioR(col, linha, tamanho);
    }

    printf("\n%i/%i Navios posicionados com sucesso.\n", navios, quantidade);
    printf("Confira o tabuleiro abaixo :.\n\n");
    mostrarTabuleiro();
}

void lancarAtaque() {
    int linha, col;
    int ataque;
    printf("\nHora de lançar um ataque. Escolha qual e onde lançá-lo.\n");
    printf(" 1 - Cone\n 2 - Cruz\n 3 - Octaedro\n");
    scanf(" %i", &ataque);
    printf("Linha: ");
    scanf(" %i", &linha);
    printf("Coluna: ");
    scanf(" %i", &col);

    printf("\nAtacando...\n");

    switch (ataque) {
        case 1:
            inserirMatriz(cone, linha, col);
            break;
        case 2:
            inserirMatriz(cruz, linha, col);
            break;
        case 3:
            inserirMatriz(octaedro, linha, col);
            break;
        default:
            printf("\nAtaque Inválido.\n");
            lancarAtaque();
            break;
    }

    mostrarTabuleiro();

    printf("\nLançar outro ataque? (s/n)\n");
    char response;
    scanf(" %c", &response);

    switch (response) {
        case 's':
            lancarAtaque();
            break;
        default:
            printf("Encerrando... Resultado final :.\n");
            mostrarTabuleiro();
            break;
    }
}

int main() {
    inicializarTabuleiro();
    srand(time(0));
    printf("Tabuleiro :. \n\n");
    mostrarTabuleiro();
    configurarNavios();

    //lancarAtaque();
    // cancelado por causar erro que não sei resolver [segmentation fault em inserirMatriz()].

    return 0;
}
