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
	// raycaster(cub);
	// mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->img.img, 0, 0);
	while (anim && cub->bullet_count)
	{
		printf ("nono\n");
		// printf ("anim address: %p\n", anim->img.img);
		mlx_destroy_image(cub->mlx.ptr, cub->img.img);
		create_img(cub);
		raycaster(cub, &anim->img);
		// print_gun(TEXS + 3, &cub->img, cub->W, cub->H);
		anim = anim->next;
	}
	if (cub->bullet_count > 0)
		cub->bullet_count--;
}
