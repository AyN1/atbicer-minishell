/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:56:15 by atbicer           #+#    #+#             */
/*   Updated: 2023/12/26 22:06:39 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while ((ptr)->next)
		ptr = ptr->next;
	ptr->next = new;
}
