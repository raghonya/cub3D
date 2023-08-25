/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map_maze.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:17:04 by dohanyan          #+#    #+#             */
/*   Updated: 2023/08/21 20:09:07 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_new_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		err_msg (line[i] == '\n' && line[i + 1] == '\n', \
		"Found new line in maze");
}

char	**return_map_maze(char *line, char **map)
{
	char	*res;
	char	*last;
	char	**map_maze;

	last = ft_strdup(map[5]);
	err_msg (!last, MALLOC);
	res = ft_strdup((ft_strstr(line, last) + ft_strlen(last)));
	err_msg (!res, MALLOC);
	free(line);
	free(last);
	line = ft_strtrim(res, "\n");
	err_msg (!line, MALLOC);
	free(res);
	check_new_line(line);
	map_maze = ft_split(line, '\n');
	err_msg (!map_maze, MALLOC);
	free(line);
	return (map_maze);
}

char	**create_map_maze(char **argv, char **map)
{
	char	*line;
	char	*joined;
	int		fd;

	joined = NULL;
	line = NULL;
	fd = open(argv[1], O_RDONLY);
	while (1)
	{
		joined = get_next_line(fd);
		if (!joined)
			break ;
		line = strjoin_w_free(line, joined);
		err_msg(!line, MALLOC);
		free(joined);
	}
	close(fd);
	return (return_map_maze(line, map));
}
