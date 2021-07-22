/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <...@student.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 17:02:35 by wnormcor          #+#    #+#             */
/*   Updated: 2020/05/03 18:57:52 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newlist;

	if ((newlist = malloc(sizeof(t_list))) == NULL)
		return (NULL);
	newlist->content = content;
	newlist->next = NULL;
	return (newlist);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

int		ft_lstsize(t_list *lst)
{
	int		size;

	if (lst == NULL)
		return (0);
	size = 1;
	while ((lst = lst->next) != NULL && size++)
		;
	return (size);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while ((lst->next) != NULL && (lst = lst->next))
		;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst == NULL)
		;
	else if (*lst == NULL)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}
