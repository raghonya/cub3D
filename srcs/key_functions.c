/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:59:03 by raghonya          #+#    #+#             */
/*   Updated: 2023/08/08 15:59:05 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	quit_game(t_cub *cub)
{
	destroy_gun_imgs(cub);
	destroy_textures(cub);
	destroy_map(cub->map);
	mlx_destroy_image(cub->mlx.ptr, cub->img.img);
	mlx_clear_window(cub->mlx.ptr, cub->mlx.win);
	mlx_destroy_window(cub->mlx.ptr, cub->mlx.win);
	exit(0);
	return (0);
}

int	key_press(int key, t_cub *cub)
{
	if (key == ESC)
		quit_game(cub);
	else if (key == KEYW)
		step_fwd_back(cub, KEYW, 0.16);
	else if (key == KEYS)
		step_fwd_back(cub, KEYS, 0.16);
	else if (key == KEYD)
		step_right_left(cub, 0.12, KEYD);
	else if (key == KEYA)
		step_right_left(cub, 0.12, KEYA);
	else if (key == ARRRIGHT)
		change_view(cub, ARRRIGHT, 0.06);
	else if (key == ARRLEFT)
		change_view(cub, ARRLEFT, 0.06);
	else if (key == SHOOT)
		gun_anim(cub, cub->gun->next);
	else
		return (1);
	if (key == SHOOT)
		re_render(cub, &cub->gun->img, 1);
	else
		re_render(cub, &cub->gun->img, 0);
	return (0);
}
