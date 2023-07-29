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

void	calc_draw_ends(t_cub *cub, int x)
{
	int color;
	int drawEnd;
	int drawStart;
	int lineHeight;
	
	lineHeight = (int)(cub->H / cub->ray.perpWallDist);
	drawStart = -lineHeight / 2 + cub->H / 2;
	drawEnd = lineHeight / 2 + cub->H / 2;
	if (drawStart < 0)
		drawStart = 0;
	if (drawEnd >= cub->H)
		drawEnd = cub->H - 1;
	color = trgb(0, 255, 0, 0);
	if (cub->ray.side == 1)
		color /= 2;
	draw(cub, x, drawStart, drawEnd, color);
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
		calc_draw_ends(cub, x);
	}
	mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->img.img, 0, 0);	
}
