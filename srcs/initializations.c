#include <cub3d.h>

void	create_img(t_cub *cub)
{
	cub->img.img = mlx_new_image(cub->mlx.ptr, cub->W, cub->H);
	err_msg(!cub->img.img, "Can`t create image for you");
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, \
	&cub->img.line_length, &cub->img.endian);
}

void	textures_init(t_cub *cub)
{
	TEXS = malloc(sizeof(t_img) * 5);
	err_msg(!TEXS, "Malloc Error");
	TEXS[0].img = mlx_xpm_file_to_image(cub->mlx.ptr, \
	"pics/eagle.xpm", &TEXS[0].wd, &TEXS[0].ht);
	TEXS[1].img = mlx_xpm_file_to_image(cub->mlx.ptr, \
	"pics/redbrick.xpm", &TEXS[1].wd, &TEXS[1].ht);
	TEXS[2].img = mlx_xpm_file_to_image(cub->mlx.ptr, \
	"pics/greystone.xpm", &TEXS[2].wd, &TEXS[2].ht);
	TEXS[3].img = mlx_xpm_file_to_image(cub->mlx.ptr, \
	"pics/bluestone.xpm", &TEXS[3].wd, &TEXS[3].ht);
	TEXS[4].img = mlx_xpm_file_to_image(cub->mlx.ptr, \
	"pics/colorstone.xpm", &TEXS[4].wd, &TEXS[4].ht);
	err_msg (!TEXS[0].img || !TEXS[1].img \
	|| !TEXS[2].img || !TEXS[3].img || !TEXS[4].img \
	|| TEXS[0].wd != TEXS[1].wd || TEXS[0].ht != TEXS[1].ht \
	|| TEXS[0].wd != TEXS[2].wd || TEXS[0].ht != TEXS[2].ht \
	|| TEXS[0].wd != TEXS[3].wd || TEXS[0].ht != TEXS[3].ht \
	|| TEXS[0].wd != TEXS[4].wd || TEXS[0].ht != TEXS[4].ht, \
	"Images Initialization");
	int i = -1;
	while (++i < 5)
		TEXS[i].addr = mlx_get_data_addr(TEXS[i].img, \
		&TEXS[i].bits_per_pixel, &TEXS[i].line_length, \
		&TEXS[i].endian);
}

void	initialization(t_cub *cub)
{
	int havai;

	cub->map_width = 1200;
	cub->map_height = 800;
	cub->player.dirX = 0;
	cub->player.dirY = 0;
	cub->player.planeX = 0;
	cub->player.planeY = 0;
	cub->mlx.ptr = mlx_init();
	err_msg(!cub->mlx.ptr, "Mlx init error");
	cub->mlx.win = mlx_new_window(cub->mlx.ptr, cub->W, cub->H, \
	"Wolfenstein 3D without guns and enemies");
	err_msg(!cub->mlx.win, "Can`t open window for you");
	textures_init(cub);
	create_img(cub);
}
