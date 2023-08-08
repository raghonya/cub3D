/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:56:54 by raghonya          #+#    #+#             */
/*   Updated: 2023/08/08 15:56:55 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (anim && cub->bullet_count)
	{
		mlx_destroy_image(cub->mlx.ptr, cub->img.img);
		create_img(cub);
		raycaster(cub, &anim->img, 0);
		usleep(10000);
		anim = anim->next;
	}
	if (cub->bullet_count > 0)
		cub->bullet_count--;
}
