/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:08:03 by raghonya          #+#    #+#             */
/*   Updated: 2023/08/08 16:08:05 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_img	*choose_texture(t_cub *cub)
{
	if (cub->ray.side == 1 && cub->ray.ray_y <= 0)
		return (cub->texs);
	else if (cub->ray.side == 0 && cub->ray.ray_x > 0)
		return (cub->texs + 1);
	else if (cub->ray.side == 0 && cub->ray.ray_x <= 0)
		return (cub->texs + 2);
	return (cub->texs + 3);
}

void	draw_texture(t_cub *cub, int x, int tex_x)
{
	t_draw	tex;
	int		y;

	if (cub->ray.perp_wall_dist < 0.000001)
		cub->ray.perp_wall_dist = 0.000001;
	calc_draw_ends(cub, &tex);
	y = tex.draw_start - 1;
	while (++y < tex.draw_end)
	{
		tex.tex_y = (int)tex.tex_pos & (TEXHEIGHT - 1);
		tex.tex_pos += tex.step;
		my_mlx_pixel_put(&cub->img, x, y, \
		my_mlx_color_taker(choose_texture(cub), tex_x, tex.tex_y));
	}
}
