/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_check_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:27:29 by dohanyan          #+#    #+#             */
/*   Updated: 2023/08/21 20:08:46 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_size_args(char **nubs)
{
	int	i;

	i = 0;
	while (nubs[i])
	{
		if (ft_atoi(nubs[i]) > 255)
		{
			ft_putendl_fd("Error: more then 255", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	check_color_nub(char *line)
{
	char	**nubs;
	int		i;
	int		j;

	i = 0;
	nubs = ft_split(line, ',');
	if (splited_len(nubs) != 3)
	{
		ft_putendl_fd("Error: more color args", 2);
		exit(EXIT_FAILURE);
	}
	while (nubs[i])
	{
		j = 0;
		while (nubs[i][j])
		{
			if (nubs[i][j] < '0' || nubs[i][j] > '9' || ft_strlen(nubs[i]) > 3)
			{
				ft_putendl_fd("Error: bad color argument", 2);
				exit(EXIT_FAILURE);
			}	
			j++;
		}
		i++;
	}
	check_size_args(nubs);
	free_2d(nubs);
}

char	*make_color_line(char **splited, int *comma)
{
	char	*line;
	int		i;

	line = NULL;
	i = 1;
	while (splited[i])
	{
		line = strjoin_w_free(line, splited[i]);
		if (i != splited_len(splited) - 1)
		{
			line = strjoin_w_free(line, ",");
			(*comma)++;
		}
		i++;
	}
	return (line);
}

void	check_color_line(char **splited)
{
	int		i;
	int		comma;
	int		count;
	char	*line;

	i = 0;
	comma = 0;
	count = 0;
	line = make_color_line(splited, &comma);
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count - comma != 2)
	{
		ft_putendl_fd("Error: more or less comma22222", 2);
		exit(EXIT_FAILURE);
	}
	check_color_nub(line);
	free(line);
}
