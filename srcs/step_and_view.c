#include <cub3d.h>

void	rotate(t_cub *cub, double oldDirX, double oldPlaneX, double rotSpeed)
{
	PLAYER.dirX = PLAYER.dirX * cos(rotSpeed) \
	- PLAYER.dirY * sin(rotSpeed);
	PLAYER.dirY = oldDirX * sin(rotSpeed) \
	+ PLAYER.dirY * cos(rotSpeed);
	PLAYER.planeX = PLAYER.planeX * cos(rotSpeed) \
	- PLAYER.planeY * sin(rotSpeed);
	PLAYER.planeY = oldPlaneX * sin(rotSpeed) \
	+ PLAYER.planeY * cos(rotSpeed);
}

void	change_view(t_cub *cub, int side)
{
	double	oldPlaneX;
	double	rotSpeed;
	double	oldDirX;

	rotSpeed = 0.06;
	oldDirX = PLAYER.dirX;
	oldPlaneX = PLAYER.planeX;
	if (side == ARRRIGHT)
		rotate(cub, oldDirX, oldPlaneX, -rotSpeed);
	else
		rotate(cub, oldDirX, oldPlaneX, rotSpeed);
}

void	 choose_direction(t_cub *cub)
{
	if (PLAYER.dirX < 0 && PLAYER.dirY > 0)
	{
		PLAYER.dirX = 1 - pow(PLAYER.dirX, 2);
		PLAYER.dirY = 1 - pow(PLAYER.dirY, 2);
	}
	else if (PLAYER.dirX > 0 && PLAYER.dirY > 0)
	{
		PLAYER.dirX = 1 - pow(PLAYER.dirX, 2);
		PLAYER.dirY = -(1 - pow(PLAYER.dirY, 2));
	}
	else if (PLAYER.dirX > 0 && PLAYER.dirY < 0)
	{
		PLAYER.dirX = -(1 - pow(PLAYER.dirX, 2));
		PLAYER.dirY = -(1 - pow(PLAYER.dirY, 2));
	}
	else
	{
		PLAYER.dirX = -(1 - pow(PLAYER.dirX, 2));
		PLAYER.dirY = 1 - pow(PLAYER.dirY, 2);
	}
}

void	step_right_left(t_cub *cub, double moveSpeed, int move)
{
	double	oldX;
	double	oldY;

	oldX = PLAYER.dirX;
	oldY = PLAYER.dirY;
	choose_direction(cub);
	if (move == KEYD)
		step_fwd_back(cub, KEYW, moveSpeed);
	else
		step_fwd_back(cub, KEYS, moveSpeed);
	PLAYER.dirX = oldX;
	PLAYER.dirY = oldY;
}

void	step_fwd_back(t_cub *cub, int side, double moveSpeed)
{
	if (side == KEYW)
	{
		if(cub->map\
		[(int)(PLAYER.posX + PLAYER.dirX * moveSpeed)]\
		[(int)(PLAYER.posY)] == '0')
			PLAYER.posX += PLAYER.dirX * moveSpeed;
		if(cub->map\
		[(int)(PLAYER.posX)]\
		[(int)(PLAYER.posY + PLAYER.dirY * moveSpeed)] == '0')
			PLAYER.posY += PLAYER.dirY * moveSpeed;
	}
	else if (side == KEYS)
	{
		if(cub->map\
		[(int)(PLAYER.posX - PLAYER.dirX * moveSpeed)]\
		[(int)(PLAYER.posY)] == '0')
			PLAYER.posX -= PLAYER.dirX * moveSpeed;
		if(cub->map\
		[(int)(PLAYER.posX)]\
		[(int)(PLAYER.posY - PLAYER.dirY * moveSpeed)] == '0')
			PLAYER.posY -= PLAYER.dirY * moveSpeed;
	}
}
