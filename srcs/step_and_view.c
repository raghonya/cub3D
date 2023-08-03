#include <cub3d.h>

void	rotate(t_cub *cub, double oldDirX, double oldPlaneX, double rotSpeed)
{
	cub->player.dirX = cub->player.dirX * cos(rotSpeed) - cub->player.dirY * sin(rotSpeed);
	cub->player.dirY = oldDirX * sin(rotSpeed) + cub->player.dirY * cos(rotSpeed);
	cub->player.planeX = cub->player.planeX * cos(rotSpeed) - cub->player.planeY * sin(rotSpeed);
	cub->player.planeY = oldPlaneX * sin(rotSpeed) + cub->player.planeY * cos(rotSpeed);
}

void	change_view(t_cub *cub, int side)
{
	double	oldDirX;
	double	rotSpeed;
	double	oldPlaneX;

	rotSpeed = 0.06;
	oldDirX = cub->player.dirX;
	oldPlaneX = cub->player.planeX;
	if (side == ARRRIGHT)
		rotate(cub, oldDirX, oldPlaneX, -rotSpeed);
	else
		rotate(cub, oldDirX, oldPlaneX, rotSpeed);
}

void	right(t_cub *cub, double moveSpeed)
{
	double	oldX;
	double	oldY;

	oldX = cub->player.dirX;
	oldY = cub->player.dirY;
	if (cub->player.dirX < 0 && cub->player.dirY > 0)
		cub->player.dirX = -cub->player.dirX;
	else if (cub->player.dirX > 0 && cub->player.dirY > 0)
		cub->player.dirY = -cub->player.dirY;
	else if (cub->player.dirX > 0 && cub->player.dirY < 0)
		cub->player.dirX = -cub->player.dirX;
	else
		cub->player.dirY = -cub->player.dirY;
	if(cub->map[(int)(cub->player.posX + cub->player.dirX * moveSpeed)]\
	[(int)(cub->player.posY)] == '0')
		cub->player.posX += cub->player.dirX * moveSpeed;
	if(cub->map[(int)(cub->player.posX)]\
	[(int)(cub->player.posY + cub->player.dirY * moveSpeed)] == '0')\
		cub->player.posY += cub->player.dirY * moveSpeed;
	cub->player.dirX = oldX;
	cub->player.dirY = oldY;
}

void	step_fwd_back(t_cub *cub, int side)
{
	double	moveSpeed;

	moveSpeed = 0.16;
	if (side == KEYW)
	{
		if(cub->map[(int)(cub->player.posX + cub->player.dirX * moveSpeed)]\
		[(int)(cub->player.posY)] == '0')
			cub->player.posX += cub->player.dirX * moveSpeed;
		if(cub->map[(int)(cub->player.posX)]\
		[(int)(cub->player.posY + cub->player.dirY * moveSpeed)] == '0')\
			cub->player.posY += cub->player.dirY * moveSpeed;
	}
	else if (side == KEYS)
	{
		if(cub->map[(int)(cub->player.posX - cub->player.dirX * moveSpeed)][(int)(cub->player.posY)] == '0')
			cub->player.posX -= cub->player.dirX * moveSpeed;
		if(cub->map[(int)(cub->player.posX)][(int)(cub->player.posY - cub->player.dirY * moveSpeed)] == '0')
			cub->player.posY -= cub->player.dirY * moveSpeed;
    }
	// else if (side == KEYD)
	// 	right(cub, moveSpeed);
	// {
	// 	if (cub->player.dirX < 0 && cub->player.dirY < 0 \
	// 	|| cub->player.dirX > 0 && cub->player.dirY > 0)
	// 	{
	// 		printf ("if um enq\n");
	// 		if(cub->map[(int)(cub->player.posX + moveSpeed)]\
	// 		[(int)(cub->player.posY)] == '0')
	// 			cub->player.posX += moveSpeed;
	// 		if(cub->map[(int)(cub->player.posX)]\
	// 		[(int)(cub->player.posY - moveSpeed)] == '0')\
	// 			cub->player.posY -= moveSpeed;
	// 		// printf ("posx: %f, posy: %f\n", cub->player.posX, cub->player.posY);
	// 	}
	// 	else
	// 	{
	// 		printf ("else um enq\n");
	// 		if(cub->map[(int)(cub->player.posX - moveSpeed)]\
	// 		[(int)(cub->player.posY)] == '0')
	// 			cub->player.posX -= moveSpeed;
	// 		if(cub->map[(int)(cub->player.posX)]\
	// 		[(int)(cub->player.posY + moveSpeed)] == '0')\
	// 			cub->player.posY += moveSpeed;
	// 	}
		
	// }
			// printf ("posx: %f, posy: %f\n", cub->player.posX, cub->player.posY);
}
