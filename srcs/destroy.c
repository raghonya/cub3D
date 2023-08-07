#include <cub3d.h>

void	destroy_gun_imgs(t_cub *cub)
{
	t_list	*tmp;

	while (cub->gun)
	{
		tmp = cub->gun;
		cub->gun = tmp->next;
		mlx_destroy_image(MLX.ptr, tmp->img.img);
		free(tmp);
	}
}

void	destroy_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		free(map[i]);
	}
	free(map);
}

void	destroy_textures(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		mlx_destroy_image(MLX.ptr, TEXS[i].img);
	}
	free(TEXS);
}
