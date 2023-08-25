/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:58:17 by raghonya          #+#    #+#             */
/*   Updated: 2023/08/08 15:58:20 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	create_wall_img(t_cub *cub)
{
	cub->texs = malloc(sizeof(t_img) * 4);
	err_msg(!cub->texs, "Malloc Error");
	cub->texs[0].img = mlx_xpm_file_to_image(cub->mlx.ptr, \
	cub->texs_path[0], &cub->texs[0].wd, &cub->texs[0].ht);
	cub->texs[1].img = mlx_xpm_file_to_image(cub->mlx.ptr, \
	cub->texs_path[1], &cub->texs[1].wd, &cub->texs[1].ht);
	cub->texs[2].img = mlx_xpm_file_to_image(cub->mlx.ptr, \
	cub->texs_path[2], &cub->texs[2].wd, &cub->texs[2].ht);
	cub->texs[3].img = mlx_xpm_file_to_image(cub->mlx.ptr, \
	cub->texs_path[3], &cub->texs[3].wd, &cub->texs[3].ht);
}

void	wall_textures(t_cub *cub)
{
	int	i;

	i = -1;
	create_wall_img(cub);
	err_msg (!cub->texs[0].img || !cub->texs[1].img \
	|| !cub->texs[2].img || !cub->texs[3].img \
	|| cub->texs[0].wd != cub->texs[1].wd \
	|| cub->texs[0].ht != cub->texs[1].ht \
	|| cub->texs[0].wd != cub->texs[2].wd \
	|| cub->texs[0].ht != cub->texs[2].ht \
	|| cub->texs[0].wd != cub->texs[3].wd \
	|| cub->texs[0].ht != cub->texs[3].ht, \
	"Images Initialization");
	while (++i < 4)
		cub->texs[i].addr = mlx_get_data_addr(cub->texs[i].img, \
		&cub->texs[i].bits_per_pixel, &cub->texs[i].line_length, \
		&cub->texs[i].endian);
}
