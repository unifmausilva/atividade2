#include <stdio.h>   // Inclui o cabeçalho padrão para entrada e saída em C
#include <string.h>  // Inclui o cabeçalho para manipulação de strings em C
#include "tarefas.h" // Inclui o cabeçalho que contém as declarações das funções relacionadas às tarefas

// Função para criar uma nova tarefa
ERROS criar(Tarefa tarefas[], int *pos){
    // Verifica se o vetor de tarefas está cheio
    if(*pos >= TOTAL)
        return MAX_TAREFA;

    // Solicita a prioridade da tarefa ao usuário
    printf("Entre com a prioridade: ");
    scanf("%d", &tarefas[*pos].prioridade);
    clearBuffer(); // Limpa o buffer do teclado

    // Solicita a categoria da tarefa ao usuário
    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, 100, stdin); // Lê a categoria da tarefa

    // Solicita a descrição da tarefa ao usuário
    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, 300, stdin); // Lê a descrição da tarefa

    // Incrementa a posição atual
    *pos = *pos + 1;

    return OK; // Retorna OK para indicar sucesso na criação da tarefa
}

// Função para deletar uma tarefa
ERROS deletar(Tarefa tarefas[], int *pos){
    // Verifica se existem tarefas
    if(*pos == 0)
        return SEM_TAREFAS;

    // Solicita a posição da tarefa a ser deletada
    int pos_deletar;
    printf("Entre com a posicao da tarefa a ser deletada: ");
    scanf("%d", &pos_deletar);
    pos_deletar--; // Ajusta a posição para o índice do array
    if(pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO; // Retorna NAO_ENCONTRADO se a posição for inválida

    // Desloca as tarefas para preencher o espaço da tarefa deletada
    for(int i = pos_deletar; i < *pos; i++){
        tarefas[i].prioridade = tarefas[i+1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
        strcpy(tarefas[i].descricao,  tarefas[i+1].descricao);
    }

    // Decrementa a posição atual
    *pos = *pos - 1;

    return OK; // Retorna OK para indicar sucesso na deleção da tarefa
}

// Função para listar todas as tarefas
ERROS listar(Tarefa tarefas[], int *pos){
    // Verifica se existem tarefas
    if(*pos == 0)
        return SEM_TAREFAS;

    // Itera sobre todas as tarefas e imprime suas informações
    for(int i=0; i<*pos; i++){
        printf("Pos: %d\t", i+1);
        printf("Prioridade: %d\t", tarefas[i].prioridade);
        printf("Categoria: %s\t", tarefas[i].categoria);
        printf("Descricao: %s\n", tarefas[i].descricao);
    }

    return OK; // Retorna OK para indicar sucesso na listagem das tarefas
}

// Função para salvar as tarefas em um arquivo binário
ERROS salvar(Tarefa tarefas[], int *pos){
    // Abre o arquivo binário para escrita
    FILE *f = fopen("tarefas.bin", "wb");
    if(f == NULL)
        return ABRIR; // Retorna ABRIR em caso de erro na abertura do arquivo

    // Escreve as tarefas no arquivo
    int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return ESCREVER; // Retorna ESCREVER em caso de erro na escrita das tarefas

    // Escreve a posição atual no arquivo
    qtd = fwrite(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return ESCREVER; // Retorna ESCREVER em caso de erro na escrita da posição

    // Fecha o arquivo
    if(fclose(f))
        return FECHAR; // Retorna FECHAR em caso de erro no fechamento do arquivo

    return OK; // Retorna OK para indicar sucesso ao salvar as tarefas
}

// Função para carregar as tarefas de um arquivo binário
ERROS carregar(Tarefa tarefas[], int *pos){
    // Abre o arquivo binário para leitura
    FILE *f = fopen("tarefas.bin", "rb");
    if(f == NULL)
        return ABRIR; // Retorna ABRIR em caso de erro na abertura do arquivo

    // Lê as tarefas do arquivo
    int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return LER; // Retorna LER em caso de erro na leitura das tarefas

    // Lê a posição atual do arquivo
    qtd = fread(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return LER; // Retorna LER em caso de erro na leitura da posição

    // Fecha o arquivo
    if(fclose(f))
        return FECHAR; // Retorna FECHAR em caso de erro no fechamento do arquivo

    return OK; // Retorna OK para indicar sucesso ao carregar as tarefas
}

// Função para limpar o buffer do teclado
void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
