/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:53:34 by raghonya          #+#    #+#             */
/*   Updated: 2023/08/08 15:53:35 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	calc_ray_pos(t_cub *cub, int pixel)
{
	cub->ray.camera_x = 2.0 * pixel / (double)cub->map_wd - 1.0;
	cub->ray.ray_x = cub->player.dir_x + \
	cub->player.plane_x * cub->ray.camera_x;
	cub->ray.ray_y = cub->player.dir_y + \
	cub->player.plane_y * cub->ray.camera_x;
	cub->player.map_x = (int)cub->player.pos_x;
	cub->player.map_y = (int)cub->player.pos_y;
	if (cub->ray.ray_x == 0)
		cub->ray.deltadist_x = 1e30;
	else
		cub->ray.deltadist_x = fabs(1 / cub->ray.ray_x);
	if (cub->ray.ray_y == 0)
		cub->ray.deltadist_y = 1e30;
	else
		cub->ray.deltadist_y = fabs(1 / cub->ray.ray_y);
}

void	find_step_dir(t_cub *cub)
{
	if (cub->ray.ray_x < 0)
	{
		cub->player.step_x = -1;
		cub->ray.sidedist_x = \
		(cub->player.pos_x - cub->player.map_x) * cub->ray.deltadist_x;
	}
	else
	{
		cub->player.step_x = 1;
		cub->ray.sidedist_x = \
		(cub->player.map_x + 1.0 - cub->player.pos_x) * cub->ray.deltadist_x;
	}
	if (cub->ray.ray_y < 0)
	{
		cub->player.step_y = -1;
		cub->ray.sidedist_y = \
		(cub->player.pos_y - cub->player.map_y) * cub->ray.deltadist_y;
	}
	else
	{
		cub->player.step_y = 1;
		cub->ray.sidedist_y = \
		(cub->player.map_y + 1.0 - cub->player.pos_y) * cub->ray.deltadist_y;
	}
}

void	dda_algorithm(t_cub *cub)
{
	cub->ray.hit = 0;
	while (cub->ray.hit == 0)
	{
		if (cub->ray.sidedist_x < cub->ray.sidedist_y)
		{
			cub->ray.sidedist_x += cub->ray.deltadist_x;
			cub->player.map_x += cub->player.step_x;
			cub->ray.side = 0;
		}
		else
		{
			cub->ray.sidedist_y += cub->ray.deltadist_y;
			cub->player.map_y += cub->player.step_y;
			cub->ray.side = 1;
		}
		if (cub->map[cub->player.map_x][cub->player.map_y] > '0')
			cub->ray.hit = 1;
	}
	if (cub->ray.side == 0)
		cub->ray.perp_wall_dist = (cub->ray.sidedist_x - cub->ray.deltadist_x);
	else
		cub->ray.perp_wall_dist = (cub->ray.sidedist_y - cub->ray.deltadist_y);
}

void	calc_draw_ends(t_cub *cub, t_draw *tex)
{
	tex->line_height = (int)(cub->map_ht / cub->ray.perp_wall_dist);
	tex->draw_start = -tex->line_height / 2 + cub->map_ht / 2;
	if (tex->draw_start < 0)
		tex->draw_start = 0;
	tex->draw_end = tex->line_height / 2 + cub->map_ht / 2;
	if (tex->draw_end >= cub->map_ht)
		tex->draw_end = cub->map_ht - 1;
	tex->step = 1.0 * TEXHEIGHT / tex->line_height;
	tex->tex_pos = \
	(tex->draw_start - cub->map_ht / 2 + tex->line_height / 2) * tex->step;
}

int	calc_texture_x(t_cub *cub)
{
	int		tex_x;
	double	wall_x;

	wall_x = cub->player.pos_x + cub->ray.perp_wall_dist * cub->ray.ray_x;
	if (cub->ray.side == 0)
		wall_x = cub->player.pos_y + cub->ray.perp_wall_dist * cub->ray.ray_y;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)(TEXWIDTH));
	if ((cub->ray.side == 0 && cub->ray.ray_x > 0) \
	|| (cub->ray.side == 1 && cub->ray.ray_y < 0))
		tex_x = TEXWIDTH - tex_x - 1;
	return (tex_x);
}
