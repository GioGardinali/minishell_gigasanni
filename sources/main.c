/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:52:55 by asanni            #+#    #+#             */
/*   Updated: 2024/07/13 18:24:32 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_pid(t_mini *minishell)
{
	char	**cmds;
	char	*path;

	//cmds = normalize_input(minishell);
	path = verify_path(minishell);
	printf("%d", path == NULL);
	execve(path, cmds, __environ);
	ft_putendl_fd("Execve falhou", 2);
	free_split(cmds);
	free(path);
	exit(1);
}

static void	start_minishell(t_mini *minishell)
{
	pid_t	pid;

	minishell->input = readline("Minishelby> ");
	if (!minishell->input)
		minishell->input = ft_strdup("exit");
	if (ft_strcmp(minishell->input, "") != 0)
		add_history(minishell->input);
	if (ft_strcmp(minishell->input, "exit") == 0)
		exit_function();
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
		check_pid(minishell);
	free(minishell->input);
	waitpid(pid, NULL, 0);
}

int	main(void)
{
	t_mini		minishell;
	t_token		token;
	int			i;
	char		*str;
	char		**split;

	i = 0;
	token = (t_token){0};
	str = " a $c 'ade sanni'  e 'dsadsd'  << < >> > |  ";
	split = ft_split(adjust_spaces(str), -1);
	printf("%s\n", adjust_spaces(str));
	while (split[i])
	{
		make_tokens(&token, split[i]);
		printf("%s\n", split[i]);
		i++;
	}
	print_tokens(&token);
	// minishell = (t_mini){0};
	// minishell.env.env_content = copy_env();
	// i = -1;
	// while (1)
	// 	start_minishell(&minishell);
	// free(minishell.env.env_content);
	// return (0);
}

/*________________________________________________________*/
// andar até o igual e dar o retorno depois do igual 
// do espaco ate o \0 colocar numa var char ponteiro 

// char	*return_folder(t_mini *minishell)
// {
// 	char	*str_path;
// 	char	**path_;

// 	str_path = search_path(minishell->env.env_content, "PATH");	
// 	//str_path = ft_split(search_path(minishell->env.env_content, "PATH"), ':');
// }

//  static void	start_minishell(t_mini *minishell)
// {
// 	pid_t	pid;

// 	minishell->input = readline("Minishelby> ");
//	//linha abaixo checa o ctrl D que é uma string NULL
// 	if (!minishell->input) 
// 		minishell->input = ft_strdup("exit");
// 	if (ft_strcmp(minishell->input, "") != 0)
// 		add_history(minishell->input);
// 	//linha abaixo aqui checa a palavra literal EXIT
// 	if (ft_strcmp(minishell->input, "exit") == 0) 
// 		exit_function();
// 	pid = fork();
// 	if (pid == -1)
// 		exit(1);
// 	else if (pid == 0)
// 		check_pid(minishell);
// 	free(minishell->input);
// 	waitpid(pid, NULL, 0);
// }
