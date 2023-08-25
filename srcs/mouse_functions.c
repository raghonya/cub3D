/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:00:33 by raghonya          #+#    #+#             */
/*   Updated: 2023/08/08 16:00:33 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	mouse_press(int button, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if (button == 1)
		gun_anim(cub, cub->gun->next);
	mlx_destroy_image(cub->mlx.ptr, cub->img.img);
	create_img(cub, &cub->img, cub->map_wd, cub->map_ht);
	if (button == 1)
		re_render(cub, &cub->gun->img, BULL_CHANGE);
	else
		re_render(cub, &cub->gun->img, !BULL_CHANGE);
	return (0);
}

int	mouse_move(int x, int y, t_cub *cub)
{
	static int	old_x;

	(void)y;
	if (x < old_x)
		change_view(cub, ARRLEFT, ROTATE_MOUSE);
	else if (x > old_x)
		change_view(cub, ARRRIGHT, ROTATE_MOUSE);
	re_render(cub, &cub->gun->img, !BULL_CHANGE);
	old_x = x;
	return (0);
}
