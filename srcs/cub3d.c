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

//check check
//check datark file
//check symbols in map
void	file_check(t_cub *cub, char *filename)
{
	int		fd;
	char	*line;
	char	*joined;
	char	player;
	int		i;
	int		j;

	i = -1;
	fd = open(filename, O_RDONLY);
	err_msg(fd < 0, "File error");
	joined = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		joined = strjoin_w_free(joined, line);
		free(line);
	}
	cub->map = ft_split(joined, '\n');
	free(joined);
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S' \
			|| cub->map[i][j] == 'E' || cub->map[i][j] == 'W')
			player = cub->map[i][j];
	}
	find_player(cub, player);
}

// Entaka e popoxutyan
void	set_dir_and_pos(t_cub *cub, char player)
{
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

//kanchvelu a symbolnery stugelu funkciayi mej
//erb parz lini playeri charactery
//arden stugac pti lini player symbolneri qanaky
void	find_player(t_cub *cub, char player)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] == player)
			{
				cub->player.pos_x = i + 0.5;
				cub->player.pos_y = j + 0.5;
				cub->map[i][j] = '0';
				break ;
			}
		}
	}
	set_dir_and_pos(cub, player);
}

void	hooks(t_cub *cub)
{
	mlx_hook(cub->mlx.win, 2, 1L << 0, &key_press, cub);
	mlx_hook(cub->mlx.win, 4, 1L << 2, &mouse_press, cub);
	mlx_hook(cub->mlx.win, 6, 1L << 4, &mouse_move, cub);
	mlx_hook(cub->mlx.win, 17, 1L << 15, &quit_game, cub);
	mlx_loop(cub->mlx.ptr);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	err_msg (argc != 2, "Invalid number of arguments, 1 required");
	initialization(&cub);
	file_check(&cub, argv[1]);
	raycaster(&cub, &cub.gun->img, 1);
	hooks(&cub);
	return (0);
}
