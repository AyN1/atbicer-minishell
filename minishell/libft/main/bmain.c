/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:56:28 by atbicer           #+#    #+#             */
/*   Updated: 2023/12/26 21:46:43 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	print_data_mine(t_list *head)
{
	while (head)
	{
		printf("content: %d[%d]\n", (int)head->content, (int)head->content);
		head = head->next;
	}
}

void	print_data_course(t_list *head)
{
	t_list	*ptr;

	ptr = head;
	while (ptr)
	{
		printf("content: %d [%d]\n", (int)ptr->content, (int)head->content);
		ptr = ptr->next;
	}
}

int	main(int argc, char *argv[])
{
	t_list	*head;
	t_list	*current;

	head = malloc(sizeof(t_list));
	head->content = (int *)45;
	head->next = NULL;
	//
	current = malloc(sizeof(t_list));
	current->content = (int *)98;
	current->next = NULL;
	ft_lstadd_back(&head, current);
	//
	current = malloc(sizeof(t_list));
	current->content = (int *)3;
	current->next = NULL;
	ft_lstadd_back(&head, current);
	//
	current = malloc(sizeof(t_list));
	current->content = (int *)22;
	current->next = NULL;
	ft_lstadd_back(&head, current);
	//
	current = malloc(sizeof(t_list));
	current->content = (int *)66;
	current->next = NULL;
	ft_lstadd_back(&head, current);
	//fr
	print_data_course(head);
	printf("size: %d\n", ft_lstsize(head));
	return (0);
}
