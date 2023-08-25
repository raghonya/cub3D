/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_simbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:11:15 by dohanyan          #+#    #+#             */
/*   Updated: 2023/08/21 19:58:54 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_first_last(char *line)
{
	char	*res;
	int		i;

	i = -1;
	res = ft_strtrim(line, " \t");
	err_msg (!res, MALLOC);
	while (res[++i])
		err_msg (res[i] != '1' && res[i] != ' ', "Wrong map borders");
	if (res)
		free(res);
}

void	check_middle_line(char *line)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strtrim(line, " \t");
	err_msg(!res, MALLOC);
	err_msg (res[i] != '1' || res[ft_strlen(res) - 1] != '1', "Wrong map borders");
	while (res[i])
	{
		err_msg (res[i] != '1' && res[i] != '0' && res[i] != ' ' && res[i] != 'N'
			&& res[i] != 'S' && res[i] != 'W' && res[i] != 'E', "Wrong map symbols");
		i++;
	}
	if (res)
		free(res);
}

void	check_map_simbols(char **map_maze)
{
	int	i;

	i = 0;
	while (map_maze[i])
	{
		if (i == 0 || i == ft_matlen(map_maze) - 1)
			check_first_last(map_maze[i]);
		check_middle_line(map_maze[i]);
		i++;
	}
}
