// Define o tamanho máximo para o vetor de tarefas
#define TOTAL 100

// Define a estrutura Tarefa, que representa uma tarefa com prioridade,
// descrição e categoria
typedef struct {
  int prioridade;      // Prioridade da tarefa
  char descricao[300]; // Descrição da tarefa
  char categoria[100]; // Categoria da tarefa
} Tarefa;

// Define o tipo de enumeração ERROS, que contém códigos de erro para as
// operações
typedef enum {
  OK,         // Operação bem-sucedida
  MAX_TAREFA, // Tentativa de criar uma nova tarefa quando o limite foi atingido
  SEM_TAREFAS, // Tentativa de realizar uma operação quando não há tarefas
  NAO_ENCONTRADO, // Tentativa de acessar uma tarefa que não existe
  ABRIR,          // Erro ao abrir um arquivo
  FECHAR,         // Erro ao fechar um arquivo
  ESCREVER,       // Erro ao escrever em um arquivo
  LER             // Erro ao ler de um arquivo
} ERROS;

// Define o tipo de ponteiro para função 'funcao', que recebe um vetor de Tarefa
// e um ponteiro para int e retorna um ERROS
typedef ERROS (*funcao)(Tarefa[], int *);

// Protótipos de função
ERROS criar(Tarefa tarefas[], int *pos); // Função para criar uma nova tarefa
ERROS deletar(Tarefa tarefas[], int *pos); // Função para deletar uma tarefa
ERROS listar(Tarefa tarefas[], int *pos); // Função para listar todas as tarefas
ERROS salvar(Tarefa tarefas[],
             int *pos); // Função para salvar as tarefas em um arquivo binário
ERROS carregar(
    Tarefa tarefas[],
    int *pos);      // Função para carregar as tarefas de um arquivo binário
void clearBuffer(); // Função para limpar o buffer do teclado
