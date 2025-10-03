#include <stdio.h>
#include <stdbool.h>
#include <math.h> // Para usar a função fabs (valor absoluto)

// --- CONSTANTES GERAIS 
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5 // Define o tamanho das matrizes de habilidade (5x5)

//  VALORES NA MATRIZ ---
#define AGUA 0
#define NAVIO 3
#define HABILIDADE_MARCA 5 // Valor para marcar a área de efeito no tabuleiro

// ORIENTAÇÕES DE MOVIMENTO (para posicionamento dos navios) 
// 0: Horizontal, 1: Vertical, 2: Diagonal Crescente, 3: Diagonal Decrescente

//  FUNÇÕES DE LÓGICA DE NAVIOS (Do desafio anterior) 
// ... (inicializarTabuleiro, calcularProximaPosicao, validarPosicionamento, posicionarNavio)
// (Mantidas do código anterior para posicionar os navios)

void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Funções de posicionamento e validação de navios (simplificadas ou omitidas aqui por espaço)
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int r, int c, int tamanho, int orientacao);
bool validarPosicionamento(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int r, int c, int tamanho, int orientacao);
void calcularProximaPosicao(int linha_inicial, int coluna_inicial, int passo, int orientacao, int *linha_out, int *coluna_out);
// ... (Fim das funções de navios)


// - 1. GERAÇÃO DAS MATRIZES DE HABILIDADE (Lógica Condicional) --

/**
 * Cria a forma de CONE na matriz de habilidade (Apontando para baixo).
 * O cone é um triângulo isósceles que se expande para baixo.
 */
void criarCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2; // Para uma matriz 5x5, centro é 2
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) { // Linhas
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) { // Colunas
            // A largura do cone na linha 'i' é (2*i + 1), centrada.
            // A distância horizontal do centro é menor ou igual à linha 'i'.
            // Ex: Na linha 0, largura 1. Na linha 2, largura 5.
            if (fabs(j - centro) <= i) {
                habilidade[i][j] = 1; // Afetado
            } else {
                habilidade[i][j] = 0; // Não Afetado
            }
        }
    }
}

/**
 * Cria a forma de CRUZ na matriz de habilidade (Ponto de origem no centro).
 */
void criarCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Atinge se a coluna for o centro OU a linha for o centro.
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

/**
 * Cria a forma de OCTAEDRO (Losango) na matriz de habilidade (Ponto de origem no centro).
 */
void criarOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // A condição do losango é que a soma das distâncias absolutas (Manhattan distance)
            // do centro seja menor ou igual à distância máxima do centro.
            // Ex: |i - centro| + |j - centro| <= centro
            if (fabs(i - centro) + fabs(j - centro) <= centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}


// --- 2. INTEGRAÇÃO DA HABILIDADE NO TABULEIRO ---

/**
 * Sobrepõe a matriz de habilidade no tabuleiro principal, centrada no ponto (origem_r, origem_c).
 * @param tabuleiro O tabuleiro 10x10.
 * @param habilidade A matriz 5x5 da habilidade.
 * @param origem_r Linha de origem/centro da habilidade no tabuleiro.
 * @param origem_c Coluna de origem/centro da habilidade no tabuleiro.
 */
void aplicarHabilidade(
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
    int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
    int origem_r,
    int origem_c
) {
    int offset = TAMANHO_HABILIDADE / 2; // Deslocamento do centro para a borda (2 para 5x5)

    // Loops aninhados para percorrer a matriz de habilidade.
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {

            // Se a posição da habilidade está marcada (valor 1):
            if (habilidade[i][j] == 1) {

                // Cálculo das coordenadas correspondentes no tabuleiro
                // Subtrai o offset (2) para centralizar a habilidade na origem.
                int tabuleiro_r = origem_r + (i - offset);
                int tabuleiro_c = origem_c + (j - offset);

                // Condicional para garantir que a área de efeito esteja dentro dos LIMITES do tabuleiro.
                if (tabuleiro_r >= 0 && tabuleiro_r < TAMANHO_TABULEIRO &&
                    tabuleiro_c >= 0 && tabuleiro_c < TAMANHO_TABULEIRO) {

                    // Se a posição já for um Navio (3), não sobrescreve.
                    // Caso contrário, marca a posição como HABILIDADE_MARCA (5).
                    if (tabuleiro[tabuleiro_r][tabuleiro_c] != NAVIO) {
                        tabuleiro[tabuleiro_r][tabuleiro_c] = HABILIDADE_MARCA;
                    }
                }
            }
        }
    }
}


/**
 * Exibe a matriz do tabuleiro no console, usando caracteres visuais.
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // ... (código de exibição com cabeçalhos de linhas e colunas)
    printf("     ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    printf("   -----------------------------------\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d |", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == NAVIO) {
                printf(" %c ", 'N'); // Navio (3)
            } else if (tabuleiro[i][j] == HABILIDADE_MARCA) {
                printf(" %c ", 'X'); // Área de Efeito (5)
            } else {
                printf(" %c ", '.'); // Água/Vazio (0)
            }
        }
        printf("\n");
    }
}

int main() {
    printf("\n\n####################################\n");
    printf("--- DESAFIO MESTRE: HABILIDADES ---\n");
    printf("####################################\n");

    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // --- 1. POSICIONAR NAVIOS (Base do tabuleiro) ---
    // Posicionamento Hardcoded de 4 Navios (2 Ortogonais, 2 Diagonais)
    // Usando uma versão simplificada do posicionamento anterior para fins de demonstração:
    tabuleiro[1][1] = tabuleiro[1][2] = tabuleiro[1][3] = NAVIO; // Horizontal
    tabuleiro[4][7] = tabuleiro[5][7] = tabuleiro[6][7] = NAVIO; // Vertical
    tabuleiro[6][0] = tabuleiro[7][1] = tabuleiro[8][2] = NAVIO; // Diagonal Crescente
    tabuleiro[0][9] = tabuleiro[1][8] = tabuleiro[2][7] = NAVIO; // Diagonal Decrescente


    // --- 2. GERAÇÃO DAS MATRIZES DE HABILIDADE (5x5) ---
    int matriz_cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matriz_cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matriz_octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    criarCone(matriz_cone);
    criarCruz(matriz_cruz);
    criarOctaedro(matriz_octaedro);

    // --- 3. APLICAR HABILIDADES NO TABULEIRO ---
    // Navio em (4, 7), Diag. Cresc. começa em (6, 0), Diag. Decr. começa em (0, 9)

    // Habilidade 1: Octaedro (Losango) no centro (5, 5)
    aplicarHabilidade(tabuleiro, matriz_octaedro, 5, 5);

    // Habilidade 2: Cone (apontando para baixo) centrada em (2, 2)
    aplicarHabilidade(tabuleiro, matriz_cone, 2, 2);

    // Habilidade 3: Cruz centrada em (7, 1)
    aplicarHabilidade(tabuleiro, matriz_cruz, 7, 1);


    // --- 4. EXIBIÇÃO FINAL DO TABULEIRO ---
    printf("\n--- TABULEIRO COM NAVIOS ('N') E AREAS DE EFEITO ('X') ---\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}