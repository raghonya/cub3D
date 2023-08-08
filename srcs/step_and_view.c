/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_and_view.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:07:09 by raghonya          #+#    #+#             */
/*   Updated: 2023/08/08 16:07:12 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	rotate(t_cub *cub, double olddir_x, double oldplane_x, double rotSpeed)
{
	cub->player.dir_x = cub->player.dir_x * cos(rotSpeed) \
	- cub->player.dir_y * sin(rotSpeed);
	cub->player.dir_y = olddir_x * sin(rotSpeed) \
	+ cub->player.dir_y * cos(rotSpeed);
	cub->player.plane_x = cub->player.plane_x * cos(rotSpeed) \
	- cub->player.plane_y * sin(rotSpeed);
	cub->player.plane_y = oldplane_x * sin(rotSpeed) \
	+ cub->player.plane_y * cos(rotSpeed);
}

void	change_view(t_cub *cub, int side, double rotSpeed)
{
	double	oldplane_x;
	double	olddir_x;

	olddir_x = cub->player.dir_x;
	oldplane_x = cub->player.plane_x;
	if (side == ARRRIGHT)
		rotate(cub, olddir_x, oldplane_x, -rotSpeed);
	else
		rotate(cub, olddir_x, oldplane_x, rotSpeed);
}

void	choose_direction(t_cub *cub)
{
	if (cub->player.dir_x < 0 && cub->player.dir_y > 0)
	{
		cub->player.dir_x = 1 - pow(cub->player.dir_x, 2);
		cub->player.dir_y = 1 - pow(cub->player.dir_y, 2);
	}
	else if (cub->player.dir_x > 0 && cub->player.dir_y > 0)
	{
		cub->player.dir_x = 1 - pow(cub->player.dir_x, 2);
		cub->player.dir_y = -(1 - pow(cub->player.dir_y, 2));
	}
	else if (cub->player.dir_x > 0 && cub->player.dir_y < 0)
	{
		cub->player.dir_x = -(1 - pow(cub->player.dir_x, 2));
		cub->player.dir_y = -(1 - pow(cub->player.dir_y, 2));
	}
	else
	{
		cub->player.dir_x = -(1 - pow(cub->player.dir_x, 2));
		cub->player.dir_y = 1 - pow(cub->player.dir_y, 2);
	}
}

void	step_right_left(t_cub *cub, double moveSpeed, int move)
{
	double	old_x;
	double	old_y;

	old_x = cub->player.dir_x;
	old_y = cub->player.dir_y;
	choose_direction(cub);
	if (move == KEYD)
		step_fwd_back(cub, KEYW, moveSpeed);
	else
		step_fwd_back(cub, KEYS, moveSpeed);
	cub->player.dir_x = old_x;
	cub->player.dir_y = old_y;
}

void	step_fwd_back(t_cub *cub, int side, double moveSpeed)
{
	if (side == KEYW)
	{
		if (cub->map[(int)(cub->player.pos_x + \
		cub->player.dir_x * moveSpeed)][(int)(cub->player.pos_y)] == '0')
			cub->player.pos_x += cub->player.dir_x * moveSpeed;
		if (cub->map[(int)(cub->player.pos_x)][(int)(cub->player.pos_y \
		+ cub->player.dir_y * moveSpeed)] == '0')
			cub->player.pos_y += cub->player.dir_y * moveSpeed;
	}
	else if (side == KEYS)
	{
		if (cub->map[(int)(cub->player.pos_x - \
		cub->player.dir_x * moveSpeed)][(int)(cub->player.pos_y)] == '0')
			cub->player.pos_x -= cub->player.dir_x * moveSpeed;
		if (cub->map[(int)(cub->player.pos_x)][(int)(cub->player.pos_y - \
		cub->player.dir_y * moveSpeed)] == '0')
			cub->player.pos_y -= cub->player.dir_y * moveSpeed;
	}
}
