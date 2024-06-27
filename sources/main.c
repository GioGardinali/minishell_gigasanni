/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:52:55 by asanni            #+#    #+#             */
/*   Updated: 2024/06/26 21:01:33 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	exit_function(void)
{
	ft_putendl_fd("exit", 1);
	exit(EXIT_SUCCESS);
}

void	check_pid(t_mini *minishell)
{
	char	**cmds;
	char	*path;

	cmds = ft_split(minishell->input, ' ');
	path = ft_strjoin(ft_strdup("/usr/bin/"), cmds[0]);
	execve(path, cmds, __environ);
	ft_putendl_fd("Execve falhou trouxa!", 2);
	free_split(cmds);
	free(path);
	exit(1);
}

static void	start_minishell(t_mini *minishell)
{
	pid_t	pid;

	minishell->input = readline("Minishelby> ");
	if (!minishell->input) //aqui checa o ctrl D que é uma string NULL
		minishell->input = ft_strdup("exit");
	if (ft_strcmp(minishell->input, "") != 0)
		add_history(minishell->input);
	if (ft_strcmp(minishell->input, "exit") == 0) // aqui checa a palavra literal EXIT
		exit_function();
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
		check_pid(minishell);
	free(minishell->input);
	waitpid(pid, NULL, 0);
}

char	**copy_env(void)
{
	int		i;
	int		size;
	char	**temp;

	size = 0;
	i = -1;
	while (__environ[size])
		size++;
	temp = ft_calloc(sizeof(char *), size + 1);
	while (++i < size)
		temp[i] = __environ[i];
	// i = -1;
	// while (++i < size)
	// 	printf("%s\n", temp[i]);
	return (temp);
}

int	main(void)
{
	t_mini		minishell;
	char		**str_path;
	int			i;

	minishell = (t_mini){0};
	//str_path = copy_env();
	minishell.env.env_content = copy_env();
	str_path = ft_split(search_path(minishell.env.env_content, "PATH"), ':');
	i = -1;
	while (str_path[++i])
		printf("%s\n", str_path[i]);
	// while (1)
	// 	start_minishell(&minishell);
	// //free_envs(minishell.env_args);
	// return (0);
}
