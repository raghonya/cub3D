/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splited_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:30:55 by dohanyan          #+#    #+#             */
/*   Updated: 2023/08/21 20:25:24 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_path_line(char **splited)
{
	err_msg (ft_matlen(splited) != 2 \
	|| ft_strcmp(ft_strrchr(splited[1], '.'), ".xpm") != 0, \
	"Incorrect option name or image format");
}

void	choose_wall(t_cub *cub, char **splited)
{
	if (ft_strcmp(*splited, "WE") == 0)
		cub->texs_path[0] = ft_strdup(*(splited + 1));
	else if (ft_strcmp(*splited, "SO") == 0)
		cub->texs_path[1] = ft_strdup(*(splited + 1));
	else if (ft_strcmp(*splited, "NO") == 0)
		cub->texs_path[2] = ft_strdup(*(splited + 1));
	else if (ft_strcmp(*splited, "EA") == 0)
		cub->texs_path[3] = ft_strdup(*(splited + 1));
}

void	check_splited(t_cub *cub, char **splited, t_news **news)
{
	t_news	*tp;

	tp = *news;
	while (tp)
	{
		if (splited && ft_strcmp(splited[0], tp->line) == 0)
		{
			if (ft_strlen(tp->line) == 2)
			{
				check_path_line(splited);
				choose_wall(cub, splited);
			}
			if (ft_strlen(tp->line) == 1)
				check_color_line(cub, splited);
			lst_pop(news, find_node(news, tp->line));
			return ;
		}
		tp = tp->next;
	}
	err_msg (!tp, "incorect name of options");
}

void	make_splited(t_cub *cub, char *line, t_news **news)
{
	char	**splited;
	char	*res;
	int		i;

	i = -1;
	res = NULL;
	splited = ft_split(line, ' ');
	err_msg(!splited, MALLOC);
	while (splited[++i])
	{
		res = strjoin_w_free(res, splited[i]);
		err_msg(!res, MALLOC);
		res = strjoin_w_free(res, "\t");
		err_msg(!res, MALLOC);
	}
	free_2d(splited);
	splited = ft_split(res, '\t');
	err_msg(!splited, MALLOC);
	free(res);
	res = NULL;
	check_splited(cub, splited, news);
	free_2d(splited);
}

void	check_before_map(t_cub *cub, char **map, t_news **news)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (map[i])
			make_splited(cub, map[i], news);
		else
			break ;
		i++;
	}
	err_msg (i != 6, "New line in maze");
}
