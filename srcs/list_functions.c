/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:59:19 by raghonya          #+#    #+#             */
/*   Updated: 2023/08/08 15:59:20 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*a;

	if (!*lst && new)
	{
		*lst = new;
		return ;
	}
	else if (!new)
		return ;
	a = *lst;
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = new;
	*lst = a;
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->img.img = content;
	new->next = NULL;
	return (new);
}

t_news	*make_new(char *line)
{
	t_news	*new;

	new = malloc(sizeof(t_news));
	new->next = NULL;
	new->line = line;
	new->prev = NULL;
	return (new);
}

void	push_back(t_news **news, char *line)
{
	t_news	*new;
	t_news	*tp;

	tp = NULL;
	new = NULL;
	err_msg(!line, MALLOC);
	if (!*news)
	{
		*news = make_new(line);
		err_msg(!*news, MALLOC);
	}
	else
	{
		tp = *news;
		new = make_new(line);
		err_msg(!new, MALLOC);
		while (tp->next != NULL)
			tp = tp->next;
		tp->next = new;
		new->prev = tp;
	}
}

void	make_news(t_news **news)
{
	push_back(news, ft_strdup("NO"));
	push_back(news, ft_strdup("SO"));
	push_back(news, ft_strdup("WE"));
	push_back(news, ft_strdup("EA"));
	push_back(news, ft_strdup("F"));
	push_back(news, ft_strdup("C"));
}
