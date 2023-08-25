/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:24:24 by dohanyan          #+#    #+#             */
/*   Updated: 2023/08/21 20:04:39 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	splited_len(char **splited)
{
	int	i;

	i = 0;
	if (!splited)
		return (i);
	while (splited[i])
		i++;
	return (i);
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
