/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:52:55 by asanni            #+#    #+#             */
/*   Updated: 2024/06/26 17:14:43 by asanni           ###   ########.fr       */
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
// int main (void)
// {
// 	t_mini minishell;
// 	minishell = (t_mini){0};
// 	minishell.env_args = __environ;
// 	while (1)
// 		start_minishell(&minishell);
// 	//free_envs(minishell.env_args);
// 	return (0);
// }

#include <stdio.h>
#include <string.h>

int main()
{
    // Example usage
    const char *paths[] = {"path/to/file1.txt", "another/path/file2.txt"};
    const int num_paths = sizeof(paths) / sizeof(paths[0]);
    
    const char *target = "another/path/file2.txt";
    const char *result = search_path(paths, target);
    
    if (result!= NULL) 
        printf("Found '%s' ", result);
	else 
        printf("'%s' not found.\n", target);
    return 0;
}


