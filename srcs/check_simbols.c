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

void	check_firs_last(char *line)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strtrim(line, " \t");
	while (res[i])
	{
		if (res[i] != '1' && res[i] != ' ')
		{
			ft_putendl_fd("Error: wrong map", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (res)
		free(res);
}

void	check_middle_line(char *line)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strtrim(line, " \t");
	if (res[i] != '1' || res[ft_strlen(res) - 1] != '1')
	{
		ft_putendl_fd("Error: wrong map", 2);
		exit(EXIT_FAILURE);
	}
	while (res[i])
	{
		if (res[i] != '1' && res[i] != '0' && res[i] != ' ' && res[i] != 'N'
			&& res[i] != 'S' && res[i] != 'W' && res[i] != 'E')
		{
			ft_putendl_fd("Error: wrong map", 2);
			exit(EXIT_FAILURE);
		}	
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
		if (i == 0 || i == splited_len(map_maze) - 1)
			check_firs_last(map_maze[i]);
		check_middle_line(map_maze[i]);
		i++;
	}
}
