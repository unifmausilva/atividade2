#include "tarefas.h" // Inclui o cabeçalho que contém as declarações das funções relacionadas às tarefas
#include <stdio.h>   // Inclui o cabeçalho padrão para entrada e saída em C

// Definição do programa principal
int main() {
  // Declarando um array de ponteiros para funções que retornam um ERROS e recebem um vetor de Tarefa e um ponteiro para int como argumentos
  funcao fs[] = {criar, deletar, listar, salvar, carregar};

  // Declarando um vetor de Tarefa com tamanho TOTAL
  Tarefa tarefas[TOTAL];

  // Declarando uma variável inteira para armazenar a posição atual no vetor de tarefas
  int pos;

  // Chamando a função carregar do array fs e passando o vetor de tarefas e o endereço de pos como argumentos
  // O retorno da função é armazenado na variável erro
  ERROS erro = fs[4](tarefas, &pos);

  // Verificando se ocorreu algum erro ao carregar as tarefas
  if (erro != OK)
    // Em caso de erro, define pos como 0
    pos = 0;

  int opcao; // Declarando uma variável inteira para armazenar a opção do menu

  // Loop principal do programa
  do {
    // Imprimindo o menu principal
    printf("\nMenu principal\n");
    printf("1 - Criar tarefa\n");
    printf("2 - Deletar tarefa\n");
    printf("3 - Listar tarefas\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");

    // Lendo a opção escolhida pelo usuário
    scanf("%d", &opcao);

    // Decrementando a opção para corresponder ao índice do array fs
    opcao--;

    // Verificando se a opção é maior que 2 (opção inválida)
    if (opcao > 2)
      printf("Opcao invalida\n");
    // Verificando se a opção é maior ou igual a 0 (opção válida)
    else if (opcao >= 0)
      // Chamando a função correspondente ao índice opcao do array fs e passando o vetor de tarefas e o endereço de pos como argumentos
      fs[opcao](tarefas, &pos);
    else
      // Imprimindo mensagem de saída
      printf("Sair...\n");

  // Continua o loop enquanto a opção escolhida for maior ou igual a 0
  } while (opcao >= 0);

  // Chamando a função salvar do array fs e passando o vetor de tarefas e o endereço de pos como argumentos
  fs[3](tarefas, &pos);

  // Retorna 0 para indicar que o programa foi executado com sucesso
  return 0;
}
