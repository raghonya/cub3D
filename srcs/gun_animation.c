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

void	print_gun(t_img *pic, t_img *game, int b)
{
	int	x;
	int	y;
	int	px;
	int	py;

	px = 0;
	x = game->wd / 2 - pic->wd / 2 - 1;
	while (++x < game->wd / 2 + pic->wd / 2)
	{
		y = game->ht - pic->ht - 1 + b;
		py = 0;
		while (++y < game->ht + b)
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
		re_render(cub, &anim->img, !BULL_CHANGE, 0);
		anim = anim->next;
	}
	if (cub->bullet_count > 0)
		cub->bullet_count--;
}
