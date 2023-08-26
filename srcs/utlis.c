/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:24:24 by dohanyan          #+#    #+#             */
/*   Updated: 2023/08/26 18:03:10 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_matlen(char **matrix)
{
	int i;
	
	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

int	len_ignore_zero(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] == '0')
		i++;
	while (str[i + len])
		len++;
	return (len);
}

void	set_dir_and_pos(t_cub *cub, char player)
{
	cub->player.dir_x = 0;
	cub->player.dir_y = 0;
	cub->player.plane_x = 0;
	cub->player.plane_y = 0;
	if (player == 'N')
	{
		cub->player.dir_x = -1;
		cub->player.plane_y = 0.66;
	}
	else if (player == 'S')
	{
		cub->player.dir_x = 1;
		cub->player.plane_y = -0.66;
	}
	else if (player == 'E')
	{
		cub->player.dir_y = 1;
		cub->player.plane_x = 0.66;
	}
	else if (player == 'W')
	{
		cub->player.dir_y = -1;
		cub->player.plane_x = -0.66;
	}
}

void	replace_player(t_cub *cub, char **map_maze)
{
	int	i;
	int	j;

	i = 0;
	while (map_maze[i])
	{
		j = 0;
		while (map_maze[i][j])
		{
			if (map_maze[i][j] == 'N' || map_maze[i][j] == 'S'
				|| map_maze[i][j] == 'E' || map_maze[i][j] == 'W')
				{
					cub->player.pos_x = i + 0.5;
					cub->player.pos_y = j + 0.5;
					set_dir_and_pos(cub, map_maze[i][j]);
					map_maze[i][j] = 'P';
				}
			j++;
		}
		i++;
	}
}

void	replace_first_tab(char **map_maze)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (map_maze[i])
	{
		if (map_maze[i][0] == '\t')
		{
			line = strjoin_w_free(ft_strdup("    "), map_maze[i]);
			err_msg (!line, MALLOC);
			free(map_maze[i]);
			map_maze[i] = ft_strdup(line);
			err_msg (!map_maze[i], MALLOC);
			free(line);
		}
		i++;
	}	
}
