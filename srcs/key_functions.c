#include <cub3d.h>

void	change_view(t_cub *cub, int side)
{
	double rotSpeed = 0.05;
	double oldDirX = cub->player.dirX;
	double oldPlaneX = cub->player.planeX;
	if (side == ARRRIGHT)
	{
		cub->player.dirX = cub->player.dirX * cos(-rotSpeed) - cub->player.dirY * sin(-rotSpeed);
		cub->player.dirY = oldDirX * sin(-rotSpeed) + cub->player.dirY * cos(-rotSpeed);
		cub->player.planeX = cub->player.planeX * cos(-rotSpeed) - cub->player.planeY * sin(-rotSpeed);
		cub->player.planeY = oldPlaneX * sin(-rotSpeed) + cub->player.planeY * cos(-rotSpeed);
	}
	else
	{
		cub->player.dirX = cub->player.dirX * cos(rotSpeed) - cub->player.dirY * sin(rotSpeed);
		cub->player.dirY = oldDirX * sin(rotSpeed) + cub->player.dirY * cos(rotSpeed);
		cub->player.planeX = cub->player.planeX * cos(rotSpeed) - cub->player.planeY * sin(rotSpeed);
		cub->player.planeY = oldPlaneX * sin(rotSpeed) + cub->player.planeY * cos(rotSpeed);
	}
}

void	step(t_cub *cub, int side)
{
	double moveSpeed = 0.1;

	if (side == KEYW)
	{
		if(cub->map[(int)(cub->player.posX + cub->player.dirX * moveSpeed)]\
		[(int)(cub->player.posY)] == '0')
			cub->player.posX += cub->player.dirX * moveSpeed;
		if(cub->map[(int)(cub->player.posX)]\
		[(int)(cub->player.posY + cub->player.dirY * moveSpeed)] == '0')\
			cub->player.posY += cub->player.dirY * moveSpeed;
	}
	else
	{
		if(cub->map[(int)(cub->player.posX - cub->player.dirX * moveSpeed)][(int)(cub->player.posY)] == '0')
			cub->player.posX -= cub->player.dirX * moveSpeed;
		if(cub->map[(int)(cub->player.posX)][(int)(cub->player.posY - cub->player.dirY * moveSpeed)] == '0')
			cub->player.posY -= cub->player.dirY * moveSpeed;
    }
}

int	quit_game(t_cub *cub)
{
	(void)cub;
	exit(0);
	return (0);
}

int	key_up(int key, t_cub *cub)
{
	printf ("keyup: %d\n", key);
	return (0);
}

int	key_down(int key, t_cub *cub)
{
	if (key == ESC)
		quit_game(cub);
	if (key == ARRRIGHT)
		change_view(cub, ARRRIGHT);
	if (key == ARRLEFT)
		change_view(cub, ARRLEFT);
	if (key == KEYW)
		step(cub, KEYW);
	if (key == KEYS)
		step(cub, KEYS);
	if (key == KEYD)
		;// cub->player.posY += 0.1;
	if (key == KEYA)
		;// cub->player.posY -= 0.1;
	mlx_destroy_image(cub->mlx.ptr, cub->img.img);
	create_img(cub);
	raycaster(cub);
	return (0);
}
