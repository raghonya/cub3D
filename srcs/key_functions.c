#include <cub3d.h>

int	quit_game(t_cub *cub)
{
	(void)cub;
	//free mallocs, destroy images etc.
	exit(0);
	return (0);
}

int	key_press(int key, t_cub *cub)
{
	if (key == ESC)
		quit_game(cub);
	if (key == KEYW)
		step_fwd_back(cub, KEYW, 0.16);
	if (key == KEYS)
		step_fwd_back(cub, KEYS, 0.16);
	if (key == KEYD)
		step_right_left(cub, 0.12, KEYD);
	if (key == KEYA)
		step_right_left(cub, 0.12, KEYA);
	if (key == ARRRIGHT)
		change_view(cub, ARRRIGHT);
	if (key == ARRLEFT)
		change_view(cub, ARRLEFT);
	if (key == SHOOT)
		gun_anim(cub, cub->gun->next);
	mlx_destroy_image(cub->mlx.ptr, cub->img.img);
	create_img(cub);
	if (key == SHOOT)
		raycaster(cub, &cub->gun->img, 1);
	else
		raycaster(cub, &cub->gun->img, 0);
	return (0);
}
