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

void	step_keys(int key, t_cub *cub)
{
	if (key == KEYW)
		step_fwd_back(cub, KEYW, STEP_FB);
	else if (key == KEYS)
		step_fwd_back(cub, KEYS, STEP_FB);
	else if (key == KEYD)
		step_right_left(cub, STEP_LR, KEYD);
	else if (key == KEYA)
		step_right_left(cub, STEP_LR, KEYA);
}

int	key_press(int key, t_cub *cub)
{
	if (key == ESC)
		quit_game(cub);
	else if (key == ARRRIGHT)
		change_view(cub, ARRRIGHT, ROTATE_ARROW);
	else if (key == ARRLEFT)
		change_view(cub, ARRLEFT, ROTATE_ARROW);
	else if (key == SHOOT)
		gun_anim(cub, cub->gun->next);
	else if (key == MMAP_HIDE)
		cub->show_map = !cub->show_map;
	else if (key == KEYW || key == KEYS \
	|| key == KEYA || key == KEYD)
		step_keys(key, cub);
	else
		return (1);
	if (key == SHOOT)
		re_render(cub, &cub->gun->img, BULL_CHANGE);
	else
		re_render(cub, &cub->gun->img, !BULL_CHANGE);
	return (0);
}
