#include <cub3d.h>

t_img	*choose_texture(t_cub *cub)
{
	if (cub->map[PLAYER.mapX][PLAYER.mapY] == '1')
	{
		if (RAY.side == 1 && RAY.rayY > 0)
			return (TEXS);
		else if (RAY.side == 1 &&  RAY.rayY <= 0)
			return (TEXS + 1);
		else if (RAY.side == 0 && RAY.rayX > 0)
			return (TEXS + 2);
		else if (RAY.side == 0 &&  RAY.rayX <= 0)
			return (TEXS + 3);
	}
	else if (cub->map[PLAYER.mapX][PLAYER.mapY] == '2')
		return (TEXS + 4);
	else if (cub->map[PLAYER.mapX][PLAYER.mapY] == '3')
		return (TEXS + 5);
	return (TEXS);
}

void	draw_texture(t_cub *cub, int x, int texX)
{
	t_draw	tex;
	int		y;
	
	if (RAY.perpWallDist < 0.000001)
		RAY.perpWallDist = 0.000001;
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
