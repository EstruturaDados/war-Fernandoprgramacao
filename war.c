#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 4
#define MAX_MISSOES 5

// Estrutura do Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para sortear e atribuir missão
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]);
}

// Função para exibir missão (passagem por valor)
void exibirMissao(const char* missao) {
    printf("\nSua missao estrategica: %s\n", missao);
}

// Função para simular ataque entre territorios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("%s e %s sao do mesmo jogador. Ataque invalido.\n", atacante->nome, defensor->nome);
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("%s (atacante) rolou %d | %s (defensor) rolou %d\n",
           atacante->nome, dadoAtacante, defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        int tropasConquistadas = atacante->tropas / 2;
        defensor->tropas = tropasConquistadas;
        strcpy(defensor->cor, atacante->cor);
        atacante->tropas -= tropasConquistadas;
        printf("%s conquistou %s com %d tropas!\n", atacante->nome, defensor->nome, defensor->tropas);
    } else {
        atacante->tropas--;
        printf("%s perdeu 1 tropa. Tropas restantes: %d\n", atacante->nome, atacante->tropas);
    }
}

// Função para exibir mapa atual
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\nMapa atual:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%s | Cor: %s | Tropas: %d\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função simples de verificação de missão (lógica inicial)
int verificarMissao(const char* missao, Territorio* mapa, int tamanho) {
    if (strcmp(missao, "Ter pelo menos 3 tropas em cada territorio") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas < 3) return 0;
        }
        return 1;
    }
    if (strcmp(missao, "Conquistar Territorio D") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].nome, "Territorio D") == 0 && strcmp(mapa[i].cor, "Jogador") == 0)
                return 1;
        }
        return 0;
    }
    return 0; // outras missões podem ser adicionadas
}

// Liberar memoria alocada dinamicamente
void liberarMemoria(Territorio* mapa, char* missao) {
    free(missao);
    free(mapa);
}

int main() {
    srand(time(NULL));

    // Alocar memoria dinamica para territorios
    Territorio* mapa = (Territorio*)malloc(sizeof(Territorio) * MAX_TERRITORIOS);

    // Inicializacao dos territorios
    strcpy(mapa[0].nome, "Territorio A"); strcpy(mapa[0].cor, "Inimigo"); mapa[0].tropas = 2;
    strcpy(mapa[1].nome, "Territorio B"); strcpy(mapa[1].cor, "Jogador"); mapa[1].tropas = 4;
    strcpy(mapa[2].nome, "Territorio C"); strcpy(mapa[2].cor, "Jogador"); mapa[2].tropas = 5;
    strcpy(mapa[3].nome, "Territorio D"); strcpy(mapa[3].cor, "Inimigo"); mapa[3].tropas = 1;

    // Vetor de missoes
    char* missoes[MAX_MISSOES] = {
        "Ter pelo menos 3 tropas em cada territorio",
        "Conquistar Territorio D",
        "Eliminar todas tropas da cor Inimigo",
        "Controlar Territorio A e B",
        "Ter mais tropas que o inimigo em Territorio C"
    };

    // Alocar memoria para a missao do jogador
    char* missaoJogador = (char*)malloc(100 * sizeof(char));
    atribuirMissao(missaoJogador, missoes, MAX_MISSOES);

    exibirMissao(missaoJogador);

    // Exibir mapa inicial
    exibirMapa(mapa, MAX_TERRITORIOS);

    // Simular alguns ataques
    atacar(&mapa[1], &mapa[0]);
    atacar(&mapa[2], &mapa[3]);

    // Exibir mapa depois dos ataques
    exibirMapa(mapa, MAX_TERRITORIOS);

    // Verificar missao
    if (verificarMissao(missaoJogador, mapa, MAX_TERRITORIOS)) {
        printf("\nMissao cumprida! Parabens!\n");
    } else {
        printf("\nMissao ainda nao cumprida.\n");
    }

    // Liberar memoria
    liberarMemoria(mapa, missaoJogador);

    return 0;
}
