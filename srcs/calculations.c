#include <cub3d.h>

void	calc_ray_pos(t_cub *cub, int pixel)
{
	RAY.cameraX = 2.0 * pixel / (double)cub->W - 1.0;
	RAY.rayX = PLAYER.dirX + PLAYER.planeX * RAY.cameraX;
	RAY.rayY = PLAYER.dirY + PLAYER.planeY * RAY.cameraX;
	PLAYER.mapX = (int)PLAYER.posX;
	PLAYER.mapY = (int)PLAYER.posY;
	if (RAY.rayX == 0)
		RAY.deltaDistX = 1e30;
	else
		RAY.deltaDistX = fabs(1 / RAY.rayX);
	if (RAY.rayY == 0)
		RAY.deltaDistY = 1e30;
	else
		RAY.deltaDistY = fabs(1 / RAY.rayY);
}

void	find_step_dir(t_cub *cub)
{
	if (RAY.rayX < 0)
	{
		PLAYER.stepX = -1;
		RAY.sideDistX = \
		(PLAYER.posX - PLAYER.mapX) * RAY.deltaDistX;
	}
	else
	{
		PLAYER.stepX = 1;
		RAY.sideDistX = \
		(PLAYER.mapX + 1.0 - PLAYER.posX) * RAY.deltaDistX;
	}
	if (RAY.rayY < 0)
	{
		PLAYER.stepY = -1;
		RAY.sideDistY = \
		(PLAYER.posY - PLAYER.mapY) * RAY.deltaDistY;
	}
	else
	{
		PLAYER.stepY = 1;
		RAY.sideDistY = \
		(PLAYER.mapY + 1.0 - PLAYER.posY) * RAY.deltaDistY;
	}
}

void	DDA_algorithm(t_cub *cub)
{
	RAY.hit = 0;
	while (RAY.hit == 0)
	{
		if (RAY.sideDistX < RAY.sideDistY)
		{
			RAY.sideDistX += RAY.deltaDistX;
			PLAYER.mapX += PLAYER.stepX;
			RAY.side = 0;
		}
		else
		{
			RAY.sideDistY += RAY.deltaDistY;
			PLAYER.mapY += PLAYER.stepY;
			RAY.side = 1;
		}
		if (cub->map[PLAYER.mapX][PLAYER.mapY] > '0')
			RAY.hit = 1;
	}
	if (RAY.side == 0)
		RAY.perpWallDist = (RAY.sideDistX - RAY.deltaDistX);
	else
		RAY.perpWallDist = (RAY.sideDistY - RAY.deltaDistY);
}

void	calc_draw_ends(t_cub *cub, t_draw *tex)
{
	tex->lineHeight = (int)(cub->H / RAY.perpWallDist);
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

	wallX = PLAYER.posX + RAY.perpWallDist * RAY.rayX;
	if (RAY.side == 0)
		wallX = PLAYER.posY + RAY.perpWallDist * RAY.rayY;
	wallX -= floor((wallX));
	texX = (int)(wallX * (double)(TEXWIDTH));
	if ((RAY.side == 0 && RAY.rayX > 0) \
	|| (RAY.side == 1 && RAY.rayY < 0))
		texX = TEXWIDTH - texX - 1;
	return (texX);
}
