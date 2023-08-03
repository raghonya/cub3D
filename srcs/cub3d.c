#include <cub3d.h>

void	err_msg(int condition, char *msg)
{
	if (condition)
	{
		printf ("Error: %s\n", msg);
		exit (1);
	}
}

void	printmap(t_cub cub)
{
	int	i =  -1;
	while (cub.map[++i])
		printf ("%s\n", cub.map[i]);
	printf ("\n");
}

void	file_check(t_cub *cub, char *filename)
{
	int		fd;
	char	*line;
	char	*joined;

	fd = open(filename, O_RDONLY);
	err_msg(fd < 0, "File error");
	joined = NULL;
	//check check
	//check datark file
	//check symbols in map
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
	int i = -1, j, player;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S' \
			|| cub->map[i][j] == 'E' || cub->map[i][j] == 'W')
			player = cub->map[i][j];
	}
	printf ("player char: %c\n", player);
	find_player(cub, player);
}

// Entaka e popoxutyan
void	set_dir_and_pos(t_cub *cub, char player)
{
	if (player == 'N')
	{
		cub->player.dirX = -1;
		cub->player.planeY = 0.66;
	}
	else if (player == 'S')
	{
		cub->player.dirX = 1;
		cub->player.planeY = -0.66;
	}
	else if (player == 'E')
	{
		cub->player.dirY = 1;
		cub->player.planeX = 0.66;
	}
	else if (player == 'W')
	{
		cub->player.dirY = -1;
		cub->player.planeX = -0.66;
	}
	// if (player == 'N')
	// {
	// 	cub->player.dirY = 1;
	// 	cub->player.planeY = 0.66;
	// }
	// else if (player == 'S')
	// {
	// 	cub->player.dirY = -1;
	// 	cub->player.planeY = -0.66;
	// }
	// else if (player == 'E')
	// {
	// 	cub->player.dirX = 1;
	// 	cub->player.planeX = 0.66;
	// }
	// else if (player == 'W')
	// {
	// 	cub->player.dirX = -1;
	// 	cub->player.planeX = -0.66;
	// }
}

//kanchvelu a symbolnery stugelu funkciayi mej
//erb parz lini playeri charactery
void	find_player(t_cub *cub, char player)
{
	int	i;
	int	j;
	
	i = -1;
	//arden stugac pti lini player symbolneri qanaky
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] == player)
			{
				cub->player.posX = i + 0.5;
				cub->player.posY = j + 0.5;
				cub->map[i][j] = '0';
				break ;
			}
		}
	}
	set_dir_and_pos(cub, player);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	err_msg (argc != 2, "Invalid number of arguments, 1 required");
	initialization(&cub);
	file_check(&cub, argv[1]);

	raycaster(&cub);
	print_gun(&cub.pistol->img, &cub.img, cub.W, cub.H);
	mlx_hook(cub.mlx.win, 2, 1L << 0, &key_down, &cub);
	mlx_hook(cub.mlx.win, 3, 1L << 1, &key_up, &cub);
	// dzel quit_game funkcian, destroy all images, free all mallocs
	mlx_hook(cub.mlx.win, 17, 1L << 15, &quit_game, &cub);
	
	mlx_loop(cub.mlx.ptr);
	return (0);
}
