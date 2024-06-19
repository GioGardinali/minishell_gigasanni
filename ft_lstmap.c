/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:45:38 by asanni            #+#    #+#             */
/*   Updated: 2024/03/08 19:32:51 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	**aux;

	(void)del;
	if (lst == NULL)
		return (NULL);
	result = ft_lstnew(f(lst->content));
	aux = &result;
	lst = lst->next;
	while (lst != NULL)
	{
		ft_lstadd_back(aux, ft_lstnew(f(lst->content)));
		lst = lst->next;
	}
	return (result);
}
