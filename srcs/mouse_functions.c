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
	create_img(cub);
	if (button == 1)
		re_render(cub, &cub->gun->img, 1);
	else
		re_render(cub, &cub->gun->img, 0);
	return (0);
}

int	mouse_move(int x, int y, t_cub *cub)
{
	static int	old_x;

	(void)y;
	if (x < old_x)
		change_view(cub, ARRLEFT, 0.09);
	else if (x > old_x)
		change_view(cub, ARRRIGHT, 0.09);
	re_render(cub, &cub->gun->img, 0);
	old_x = x;
	return (0);
}
