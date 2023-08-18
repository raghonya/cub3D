#include <cub3d.h>

int	mat_len(char **matrix)
{
	int i = 0;
	while (matrix[i])
		i++;
	return (i);
}
void	draw_map(t_cub *cub)
{
	int	player_color;
	int	space_color;
	int	wall_color;

	player_color = 0xFF0000;
	space_color = 0xFFFFFF;
	wall_color = 0x000000;

	create_img(cub, &cub->minimap, ft_strlen(*cub->map) * 10, mat_len(cub->map) * 10);
}