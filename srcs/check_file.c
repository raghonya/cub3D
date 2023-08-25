/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:32:17 by dohanyan          #+#    #+#             */
/*   Updated: 2023/08/21 20:04:56 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_file_name(int argc, char **argv)
{
	int	fd;

	fd = 0;
	if (argc > 2 || argc <= 1)
	{
		ft_putendl_fd("Error: less or more argc", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(ft_strrchr(argv[1], '.'), ".cub") != 0
		|| ft_strlen(argv[1]) == 4)
	{
		ft_putendl_fd("Error: bad file name!", 2);
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error: bad file discriptor", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
