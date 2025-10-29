#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura de dados Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os territórios dinamicamente
void cadastrarTerritorios(Territorio* mapa, int n) {
    printf("=== CADASTRO DE TERRITÓRIOS ===\n\n");
    for (int i = 0; i < n; i++) {
        printf("Cadastro do território %d:\n", i + 1);
        printf("Digite o nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Digite a cor do exército: ");
        scanf(" %s", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);

        printf("\n");
    }
}

// Função para exibir todos os territórios
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=== DADOS DOS TERRITÓRIOS ===\n\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("-----------------------------\n");
    }
}

// Função que simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n O ataque não pode ser feito entre territórios da mesma cor!\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("\n O território atacante precisa de mais de 1 tropa para atacar!\n");
        return;
    }

    printf("\n Iniciando ataque de %s (%s) contra %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtacante = (rand() % 6) + 1; // valor entre 1 e 6
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf(" O atacante venceu a batalha!\n");

        // Território defensor muda de dono
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2; // metade das tropas transferida

        // Atacante perde uma tropa no ataque
        atacante->tropas -= 1;

        printf("⚔️ %s agora pertence ao exército %s com %d tropas!\n",
               defensor->nome, defensor->cor, defensor->tropas);
    } else {
        printf("❌ O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1; // atacante perde uma tropa
    }
}

// Função para liberar a memória alocada dinamicamente
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL)); // inicializa o gerador de números aleatórios

    int n;
    printf("Informe o número de territórios que deseja cadastrar: ");
    scanf("%d", &n);

    // Alocação dinâmica do vetor de territórios
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Cadastro e exibição inicial
    cadastrarTerritorios(mapa, n);
    exibirTerritorios(mapa, n);

    int opcao;
    do {
        printf("\n=== MENU DE AÇÕES ===\n");
        printf("1 - Realizar um ataque\n");
        printf("2 - Exibir territórios\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int iAtacante, iDefensor;
            printf("\nEscolha o número do território atacante: ");
            scanf("%d", &iAtacante);
            printf("Escolha o número do território defensor: ");
            scanf("%d", &iDefensor);

            if (iAtacante < 1 || iAtacante > n || iDefensor < 1 || iDefensor > n) {
                printf(" Escolha inválida de território!\n");
            } else {
                atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);
            }

        } else if (opcao == 2) {
            exibirTerritorios(mapa, n);
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    printf("\nMemória liberada. Fim do programa!\n");

    return 0;
}
