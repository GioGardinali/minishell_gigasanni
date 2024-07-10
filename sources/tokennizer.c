/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokennizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:32:48 by asanni            #+#    #+#             */
/*   Updated: 2024/07/10 20:29:35 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	make_tokens(t_token **token, char *split)
// {
// 	t_token	*new_token;
// 	t_token	*tmp;

// 	if (token == NULL)
// 		error_function("error in tokenizer");
// 	new_token = (malloc(sizeof(t_token)));
// 	if (new_token == NULL)
// 		error_function("error in tokenizer");
// 	new_token->str = split;
// 	new_token->type = find_etype(split);
// 	new_token->next = NULL;
// 	new_token->prev = NULL;
// 	if (*token == NULL)
// 	{
// 		*token = new_token;
// 		return ;
// 	}
// 	else
// 	{
// 		tmp = *token;
// 		while (tmp->next != NULL)
// 			tmp = tmp->next;
// 		tmp->next = new_token;
// 		new_token->prev = tmp;
// 	}
// }

void make_tokens(t_token *token, char *split) {
    t_token *new_token;

    // Verifica se o token fornecido é nulo
    if (token == NULL) {
        printf("O token fornecido não pode ser NULL.\n");
        return;
    }

    // Aloca memória para o novo nó
    new_token = malloc(sizeof(t_token));
    if (new_token == NULL) {
        error_function("Erro na alocação de memória para o novo token."); // Certifique-se de que esta função esteja definida em algum lugar do seu código
        return;
    }

    // Preenche os dados do novo nó
    new_token->str = split;
    new_token->type = find_etype(split); // Assumindo que esta função esteja definida em algum lugar do seu código
    new_token->next = NULL;
    new_token->prev = NULL;

    // Insere o novo nó após o token fornecido
    if (token->next != NULL) {
        // Se o token fornecido não estiver no final da lista, insere o novo nó após ele
        new_token->next = token->next;
        new_token->next->prev = new_token;
        token->next = new_token;
        new_token->prev = token;
    } else {
        // Se o token fornecido estiver no final da lista, atualiza o ponteiro do token anterior para apontar para o novo nó
        token->next = new_token;
        new_token->prev = token;
    }
}

// void	make_tokens(t_token *token, char *split)
// {
// 	t_token	*new_token;

// 	if (token == NULL)
// 	{
// 		new_token = malloc(sizeof(t_token));
// 		if (new_token == NULL)
// 			error_function("error in tokenizer");
// 		new_token->str = split;
// 		new_token->type = find_etype(split);
// 		new_token->next = NULL;
// 		new_token->prev = NULL;
// 		token = new_token;
// 	}
// 	else
// 	{
// 		token->str = split;
// 		token->type = find_etype(split);
// 	}
// }

// void make_tokens(t_token *token, char *split) {
//     t_token *new_token;

//     // Verifica se o token fornecido é nulo
//     if (token == NULL) {
//         printf("O token fornecido não pode ser NULL.\n");
//         return;
//     }

//     // Aloca memória para o novo nó
//     new_token = malloc(sizeof(t_token));
//     if (new_token == NULL) {
//         error_function("Erro na alocação de memória para o novo token."); // Certifique-se de que esta função esteja definida em algum lugar do seu código
//         return;
//     }

//     // Preenche os dados do novo nó
//     new_token->str = split;
//     new_token->type = find_etype(split); // Assumindo que esta função esteja definida em algum lugar do seu código
//     new_token->next = NULL;
//     new_token->prev = NULL;

//     // Insere o novo nó após o token fornecido
//     if (token->next != NULL) {
//         // Se o token fornecido não estiver no final da lista, insere o novo nó após ele
//         new_token->next = token->next;
//         new_token->next->prev = new_token;
//         token->next = new_token;
//         new_token->prev = token;
//     } else {
//         // Se o token fornecido estiver no final da lista, atualiza o ponteiro do token anterior para apontar para o novo nó
//         token->next = new_token;
//         new_token->prev = token;
//     }
// }


int	find_etype(char *str)
{
	if (str[0] == '$')
		return (VAR);
	else if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(str, ">") == 0)
		return (TRUNC);
	else if (ft_strcmp(str, ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(str, "<") == 0)
		return (INPUT);
	else if (ft_strcmp(str, "<<") == 0)
		return (HERE_DOC);
	else
		return (WORD);
}

void	print_tokens(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		printf("Token: |%s| -> Type: %d,\n", current->str, current->type);
		current = current->next;
	}
}
