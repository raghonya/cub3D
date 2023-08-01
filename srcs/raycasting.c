#include <cub3d.h>

void	find_step_dir(t_cub *cub)
{
	if (cub->ray.rayX < 0)
	{
		cub->player.stepX = -1;
		cub->ray.sideDistX = (cub->player.posX - cub->player.mapX) * cub->ray.deltaDistX;
	}
	else
	{
		cub->player.stepX = 1;
		cub->ray.sideDistX = (cub->player.mapX + 1.0 - cub->player.posX) * cub->ray.deltaDistX;
	}
	if (cub->ray.rayY < 0)
	{
		cub->player.stepY = -1;
		cub->ray.sideDistY = (cub->player.posY - cub->player.mapY) * cub->ray.deltaDistY;
	}
	else
	{
		cub->player.stepY = 1;
		cub->ray.sideDistY = (cub->player.mapY + 1.0 - cub->player.posY) * cub->ray.deltaDistY;
	}
}

void	DDA_algorithm(t_cub *cub)
{
	cub->ray.hit = 0;
	while (cub->ray.hit == 0)
	{
		if (cub->ray.sideDistX < cub->ray.sideDistY)
		{
			cub->ray.sideDistX += cub->ray.deltaDistX;
			cub->player.mapX += cub->player.stepX;
			cub->ray.side = 0;
		}
		else
		{
			cub->ray.sideDistY += cub->ray.deltaDistY;
			cub->player.mapY += cub->player.stepY;
			cub->ray.side = 1;
		}
		if (cub->map[cub->player.mapX][cub->player.mapY] == '1') cub->ray.hit = 1;
	}
	if (cub->ray.side == 0)
		cub->ray.perpWallDist = (cub->ray.sideDistX - cub->ray.deltaDistX);
	else
		cub->ray.perpWallDist = (cub->ray.sideDistY - cub->ray.deltaDistY);
}

// # define TEXWIDTH 64
// # define TEXHEIGHT 64

void	calc_draw_ends(t_cub *cub, int x, int texX)
{
// 	int lineHeight;
	
// 	lineHeight = (int)(cub->H / cub->ray.perpWallDist);
// 	drawStart = -lineHeight / 2 + cub->H / 2;
// 	drawEnd = lineHeight / 2 + cub->H / 2;
// 	if (drawStart < 0)
// 		drawStart = 0;
// 	if (drawEnd >= cub->H)
// 		drawEnd = cub->H - 1;
// 	color = trgb(0, 255, 0, 0);
// 	if (cub->ray.side == 1)
// 		color /= 2;
// 	draw(cub, x, drawStart, drawEnd, color);
	int color;
	int drawEnd;
	int drawStart;
	int lineHeight = (int)(cub->H / cub->ray.perpWallDist);
	int pitch = 100;
	//calculate lowest and highest pixel to fill in current stripe
	drawStart = -lineHeight / 2 + cub->H / 2 + pitch;
	if(drawStart < 0) drawStart = 0;
	drawEnd = lineHeight / 2 + cub->H / 2 + pitch;
	if(drawEnd >= cub->H) drawEnd = cub->H - 1;
	double step = 1.0 * TEXHEIGHT / lineHeight;
	// Starting texture coordinate
	double texPos = (drawStart - pitch - cub->H / 2 + lineHeight / 2) * step;
	for(int y = drawStart; y < drawEnd; y++)
	{
		// Cast the texture coordinate to integer, and mask with (TEXHEIGHT - 1) in case of overflow
		int texY = (int)texPos & (TEXHEIGHT - 1);
		texPos += step;
		if (cub->ray.side == 1) my_mlx_color_taker(TEXS, texX, texY, &color);
		else					my_mlx_color_taker(TEXS + 1, texX, texY, &color);
		my_mlx_pixel_put(&cub->img, x, y, color);
	}
}

void	calc_ray_pos(t_cub *cub, int x)
{
	cub->ray.cameraX = 2 * x / (double)cub->W - 1;
	cub->ray.rayX = cub->player.dirX + cub->player.planeX * cub->ray.cameraX;
	cub->ray.rayY = cub->player.dirY + cub->player.planeY * cub->ray.cameraX;
	cub->player.mapX = (int)cub->player.posX;
	cub->player.mapY = (int)cub->player.posY;
	if (cub->ray.rayX == 0)
		cub->ray.deltaDistX = 1e30;
	else
		cub->ray.deltaDistX = fabs(1 / cub->ray.rayX);
	if (cub->ray.rayY == 0)
		cub->ray.deltaDistY = 1e30;
	else
		cub->ray.deltaDistY = fabs(1 / cub->ray.rayY);
}

void	raycaster(t_cub *cub)
{
	int	x;

	x = -1;
	while (++x < cub->W)
	{
		calc_ray_pos(cub, x);
		find_step_dir(cub);
		DDA_algorithm(cub);
		// int texNum = cub->map[cub->player.mapX][cub->player.mapY] - 49; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if(cub->ray.side == 0) wallX = cub->player.posY + cub->ray.perpWallDist * cub->ray.rayY;
		else          wallX = cub->player.posX + cub->ray.perpWallDist * cub->ray.rayX;
		wallX -= floor((wallX));
		// printf ("wall: %f\n", wallX);

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(TEXWIDTH));
		if(cub->ray.side == 0 && cub->ray.rayX > 0) texX = TEXWIDTH - texX - 1;
		if(cub->ray.side == 1 && cub->ray.rayY < 0) texX = TEXWIDTH - texX - 1;
		calc_draw_ends(cub, x, texX);

	}
	printf ("dirx: %f, diry: %f\n", cub->player.dirX, cub->player.dirY);
	mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->img.img, 0, 0);	
}
