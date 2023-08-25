/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_all_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:41:49 by dohanyan          #+#    #+#             */
/*   Updated: 2023/08/21 20:05:35 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_last_line(char *line)
{
	char	*last;

	last = ft_strrchr(line, '\n');
	err_msg (ft_strlen(last) == 1, "New line");
}

char	**create_all_map(int fd)
{
	char	*line;
	char	*joined;
	char	*res;
	char	**splited;

	line = NULL;
	while (1)
	{
		joined = get_next_line(fd);
		if (!joined)
			break ;
		res = ft_strtrim(joined, "\t ");
		err_msg(!res, MALLOC);
		line = strjoin_w_free(line, res);
		err_msg(!line, MALLOC);
		free(joined);
		free(res);
	}
	close(fd);
	err_msg (!line, "File is empty");
	check_last_line(line);
	splited = ft_split(line, '\n');
	free(line);
	return (splited);
}
