/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:28 by raghonya          #+#    #+#             */
/*   Updated: 2023/08/08 16:14:30 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	err_msg(int condition, char *msg)
{
	if (condition)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putendl_fd(msg, 2);
		exit (1);
	}
}

void	hooks(t_cub *cub)
{
	mlx_hook(cub->mlx.win, 2, 1L << 0, &key_press, cub);
	mlx_hook(cub->mlx.win, 4, 1L << 2, &mouse_press, cub);
	mlx_hook(cub->mlx.win, 6, 1L << 4, &mouse_move, cub);
	mlx_hook(cub->mlx.win, 17, 1L << 15, &quit_game, cub);
	mlx_loop(cub->mlx.ptr);
}

void	file_parsing(t_cub *cub, char **argv)
{
	t_news	*news;
	char	**map;
	int		fd;
	
	news = NULL;
	cub->map = NULL;
	cub->texs_path = malloc(sizeof(char *) * 4);
	err_msg(!cub->texs_path, MALLOC);
	fd = check_file_name(argv);
	make_news(&news);
	map = create_all_map(fd);
	err_msg(!map, MALLOC);
	check_before_map(cub, map, &news);
	cub->map = create_map_maze(argv, map);
	err_msg (!cub->map || !*cub->map, "Incorrect map");
	check_count_player(cub->map);
	check_map_simbols(cub->map);
	replace_player(cub, cub->map);
	replace_first_tab(cub->map);
	check_empty(cub->map);
	free_2d(map);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	err_msg (argc != 2, "Invalid number of arguments, 1 required");
	
	file_parsing(&cub, argv);
	initialization(&cub);
	raycaster(&cub, &cub.gun->img, BULL_CHANGE);
	hooks(&cub);
	return (0);
}
