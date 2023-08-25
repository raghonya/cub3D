/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:56:39 by raghonya          #+#    #+#             */
/*   Updated: 2023/08/08 15:56:41 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	destroy_gun_imgs(t_cub *cub)
{
	t_list	*tmp;

	while (cub->gun)
	{
		tmp = cub->gun;
		cub->gun = tmp->next;
		mlx_destroy_image(cub->mlx.ptr, tmp->img.img);
		free(tmp);
	}
}

void	destroy_map(char **map)
{
	free_2d(map);
}

void	destroy_textures(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		mlx_destroy_image(cub->mlx.ptr, cub->texs[i].img);
		free(cub->texs_path[i]);
	}
	free(cub->texs);
	free(cub->texs_path);
}
