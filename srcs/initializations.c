/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:58:34 by raghonya          #+#    #+#             */
/*   Updated: 2023/08/08 15:58:35 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	create_img(t_cub *cub, t_img *img, int wd, int ht)
{
	img->img = mlx_new_image(cub->mlx.ptr, wd, ht);
	err_msg(!img->img, "Can`t create image for you");
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
	err_msg(!img->addr, "Address initialization");
	img->wd = wd;
	img->ht = ht;
}

void	gun_pic_list_init(t_cub *cub, t_list **gun, char *pic)
{
	t_list	*new;

	new = ft_lstnew("");
	err_msg(!new, "Malloc error");
	new->img.img = mlx_xpm_file_to_image(cub->mlx.ptr, \
	pic, &new->img.wd, &new->img.ht);
	err_msg(!new->img.img, "Image initialization");
	new->img.addr = mlx_get_data_addr(new->img.img, \
	&new->img.bits_per_pixel, &new->img.line_length, \
	&new->img.endian);
	err_msg(!new->img.addr, "Address initialization");
	ft_lstadd_back(gun, new);
}

void	gun_pic_init(t_cub *cub)
{
	char	**gun_pics;
	int		i;

	i = -1;
	gun_pics = malloc(sizeof(char *) * 4);
	err_msg(!gun_pics, "Malloc error");
	*gun_pics = "pics/gun_anim1.xpm";
	*(gun_pics + 1) = "pics/gun_anim2.xpm";
	*(gun_pics + 2) = "pics/gun_anim3.xpm";
	*(gun_pics + 3) = "pics/gun_anim4.xpm";
	cub->gun = NULL;
	while (++i < 4)
		gun_pic_list_init(cub, &cub->gun, *(gun_pics + i));
	free(gun_pics);
}

void	initialization(t_cub *cub)
{
	cub->map_wd = 1000;
	cub->map_ht = 700;
	cub->show_map = 1;
	cub->bullet_count = 10;
	cub->mlx.ptr = mlx_init();
	err_msg(!cub->mlx.ptr, "Mlx init error");
	cub->mlx.win = mlx_new_window(cub->mlx.ptr, cub->map_wd, cub->map_ht + 20, \
	"Wolfenstein 3D without guns and enemies");
	err_msg(!cub->mlx.win, "Can`t open window for you");
	wall_textures(cub);
	gun_pic_init(cub);
	create_img(cub, &cub->img, cub->map_wd, cub->map_ht);
}
