/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:18:51 by dohanyan          #+#    #+#             */
/*   Updated: 2023/08/21 20:06:32 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	lst_siz(t_news *news)
{
	int		i;
	t_news	*tp;

	tp = news;
	i = 0;
	while (tp)
	{
		tp = tp->next;
		i++;
	}
	return (i);
}

t_news	*fine_node(t_news **news, char *line)
{
	t_news	*tp;

	tp = *news;
	while (tp)
	{
		if (ft_strcmp(tp->line, line) == 0)
			return (tp);
		tp = tp->next;
	}
	return (NULL);
}

void	lst_del(t_news *del)
{
	free(del->line);
	free(del);
}

void	lst_pop(t_news **news, t_news *remov)
{
	t_news	*next;
	t_news	*prev;

	if (remov)
	{
		next = remov->next;
		prev = remov->prev;
		lst_del(remov);
		if (news && *news)
		{
			if (prev)
				prev->next = next;
			if (next)
				next->prev = prev;
			if (*news == remov)
				*news = next;
		}
	}
}
