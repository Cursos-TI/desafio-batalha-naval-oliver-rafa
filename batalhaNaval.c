#include <stdio.h>

#define TAM 10       // Tamanho do tabuleiro 10x10
#define TAM_NAVIO 3  // Cada navio ocupa 3 posições
#define NAVIO 3      // Valor que representa o navio no tabuleiro
#define AGUA 0       // Valor que representa água no tabuleiro

int main() {
    int tabuleiro[TAM][TAM];

    // Coordenadas iniciais dos navios
    int linhaNavioVertical = 2, colunaNavioVertical = 4;
    int linhaNavioHorizontal = 6, colunaNavioHorizontal = 1;

    // Vetores que representam os navios (não são obrigatórios, mas usados para entender a lógica)
    int navioVertical[TAM_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioHorizontal[TAM_NAVIO] = {NAVIO, NAVIO, NAVIO};

    // -----------------------------
    // Inicializando o tabuleiro com água
    // -----------------------------
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // -----------------------------
    // Posicionando o navio vertical
    // -----------------------------
    // Para validação: o navio deve caber dentro do tabuleiro
    if (linhaNavioVertical + TAM_NAVIO <= TAM) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linhaNavioVertical + i][colunaNavioVertical] = navioVertical[i];
        }
    } else {
        printf("Erro: Navio vertical não cabe no tabuleiro!\n");
        return 1;
    }

    // -----------------------------
    // Posicionando o navio horizontal
    // -----------------------------
    // Validação: o navio deve caber dentro do tabuleiro e não sobrepor outro
    if (colunaNavioHorizontal + TAM_NAVIO <= TAM) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaNavioHorizontal][colunaNavioHorizontal + i] == NAVIO) {
                printf("Erro: Sobreposição de navios detectada!\n");
                return 1;
            }
            tabuleiro[linhaNavioHorizontal][colunaNavioHorizontal + i] = navioHorizontal[i];
        }
    } else {
        printf("Erro: Navio horizontal não cabe no tabuleiro!\n");
        return 1;
    }

    // -----------------------------
    // Exibindo o tabuleiro
    // -----------------------------
    printf("\nTabuleiro de Batalha Naval:\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
