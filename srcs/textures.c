#include <cub3d.h>

t_img	*choose_texture(t_cub *cub)
{
	if (cub->map[cub->player.mapX][cub->player.mapY] == '2')
		return (TEXS + 4);
	else if (cub->map[cub->player.mapX][cub->player.mapY] == '3')
		return (TEXS + 5);
	if (cub->ray.side == 1 && cub->ray.rayY > 0)
		return (TEXS);
	else if (cub->ray.side == 1 &&  cub->ray.rayY <= 0)
		return (TEXS + 1);
	else if (cub->ray.side == 0 && cub->ray.rayX > 0)
		return (TEXS + 2);
	else if (cub->ray.side == 0 &&  cub->ray.rayX <= 0)
		return (TEXS + 3);
}

void	draw_texture(t_cub *cub, int x, int texX)
{
	int		y;
	t_draw	tex;
	
	if (cub->ray.perpWallDist < 0.000001)
		cub->ray.perpWallDist = 0.000001;
	calc_draw_ends(cub, &tex);
	y = tex.drawStart - 1;
	while (++y < tex.drawEnd)
	{
		tex.texY = (int)tex.texPos & (TEXHEIGHT - 1);
		tex.texPos += tex.step;
		my_mlx_pixel_put(&cub->img, x, y, \
		my_mlx_color_taker(choose_texture(cub), texX, tex.texY));
	}
}
