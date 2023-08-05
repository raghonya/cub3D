#include <cub3d.h>

void	rotate(t_cub *cub, double oldDirX, double oldPlaneX, double rotSpeed)
{
	cub->player.dirX = cub->player.dirX * cos(rotSpeed) \
	- cub->player.dirY * sin(rotSpeed);
	cub->player.dirY = oldDirX * sin(rotSpeed) \
	+ cub->player.dirY * cos(rotSpeed);
	cub->player.planeX = cub->player.planeX * cos(rotSpeed) \
	- cub->player.planeY * sin(rotSpeed);
	cub->player.planeY = oldPlaneX * sin(rotSpeed) \
	+ cub->player.planeY * cos(rotSpeed);
}

void	change_view(t_cub *cub, int side)
{
	double	oldPlaneX;
	double	rotSpeed;
	double	oldDirX;

	rotSpeed = 0.06;
	oldDirX = cub->player.dirX;
	oldPlaneX = cub->player.planeX;
	if (side == ARRRIGHT)
		rotate(cub, oldDirX, oldPlaneX, -rotSpeed);
	else
		rotate(cub, oldDirX, oldPlaneX, rotSpeed);
}

void	 choose_direction(t_cub *cub)
{
	if (cub->player.dirX < 0 && cub->player.dirY > 0)
	{
		cub->player.dirX = 1 - pow(cub->player.dirX, 2);
		cub->player.dirY = 1 - pow(cub->player.dirY, 2);
	}
	else if (cub->player.dirX > 0 && cub->player.dirY > 0)
	{
		cub->player.dirX = 1 - pow(cub->player.dirX, 2);
		cub->player.dirY = -(1 - pow(cub->player.dirY, 2));
	}
	else if (cub->player.dirX > 0 && cub->player.dirY < 0)
	{
		cub->player.dirX = -(1 - pow(cub->player.dirX, 2));
		cub->player.dirY = -(1 - pow(cub->player.dirY, 2));
	}
	else
	{
		cub->player.dirX = -(1 - pow(cub->player.dirX, 2));
		cub->player.dirY = 1 - pow(cub->player.dirY, 2);
	}
}

void	step_right_left(t_cub *cub, double moveSpeed, int move)
{
	double	oldX;
	double	oldY;

	oldX = cub->player.dirX;
	oldY = cub->player.dirY;
	choose_direction(cub);
	if (move == KEYD)
		step_fwd_back(cub, KEYW, moveSpeed);
	else
		step_fwd_back(cub, KEYS, moveSpeed);
	cub->player.dirX = oldX;
	cub->player.dirY = oldY;
}

void	step_fwd_back(t_cub *cub, int side, double moveSpeed)
{
	if (side == KEYW)
	{
		if(cub->map\
		[(int)(cub->player.posX + cub->player.dirX * moveSpeed)]\
		[(int)(cub->player.posY)] == '0')
			cub->player.posX += cub->player.dirX * moveSpeed;
		if(cub->map\
		[(int)(cub->player.posX)]\
		[(int)(cub->player.posY + cub->player.dirY * moveSpeed)] == '0')
			cub->player.posY += cub->player.dirY * moveSpeed;
	}
	else if (side == KEYS)
	{
		if(cub->map\
		[(int)(cub->player.posX - cub->player.dirX * moveSpeed)]\
		[(int)(cub->player.posY)] == '0')
			cub->player.posX -= cub->player.dirX * moveSpeed;
		if(cub->map\
		[(int)(cub->player.posX)]\
		[(int)(cub->player.posY - cub->player.dirY * moveSpeed)] == '0')
			cub->player.posY -= cub->player.dirY * moveSpeed;
	}
}
