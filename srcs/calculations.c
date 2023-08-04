#include <cub3d.h>

void	calc_ray_pos(t_cub *cub, int pixel)
{
	cub->ray.cameraX = 2.0 * pixel / (double)cub->W - 1.0;
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

void	find_step_dir(t_cub *cub)
{
	if (cub->ray.rayX < 0)
	{
		cub->player.stepX = -1;
		cub->ray.sideDistX = \
		(cub->player.posX - cub->player.mapX) * cub->ray.deltaDistX;
	}
	else
	{
		cub->player.stepX = 1;
		cub->ray.sideDistX = \
		(cub->player.mapX + 1.0 - cub->player.posX) * cub->ray.deltaDistX;
	}
	if (cub->ray.rayY < 0)
	{
		cub->player.stepY = -1;
		cub->ray.sideDistY = \
		(cub->player.posY - cub->player.mapY) * cub->ray.deltaDistY;
	}
	else
	{
		cub->player.stepY = 1;
		cub->ray.sideDistY = \
		(cub->player.mapY + 1.0 - cub->player.posY) * cub->ray.deltaDistY;
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
		if (cub->map[cub->player.mapX][cub->player.mapY] > '0')
			cub->ray.hit = 1;
	}
	if (cub->ray.side == 0)
		cub->ray.perpWallDist = (cub->ray.sideDistX - cub->ray.deltaDistX);
	else
		cub->ray.perpWallDist = (cub->ray.sideDistY - cub->ray.deltaDistY);
}

void	calc_draw_ends(t_cub *cub, t_draw *tex)
{
	tex->lineHeight = (int)(cub->H / cub->ray.perpWallDist);
	tex->drawStart = -tex->lineHeight / 2 + cub->H / 2;
	if (tex->drawStart < 0)
		tex->drawStart = 0;
	tex->drawEnd = tex->lineHeight / 2 + cub->H / 2;
	if (tex->drawEnd >= cub->H)
		tex->drawEnd = cub->H - 1;
	tex->step = 1.0 * TEXHEIGHT / tex->lineHeight;
	tex->texPos = \
	(tex->drawStart - cub->H / 2 + tex->lineHeight / 2) * tex->step;
}

int	calc_texture_x(t_cub *cub)
{
	int		texX;
	double	wallX;

	wallX = cub->player.posX + cub->ray.perpWallDist * cub->ray.rayX;
	if (cub->ray.side == 0)
		wallX = cub->player.posY + cub->ray.perpWallDist * cub->ray.rayY;
	wallX -= floor((wallX));
	texX = (int)(wallX * (double)(TEXWIDTH));
	if ((cub->ray.side == 0 && cub->ray.rayX > 0) \
	|| (cub->ray.side == 1 && cub->ray.rayY < 0))
		texX = TEXWIDTH - texX - 1;
	return (texX);
}
