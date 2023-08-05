#include <cub3d.h>

void	draw_floor_n_ceil(t_cub *cub)
{
	int	x;
	int	y;

	y = -1;
	while (++y < cub->H / 2)
	{
		x = -1;
		while (++x < cub->W)
			my_mlx_pixel_put(&cub->img, x, y, 0xFFAFFF);
	}
	while (++y < cub->H)
	{
		x = -1;
		while (++x < cub->W)
			my_mlx_pixel_put(&cub->img, x, y, 0x00B000);
	}

}

void	raycaster(t_cub *cub, t_img *anim)
{
	int	pixel;

	pixel = -1;
	draw_floor_n_ceil(cub);
	while (++pixel <= cub->W)
	{
		calc_ray_pos(cub, pixel);
		find_step_dir(cub);
		DDA_algorithm(cub);
		draw_texture(cub, pixel, calc_texture_x(cub));
	}
	print_gun(cub, anim, &cub->img, cub->W, cub->H);
	mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->img.img, 0, 0);
}
