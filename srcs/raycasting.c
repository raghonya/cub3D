/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:02:38 by raghonya          #+#    #+#             */
/*   Updated: 2023/08/08 16:02:41 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	re_render(t_cub *cub, t_img *img, int bul_change)
{
	mlx_destroy_image(cub->mlx.ptr, cub->img.img);
	create_img(cub, &cub->img, cub->map_wd, cub->map_ht);
	raycaster(cub, img, bul_change);
}

void	draw_floor_n_ceil(t_cub *cub)
{
	int	x;
	int	y;

	y = -1;
	while (++y < cub->map_ht / 2)
	{
		x = -1;
		while (++x < cub->map_wd)
			my_mlx_pixel_put(&cub->img, x, y, cub->ceil_color);
	}
	while (++y < cub->map_ht - 1)
	{
		x = -1;
		while (++x < cub->map_wd)
			my_mlx_pixel_put(&cub->img, x, y, cub->floor_color);
	}
}

void	change_bullet_count(t_cub *cub)
{
	char	*str;

	str = ft_itoa(cub->bullet_count);
	err_msg(!str, MALLOC);
	mlx_clear_window(cub->mlx.ptr, cub->mlx.win);
	mlx_string_put(cub->mlx.ptr, cub->mlx.win, 0, \
	cub->map_ht + 10, 0xFFFFFF, "Bullets left: ");
	mlx_string_put(cub->mlx.ptr, cub->mlx.win, 100, \
	cub->map_ht + 10, 0xFFFFFF, str);
	mlx_string_put(cub->mlx.ptr, cub->mlx.win, cub->map_wd / 3, \
	cub->map_ht + 10, 0xFFFFFF, "Press M to show/hide minimap");
	free(str);
}

void	raycaster(t_cub *cub, t_img *anim, int bullet_change)
{
	int	pixel;

	pixel = -1;
	draw_floor_n_ceil(cub);
	while (++pixel <= cub->map_wd)
	{
		calc_ray_pos(cub, pixel);
		find_step_dir(cub);
		dda_algorithm(cub);
		draw_texture(cub, pixel, calc_texture_x(cub));
	}
	print_gun(anim, &cub->img, cub->map_wd, cub->map_ht);
	if (bullet_change)
		change_bullet_count(cub);
	if (cub->show_map)
		draw_minimap(cub);
	mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->img.img, 0, 0);
	printf ("dirx: %f ,diry: %f\n", cub->player.dir_x, cub->player.dir_y);
}
