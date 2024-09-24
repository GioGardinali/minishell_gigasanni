/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   *//
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:38:49 by asanni            #+#    #+#             */
/*   Updated: 2024/07/14 11:49:42 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* BUILT INS
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
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
//ex cd adedayo , a função vai ser built_cd(adedayo)
int	built_cd(char *str)
{
	if (str != NULL)
		return (1);
	if (chdir(str) == -1)
		return (1);
	return (0);
}
