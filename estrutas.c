#include <stdio.h>
#include <string.h>

/*
 * Estrutura de dados Territorio:
 * Armazena informações sobre um território, incluindo:
 * - nome: nome do território
 * - cor: cor do exército que o representa
 * - tropas: número de tropas alocadas no território
 */
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Vetor que armazenará 5 territórios
    struct Territorio territorios[5];

    printf("=== CADASTRO DE TERRITÓRIOS ===\n\n");

    // Laço para entrada dos dados
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do território %d:\n", i + 1);

        // Lê o nome do território
        printf("Digite o nome do território: ");
        scanf(" %[^\n]", territorios[i].nome); // Lê até o ENTER, inclusive espaços

        // Lê a cor do exército
        printf("Digite a cor do exército: ");
        scanf(" %s", territorios[i].cor);

        // Lê a quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n"); // Linha em branco para melhor legibilidade
    }

    // Exibição dos dados cadastrados
    printf("=== DADOS DOS TERRITÓRIOS CADASTRADOS ===\n\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}
