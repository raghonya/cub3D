/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:37:28 by dohanyan          #+#    #+#             */
/*   Updated: 2023/08/21 20:01:02 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_count_player(char **map_maze)
{
	int	count;
	int	i;
	int	j;

	i = -1;
	count = 0;
	while (map_maze[++i])
	{
		j = -1;
		while (map_maze[i][++j])
			if (map_maze[i][j] == 'W' || map_maze[i][j] == 'S' \
			|| map_maze[i][j] == 'E' || map_maze[i][j] == 'N')
				count++;
	}
	err_msg (count != 1, "Bad player simbol");
}

void	player_symbol_change(char **map_maze)
{
	int	i;
	int	j;

	i = -1;
	while (map_maze[++i])
	{
		j = -1;
		while (map_maze[i][++j])
			if (map_maze[i][j] == 'P')
				map_maze[i][j] = '0';
	}
}

void	check_empty(char **map_maze)
{
	int	i;
	int	j;

	i = -1;
	while (map_maze[++i])
	{
		j = -1;
		while (map_maze[i][++j])
		{
			if (map_maze[i][j] == '0' || map_maze[i][j] == 'P')
			{
				if (j > (int)(ft_strlen(map_maze[i + 1]) - 1)
					|| j > (int)(ft_strlen(map_maze[i - 1]) - 1))
					err_msg(1, "Wrong map borders");
				else
					err_msg (map_maze[i + 1][j] == ' ' || map_maze[i - 1][j] == ' ' \
					|| map_maze[i][j + 1] == ' ' || map_maze[i][j - 1] == ' ' \
					|| map_maze[i + 1][j] == '\t' \
					|| map_maze[i - 1][j] == '\t', "Wrong map maze");
			}	
		}
	}
	player_symbol_change(map_maze);
}
