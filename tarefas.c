#include <stdio.h>
#include <string.h>
#include "tarefas.h" // Inclui o cabeçalho que contém as definições das funções e as estruturas de dados

// Função para criar uma nova tarefa
ERROS criar(Tarefa tarefas[], int *pos) {
    if (*pos >= TOTAL)
        return MAX_TAREFA; // Retorna MAX_TAREFA se o limite de tarefas foi atingido

    printf("Entre com a prioridade (entre 1 e 10): ");
    scanf("%d", &tarefas[*pos].prioridade); // Lê a prioridade da tarefa

    while (tarefas[*pos].prioridade < 1 || tarefas[*pos].prioridade > 10) {
        printf("Prioridade fora do intervalo permitido. Entre com um valor entre 1 e 10: ");
        scanf("%d", &tarefas[*pos].prioridade); // Verifica se a prioridade está dentro do intervalo permitido
    }

    clearBuffer(); // Limpa o buffer do teclado

    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, 100, stdin); // Lê a categoria da tarefa
    tarefas[*pos].categoria[strcspn(tarefas[*pos].categoria, "\n")] = '\0'; // Remove a quebra de linha

    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, 300, stdin); // Lê a descrição da tarefa
    tarefas[*pos].descricao[strcspn(tarefas[*pos].descricao, "\n")] = '\0'; // Remove a quebra de linha

    *pos = *pos + 1;

    return OK; // Retorna OK para indicar sucesso na criação da tarefa
}

// Função para deletar uma tarefa
ERROS deletar(Tarefa tarefas[], int *pos) {
    if (*pos == 0)
        return SEM_TAREFAS; // Retorna SEM_TAREFAS se não houver tarefas

    int pos_deletar;
    printf("Entre com a posicao da tarefa a ser deletada: ");
    scanf("%d", &pos_deletar);
    pos_deletar--;

    if (pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO; // Retorna NAO_ENCONTRADO se a posição for inválida

    for (int i = pos_deletar; i < *pos; i++) {
        // Desloca as tarefas para preencher o espaço da tarefa deletada
        tarefas[i].prioridade = tarefas[i + 1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i + 1].categoria);
        strcpy(tarefas[i].descricao, tarefas[i + 1].descricao);
    }

    *pos = *pos - 1;

    return OK; // Retorna OK para indicar sucesso na deleção da tarefa
}

// Função para listar todas as tarefas
ERROS listar(Tarefa tarefas[], int *pos) {
    if (*pos == 0)
        return SEM_TAREFAS; // Retorna SEM_TAREFAS se não houver tarefas

    // Itera sobre todas as tarefas e imprime suas informações
    for (int i = 0; i < *pos; i++) {
        printf("Pos: %d\t", i + 1);
        printf("Prioridade: %d\t", tarefas[i].prioridade);
        printf("Categoria: %s\t", tarefas[i].categoria);
        printf("Descricao: %s\n", tarefas[i].descricao);
    }

    return OK; // Retorna OK para indicar sucesso na listagem das tarefas
}

// Função para salvar as tarefas em um arquivo binário
ERROS salvar(Tarefa tarefas[], int *pos) {
    FILE *f = fopen("tarefas.bin", "wb");
    if (f == NULL)
        return ABRIR; // Retorna ABRIR em caso de erro na abertura do arquivo

    int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
    if (qtd == 0)
        return ESCREVER; // Retorna ESCREVER em caso de erro na escrita das tarefas

    qtd = fwrite(pos, 1, sizeof(int), f);
    if (qtd == 0)
        return ESCREVER; // Retorna ESCREVER em caso de erro na escrita da posição

    if (fclose(f))
        return FECHAR; // Retorna FECHAR em caso de erro no fechamento do arquivo

    return OK; // Retorna OK para indicar sucesso ao salvar as tarefas
}

// Função para carregar as tarefas de um arquivo binário
ERROS carregar(Tarefa tarefas[], int *pos) {
    FILE *f = fopen("tarefas.bin", "rb");
    if (f == NULL)
        return ABRIR; // Retorna ABRIR em caso de erro na abertura do arquivo

    int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
    if (qtd == 0)
        return LER; // Retorna LER em caso
