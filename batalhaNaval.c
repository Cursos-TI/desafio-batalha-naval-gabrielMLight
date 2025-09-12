#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int tabuleiro[10][10];
int agua = 0, navio = 1;
int navios = 0;

void inicializarTabuleiro() {
    for (int i = 0; i < 10; i++) tabuleiro[i][i] = agua;
}

void mostrarTabuleiro() {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) printf(" %i ", tabuleiro[y][x]);
        printf("\n");
    }
}

// insere um navio em uma coordenada e decide a orientação manualmente.
void inserirNavio(int orientacao, int col, int linha, int tamanho, int segundaTentativa) {
    navios++;
    if (orientacao == 1) {
        for (int i = linha; i < linha + tamanho; i++) {
            if (tabuleiro[i][col] == agua && linha + tamanho <= 9)
                tabuleiro[i][col] = navio;
            else if (segundaTentativa) {
                printf("Posição do Navio %i Inválida.\n", navios);
                navios--;
                break;
            }
            else {
                inserirNavio(0, col, linha, tamanho, 1);
                navios--;
                break;
            }
        }
    } else {
        for (int i = col; i < col + tamanho; i++) {
            if (tabuleiro[linha][i] == agua && col + tamanho <= 9)
                tabuleiro[linha][i] = navio;
            else if (segundaTentativa) {
                printf("Posição do Navio %i Inválida.\n", navios);
                navios--;
                break;
            }
            else {
                inserirNavio(1, col, linha, tamanho, 1);
                navios--;
                break;
            }
        }
    }
}

// insere um navio em uma coordenada e decide a orientação aleatóriamente.
void inserirNavioR(int col, int linha, int tamanho) {
    srand(time(0));
    int rng = rand() % 2 == 0;
    inserirNavio(rng, col, linha, tamanho, 0);
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

int main() {
    inicializarTabuleiro();

    printf("Tabuleiro :. \n\n");
    mostrarTabuleiro();
    configurarNavios();

    return 0;
}
