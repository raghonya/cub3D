#include <cub3d.h>

void	create_img(t_cub *cub)
{
	cub->img.img = mlx_new_image(cub->mlx.ptr, cub->W, cub->H);
	err_msg(!cub->img.img, "Can`t create image for you");
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, \
	&cub->img.line_length, &cub->img.endian);
	cub->img.wd = cub->W;
	cub->img.ht = cub->H;
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
	int havai;

	cub->map_width = 1000;
	cub->map_height = 700;
	cub->player.dirX = 0;
	cub->player.dirY = 0;
	cub->player.planeX = 0;
	cub->player.planeY = 0;
	cub->bullet_count = 10;
	cub->mlx.ptr = mlx_init();
	err_msg(!cub->mlx.ptr, "Mlx init error");
	cub->mlx.win = mlx_new_window(cub->mlx.ptr, cub->W, cub->H + 100, \
	"Wolfenstein 3D without guns and enemies");
	err_msg(!cub->mlx.win, "Can`t open window for you");
	wall_textures(cub);
	gun_pic_init(cub);
	create_img(cub);
}
