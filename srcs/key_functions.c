#include <cub3d.h>

int	quit_game(t_cub *cub)
{
	(void)cub;
	//free mallocs, destroy images etc.
	exit(0);
	return (0);
}

int	key_up(int key, t_cub *cub)
{
	// printf ("keyup: %d\n", key);
	return (0);
}

int	key_down(int key, t_cub *cub)
{
	if (key == ESC)
		quit_game(cub);
	if (key == ARRRIGHT || key == KEYD)
		change_view(cub, ARRRIGHT);
	if (key == ARRLEFT || key == KEYA)
		change_view(cub, ARRLEFT);
	if (key == KEYW)
		step_fwd_back(cub, KEYW);
	if (key == KEYS)
		step_fwd_back(cub, KEYS);
	if (key == KEYD)
		step_fwd_back(cub, KEYD);
	if (key == KEYA)
		step_fwd_back(cub, KEYA);
	if (key == SHOOT)
	{
		gun_anim(cub, cub->pistol);
		print_gun(&cub->pistol->img, &cub->img, cub->W, cub->H);
		return (0);
	}
	mlx_destroy_image(cub->mlx.ptr, cub->img.img);
	create_img(cub);
	raycaster(cub);
	print_gun(&cub->pistol->img, &cub->img, cub->W, cub->H);
	return (0);
}
