#include <cub3d.h>

void	draw_floor_n_ceil(t_cub *cub)
{
	int	x;
	int	y;

	y = -1;
	while (++y < cub->H / 2)
	{
		x = -1;
		while (++x < cub->W)
			my_mlx_pixel_put(&cub->img, x, y, 0xFF0000);
	}
	while (++y < cub->H)
	{
		x = -1;
		while (++x < cub->W)
			my_mlx_pixel_put(&cub->img, x, y, 0x0000FF);
	}

}

void	print_gun(t_img *pic, t_img *game, int w, int h)
{
	int	x;
	int	y;
	int	px;
	int	py;

	px = 0;
	x = w / 2 - pic->wd / 2 - 1;
	while (++x < w / 2 + pic->wd / 2)
	{
		y = h - pic->ht - 1;
		py = 0;
		while (++y < h)
		{
			if (my_mlx_color_taker(pic, px, py) != 4278190080)
				my_mlx_pixel_put(game, x, y, \
				my_mlx_color_taker(pic, px, py));
			py++;
		}
		px++;
	}
}

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

void	raycaster(t_cub *cub)
{
	int	pixel;

	pixel = -1;
	draw_floor_n_ceil(cub);
	while (++pixel <= cub->W)
	{
		calc_ray_pos(cub, pixel);
		find_step_dir(cub);
		DDA_algorithm(cub);
		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		wallX = cub->player.posX + cub->ray.perpWallDist * cub->ray.rayX;
		if (cub->ray.side == 0)
			wallX = cub->player.posY + cub->ray.perpWallDist * cub->ray.rayY;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(TEXWIDTH));
		if ((cub->ray.side == 0 && cub->ray.rayX > 0) \
		|| (cub->ray.side == 1 && cub->ray.rayY < 0))
			texX = TEXWIDTH - texX - 1;
		calc_draw_ends(cub, pixel, texX);
		
	}
	// printf ("dirx: %f, diry: %f\n", cub->player.dirX, cub->player.dirY);
	print_gun(&cub->pistol->img, &cub->img, cub->W, cub->H);
	
	mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->img.img, 0, 0);
}
