#include <stdio.h>
#include "tarefas.h" // Inclui o cabeçalho que contém as declarações das funções relacionadas às tarefas

#define TOTAL 100

int main() {
    funcao fs[] = {criar, deletar, listar, salvar, carregar}; // Array de ponteiros para funções
    Tarefa tarefas[TOTAL]; // Vetor de tarefas
    int pos;
    ERROS erro = fs[4](tarefas, &pos); // Carrega as tarefas do arquivo
    if (erro != OK)
        pos = 0;

    int opcao;
    do {
        // Menu principal
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        opcao--;

        if (opcao > 2)
            printf("Opcao invalida\n");
        else if (opcao >= 0)
            fs[opcao](tarefas, &pos); // Chama a função correspondente à opção escolhida
        else
            printf("Sair...\n");
    } while (opcao >= 0);

    fs[3](tarefas, &pos); // Salva as tarefas no arquivo

    return 0;
}
