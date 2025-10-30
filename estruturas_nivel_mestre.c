#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h> // Necessário para usar tolower()

// Estrutura de dados Territorio
typedef struct {
    char nome[30];
    char cor[20];   // cor do dono (ex: "Vermelha", "Azul")
    int tropas;
} Territorio;

// Estrutura de Jogador (para armazenar cor e missão)
typedef struct {
    char cor[20];
    char* missao; // alocada dinamicamente
} Jogador;

/* 
 * atribuirMissao: sorteia uma missão e copia para o destino.
 */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]);
}

/*
 * exibirMissao: exibe a missão do jogador.
 */
void exibirMissao(char* missao) {
    printf("-> MISSÃO: %s\n", missao);
}

/*
 * atacar: simula ataque entre dois territórios.
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Ataque inválido: mesmos donos.\n");
        return;
    }
    if (atacante->tropas <= 1) {
        printf("Ataque inválido: atacante precisa ter mais de 1 tropa.\n");
        return;
    }

    printf("\nIniciando ataque: %s (%s, %d tropas) -> %s (%s, %d tropas)\n",
           atacante->nome, atacante->cor, atacante->tropas,
           defensor->nome, defensor->cor, defensor->tropas);

    int dadoAt = (rand() % 6) + 1;
    int dadoDf = (rand() % 6) + 1;
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAt, dadoDf);

    if (dadoAt > dadoDf) {
        printf("Atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        if (defensor->tropas < 1) defensor->tropas = 1;
        atacante->tropas -= 1;
        printf("%s agora pertence a %s com %d tropas. %s perdeu 1 tropa (fica com %d).\n",
               defensor->nome, defensor->cor, defensor->tropas,
               atacante->nome, atacante->tropas);
    } else {
        printf("Defensor resistiu!\n");
        atacante->tropas -= 1;
        printf("%s perde 1 tropa (fica com %d).\n", atacante->nome, atacante->tropas);
    }
}

/*
 * verificarMissao: verifica se o jogador cumpriu a missão.
 */
int verificarMissao(char* missao, Territorio* mapa, int tamanho, const char* corJogador) {
    char temp[200];
    strcpy(temp, missao);
    for (int i = 0; temp[i]; i++) temp[i] = (char)tolower((unsigned char)temp[i]);

    if (strstr(temp, "conquistar 3") != NULL) {
        int count = 0;
        for (int i = 0; i < tamanho; i++)
            if (strcasecmp(mapa[i].cor, corJogador) == 0) count++;
        return (count >= 3);
    }

    if (strstr(temp, "eliminar todas as tropas da cor") != NULL) {
        if (strstr(temp, "vermelha") != NULL) {
            for (int i = 0; i < tamanho; i++)
                if (strcasecmp(mapa[i].cor, "Vermelha") == 0) return 0;
            return 1;
        }
    }

    if (strstr(temp, "controlar mais da metade") != NULL) {
        int count = 0;
        for (int i = 0; i < tamanho; i++)
            if (strcasecmp(mapa[i].cor, corJogador) == 0) count++;
        return (count > (tamanho / 2));
    }

    if (strstr(temp, "menos de 3 tropas") != NULL) {
        for (int i = 0; i < tamanho; i++)
            if (mapa[i].tropas < 3 && strcasecmp(mapa[i].cor, corJogador) != 0)
                return 0;
        return 1;
    }

    if (strstr(temp, "capital") != NULL) {
        for (int i = 0; i < tamanho; i++)
            if (strcasecmp(mapa[i].nome, "Capital") == 0)
                return (strcasecmp(mapa[i].cor, corJogador) == 0);
    }

    return 0;
}

/*
 * exibirTerritorios: mostra o estado atual do mapa.
 */
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=== DADOS DOS TERRITÓRIOS ===\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] Nome: %s | Cor: %s | Tropas: %d\n", 
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("-----------------------------\n");
}

/*
 * liberarMemoria: libera mapa e missões.
 */
void liberarMemoria(Territorio* mapa, Jogador* jogadores, int numJogadores) {
    if (mapa) free(mapa);
    if (jogadores) {
        for (int i = 0; i < numJogadores; i++)
            free(jogadores[i].missao);
        free(jogadores);
    }
}

/*
 * cadastrarTerritorios: preenche o mapa.
 */
void cadastrarTerritorios(Territorio* mapa, int n) {
    printf("=== CADASTRO DE TERRITÓRIOS ===\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d nome: ", i + 1);
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor do exército (dono): ");
        scanf(" %19s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("\n");
    }
}

int main() {
    srand((unsigned int) time(NULL));

    int nTerritorios;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &nTerritorios);
    if (nTerritorios <= 0) {
        printf("Número inválido.\n");
        return 1;
    }

    Territorio* mapa = (Territorio*) calloc(nTerritorios, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar mapa.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, nTerritorios);
    exibirTerritorios(mapa, nTerritorios);

    // Vetor de missões
    char* missoesDisponiveis[] = {
        "Conquistar 3 territórios",
        "Eliminar todas as tropas da cor Vermelha",
        "Controlar mais da metade dos territórios",
        "Controlar todos os territórios com menos de 3 tropas",
        "Controlar o território 'Capital'"
    };
    int totalMissoes = sizeof(missoesDisponiveis) / sizeof(missoesDisponiveis[0]);

    // Jogadores
    int numJogadores;
    printf("Quantos jogadores (2 a 4)? ");
    scanf("%d", &numJogadores);
    if (numJogadores < 2 || numJogadores > 4) {
        printf("Número de jogadores inválido.\n");
        free(mapa);
        return 1;
    }

    Jogador* jogadores = (Jogador*) calloc(numJogadores, sizeof(Jogador));
    if (!jogadores) {
        printf("Erro ao alocar jogadores.\n");
        free(mapa);
        return 1;
    }

    // Atribui missões
    for (int i = 0; i < numJogadores; i++) {
        printf("Jogador %d - cor do exército: ", i + 1);
        scanf(" %19s", jogadores[i].cor);

        jogadores[i].missao = (char*) malloc(200 * sizeof(char));
        if (!jogadores[i].missao) {
            printf("Erro ao alocar missão.\n");
            liberarMemoria(mapa, jogadores, numJogadores);
            return 1;
        }

        atribuirMissao(jogadores[i].missao, missoesDisponiveis, totalMissoes);
        printf("\nJogador %d (%s) recebeu sua missão:\n", i + 1, jogadores[i].cor);
        exibirMissao(jogadores[i].missao);
        printf("\n");
    }

    // Loop principal
    int vencedor = -1;
    int turno = 0;
    int opcao;

    do {
        int jogadorAtual = turno % numJogadores;
        printf("\n=== Turno do jogador %d (%s) ===\n", jogadorAtual + 1, jogadores[jogadorAtual].cor);
        printf("1 - Atacar\n2 - Exibir territórios\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int idxAt, idxDf;
            printf("Território atacante (1 a %d): ", nTerritorios);
            scanf("%d", &idxAt);
            printf("Território defensor (1 a %d): ", nTerritorios);
            scanf("%d", &idxDf);

            if (idxAt < 1 || idxAt > nTerritorios || idxDf < 1 || idxDf > nTerritorios) {
                printf("Índices inválidos.\n");
            } else {
                Territorio* at = &mapa[idxAt - 1];
                if (strcasecmp(at->cor, jogadores[jogadorAtual].cor) != 0) {
                    printf("Você não controla esse território!\n");
                } else {
                    atacar(at, &mapa[idxDf - 1]);

                    // Verifica missões após cada ataque
                    for (int j = 0; j < numJogadores; j++) {
                        if (verificarMissao(jogadores[j].missao, mapa, nTerritorios, jogadores[j].cor)) {
                            vencedor = j;
                            break;
                        }
                    }
                    if (vencedor != -1) break;
                }
            }
        } else if (opcao == 2) {
            exibirTerritorios(mapa, nTerritorios);
        } else if (opcao == 0) {
            printf("Saindo do jogo...\n");
            break;
        } else {
            printf("Opção inválida.\n");
        }

        turno++;
    } while (1);

    if (vencedor != -1) {
        printf("\n=====================================\n");
        printf("MISSÃO CUMPRIDA! Jogador %d (%s) venceu!\n", 
               vencedor + 1, jogadores[vencedor].cor);
        printf("Missão: %s\n", jogadores[vencedor].missao);
        printf("=====================================\n");
    }

    liberarMemoria(mapa, jogadores, numJogadores);
    printf("Memória liberada. Fim do programa.\n");
    return 0;
}
