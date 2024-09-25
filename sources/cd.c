/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:38:49 by asanni            #+#    #+#             */
/*   Updated: 2024/09/25 17:24:25 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* BUILT INS
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or argumentsclear
◦ exit with no options
*/

// int	built_pwd(void)
// {
// 	char	*str;

// 	str = getcwd(NULL, 0);
// 	printf("%s\n", str);
// 	return (0);
// }

// aqui vai chamar o que estiver apos o cd na linha
//ex cd adedayo, a função vai ser built_cd(adedayo)
int	execute_cd(t_cmd *cmd)
{
	if (cmd->options[1] != NULL)
		return (1);
	if (chdir(cmd->options[1]) == -1)
		return (1);
	return (0);
}
