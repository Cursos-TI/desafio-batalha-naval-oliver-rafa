#include <stdio.h>

#define TAM 10       // Tamanho do tabuleiro 10x10
#define TAM_NAVIO 3  // Cada navio ocupa 3 posições
#define NAVIO 3      // Valor que representa navio
#define AGUA 0       // Valor que representa água

// Função para inicializar o tabuleiro com 0
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se uma célula está livre
int posicaoLivre(int tabuleiro[TAM][TAM], int linha, int coluna) {
    return tabuleiro[linha][coluna] == AGUA;
}

// Função para posicionar um navio vertical
int posicionarNavioVertical(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (linha + TAM_NAVIO > TAM) return 0; // Não cabe no tabuleiro

    // Valida sobreposição
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (!posicaoLivre(tabuleiro, linha + i, coluna)) return 0;
    }

    // Posiciona navio
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = NAVIO;
    }
    return 1;
}

// Função para posicionar um navio horizontal
int posicionarNavioHorizontal(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (coluna + TAM_NAVIO > TAM) return 0; // Não cabe no tabuleiro

    // Valida sobreposição
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (!posicaoLivre(tabuleiro, linha, coluna + i)) return 0;
    }

    // Posiciona navio
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = NAVIO;
    }
    return 1;
}

// Função para posicionar um navio na diagonal crescente (\)
int posicionarNavioDiagonalCrescente(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (linha + TAM_NAVIO > TAM || coluna + TAM_NAVIO > TAM) return 0; // Não cabe

    for (int i = 0; i < TAM_NAVIO; i++) {
        if (!posicaoLivre(tabuleiro, linha + i, coluna + i)) return 0;
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = NAVIO;
    }
    return 1;
}

// Função para posicionar um navio na diagonal decrescente (/)
int posicionarNavioDiagonalDecrescente(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (linha + TAM_NAVIO > TAM || coluna - (TAM_NAVIO - 1) < 0) return 0; // Não cabe

    for (int i = 0; i < TAM_NAVIO; i++) {
        if (!posicaoLivre(tabuleiro, linha + i, coluna - i)) return 0;
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = NAVIO;
    }
    return 1;
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro de Batalha Naval:\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Posiciona os navios
    if (!posicionarNavioVertical(tabuleiro, 1, 1)) {
        printf("Erro ao posicionar navio vertical!\n");
    }

    if (!posicionarNavioHorizontal(tabuleiro, 4, 4)) {
        printf("Erro ao posicionar navio horizontal!\n");
    }

    if (!posicionarNavioDiagonalCrescente(tabuleiro, 0, 7)) {
        printf("Erro ao posicionar navio diagonal crescente!\n");
    }

    if (!posicionarNavioDiagonalDecrescente(tabuleiro, 5, 9)) {
        printf("Erro ao posicionar navio diagonal decrescente!\n");
    }

    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}
