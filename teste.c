#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_mini {
    char *input;
} t_mini;

// Função auxiliar para verificar o PID (suponho que você tenha essa função definida)
void check_pid(t_mini *minishell) {
    // Implementação da função check_pid
}

// Função de saída do minishell
void exit_function() {
    printf("Saindo do minishell...\n");
    exit(0);
}

static void start_minishell(t_mini *minishell) {
    pid_t pid;

    minishell->input = readline("Minishell> ");
    if (!minishell->input)
        minishell->input = strdup("exit");

    if (strcmp(minishell->input, "") != 0)
        add_history(minishell->input);

    if (strcmp(minishell->input, "exit") == 0)
        exit_function();

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        check_pid(minishell); // Processo filho executa a função para verificar o PID
        exit(0); // Saída do processo filho após execução
    }

    free(minishell->input); // Libera a memória alocada para a entrada
    waitpid(pid, NULL, 0); // Espera pelo término do processo filho
}

int main() {
    t_mini minishell;

    while (1) {
        start_minishell(&minishell);
    }

    return 0;
}
