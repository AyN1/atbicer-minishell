/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 20:13:59 by atbicer           #+#    #+#             */
/*   Updated: 2023/12/26 21:31:38 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;

	if (!*lst || !del || !lst)
		return ;
	while (*lst)
	{
		ptr = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = ptr;
	}
	*lst = NULL;
}
