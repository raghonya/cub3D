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

int	check_file_name(char **argv)
{
	int	fd;

	fd = 0;
	if (/*ft_strlen(argv[1]) < 4 || */ft_strcmp(ft_strrchr(argv[1], '.'), ".cub") != 0
		|| ft_strlen(argv[1]) == 4)
	{
		//Dav es inch a , xi a strlen hashvum
		//Petq a strrchr ov / man gal, u et filename vekalel stugeluc
		//bayc open anel argv[1] y
		//bayc petq chi stugel length == 4, petq a stugel length < 4 
		ft_putendl_fd("Error: bad file name!", 2);
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	err_msg (fd == -1, "Bad file discriptor");
	return (fd);
}
