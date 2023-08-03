#include <cub3d.h>

void	print_gun(t_img *pic, t_img *game, int w, int h)
{
	int	x;
	int	y;
	int	px;
	int	py;

	px = 0;
	x = w / 2 - pic->wd / 2 - 1;
	while (++x < w / 2 + pic->wd / 2)
	{
		y = h - pic->ht - 1;
		py = 0;
		while (++y < h)
		{
			if (my_mlx_color_taker(pic, px, py) != 4278190080)
				my_mlx_pixel_put(game, x, y, \
				my_mlx_color_taker(pic, px, py));
			py++;
		}
		px++;
	}
}

void	gun_anim(t_cub *cub, t_list *anim)
{
	raycaster(cub);
	while (anim)
	{
		print_gun(&anim->img, &cub->img, cub->W, cub->H);
		mlx_destroy_image(cub->mlx.ptr, cub->img.img);
		create_img(cub);
		raycaster(cub);
		anim = anim->next;
	}
}
