#include <cub3d.h>

int	check_points(t_cub *cub, int beginX, int beginY, int endY)
{
	if (endY < beginY)
	{
		beginY += endY;
		endY = beginY - endY;
		beginY -= endY;
	}
	if (endY < 0 || beginY >= cub->H  || beginX < 0 || beginX >= cub->W)
		return (1);
	if (beginY < 0)
		beginY = 0;
	if (endY >= cub->W)
		endY = cub->H - 1;
	return (0);
}

void	draw(t_cub *cub, int beginX, int beginY, int endY, int color)
{
	int		pixels;
	double	deltaY;
	double	pixelX;
	double	pixelY;

	pixelX = beginX;
	pixelY = beginY;
	deltaY = endY - beginY; // 0
	pixels = sqrt((deltaY * deltaY));
	if (check_points(cub, beginX, beginY, endY))
		return ;
	deltaY /= pixels;
	while (pixels)
	{
		my_mlx_pixel_put(&cub->img, pixelX, pixelY, color);
		pixelY += deltaY;
		--pixels;
	}
}

void	raycaster(t_cub *cub)
{
	int	x;

	x = -1;
	while (x < cub->W)
    {
		double	cameraX;

		cameraX = 2 * x / (double)cub->W - 1;
		cub->ray.rayX = cub->player.dirX + cub->player.planeX * cameraX;
		cub->ray.rayY = cub->player.dirY + cub->player.planeY * cameraX;
		int mapX = (int)cub->player.posX;
		int mapY = (int)cub->player.posY;
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (cub->ray.rayX == 0) ? 1e30 : fabs(1 / cub->ray.rayX);
		double deltaDistY = (cub->ray.rayY == 0) ? 1e30 : fabs(1 / cub->ray.rayY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		if (cub->ray.rayX < 0)
		{
			stepX = -1;
			sideDistX = (cub->player.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cub->player.posX) * deltaDistX;
		}
		if (cub->ray.rayY < 0)
		{
			stepY = -1;
			sideDistY = (cub->player.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cub->player.posY) * deltaDistY;
		}
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (cub->map[mapX][mapY] == '1') hit = 1;
		}
		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);
		int lineHeight = (int)(cub->H / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + cub->H / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + cub->H / 2;
		if(drawEnd >= cub->H)drawEnd = cub->H - 1;
		int color = trgb(0, 255, 0, 0);
		if (side == 1)
			color /= 2;
		draw(cub, x, drawStart, drawEnd, color);
		x++;
	}
	mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->img.img, 0, 0);	
}
