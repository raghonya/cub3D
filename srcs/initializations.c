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

void	create_wall_img(t_cub *cub)
{
	TEXS = malloc(sizeof(t_img) * 6);
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
	"pics/flagsvastiki.xpm", &TEXS[4].wd, &TEXS[4].ht);
	TEXS[5].img = mlx_xpm_file_to_image(cub->mlx.ptr, \
	"pics/bantik.xpm", &TEXS[5].wd, &TEXS[5].ht);
}

void	wall_textures(t_cub *cub)
{
	int	i;

	i = -1;
	create_wall_img(cub);
	err_msg (!TEXS[0].img || !TEXS[1].img || !TEXS[2].img 
	|| !TEXS[3].img || !TEXS[4].img || !TEXS[5].img \
	|| TEXS[0].wd != TEXS[1].wd || TEXS[0].ht != TEXS[1].ht \
	|| TEXS[0].wd != TEXS[2].wd || TEXS[0].ht != TEXS[2].ht \
	|| TEXS[0].wd != TEXS[3].wd || TEXS[0].ht != TEXS[3].ht, \
	"Images Initialization");
	while (++i < 6)
		TEXS[i].addr = mlx_get_data_addr(TEXS[i].img, \
		&TEXS[i].bits_per_pixel, &TEXS[i].line_length, \
		&TEXS[i].endian);
}

void	textures_init(t_cub *cub)
{
	int	i;
	
	i = -1;
	wall_textures(cub);
	cub->pistol = malloc(sizeof(t_list));
	err_msg(!cub->pistol, "Malloc error");
	cub->pistol->img.img = mlx_xpm_file_to_image(cub->mlx.ptr, \
	"pics/pistol_anim1.xpm", &cub->pistol->img.wd, &cub->pistol->img.ht);
	err_msg(!cub->pistol->img.img, "Image initialization");
	printf ("%p\n", cub->pistol->img.img);
	cub->pistol->img.addr = mlx_get_data_addr(cub->pistol->img.img, \
	&cub->pistol->img.bits_per_pixel, &cub->pistol->img.line_length, \
	&cub->pistol->img.endian);

	cub->pistol->next = malloc(sizeof(t_list));
	cub->pistol->next->img.img = mlx_xpm_file_to_image(cub->mlx.ptr, \
	"pics/pistol_anim2.xpm", &cub->pistol->next->img.wd, &cub->pistol->next->img.ht);
	cub->pistol->next->img.addr = mlx_get_data_addr(cub->pistol->next->img.img, \
	&cub->pistol->next->img.bits_per_pixel, &cub->pistol->next->img.line_length, \
	&cub->pistol->next->img.endian);
	
	cub->pistol->next->next = malloc(sizeof(t_list));
	cub->pistol->next->next->img.img = mlx_xpm_file_to_image(cub->mlx.ptr, \
	"pics/pistol_anim3.xpm", &cub->pistol->next->next->img.wd, &cub->pistol->next->next->img.ht);
	cub->pistol->next->next->img.addr = mlx_get_data_addr(cub->pistol->next->next->img.img, \
	&cub->pistol->next->next->img.bits_per_pixel, &cub->pistol->next->next->img.line_length, \
	&cub->pistol->next->next->img.endian);
	
	cub->pistol->next->next->next = malloc(sizeof(t_list));
	cub->pistol->next->next->next->img.img = mlx_xpm_file_to_image(cub->mlx.ptr, \
	"pics/pistol_anim4.xpm", &cub->pistol->next->next->next->img.wd, &cub->pistol->next->next->next->img.ht);
	cub->pistol->next->next->next->img.addr = mlx_get_data_addr(cub->pistol->next->next->next->img.img, \
	&cub->pistol->next->next->next->img.bits_per_pixel, &cub->pistol->next->next->next->img.line_length, \
	&cub->pistol->next->next->next->img.endian);
	cub->pistol->next->next->next->next = NULL;
	err_msg(!cub->pistol->img.img || !cub->pistol->next->img.img || !cub->pistol->next->next->img.img || !cub->pistol->next->next->next->img.img, "vata");
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
	cub->bullet_count = 10;
	cub->mlx.ptr = mlx_init();
	err_msg(!cub->mlx.ptr, "Mlx init error");
	cub->mlx.win = mlx_new_window(cub->mlx.ptr, cub->W, cub->H, \
	"Wolfenstein 3D without guns and enemies");
	err_msg(!cub->mlx.win, "Can`t open window for you");
	textures_init(cub);
	create_img(cub);
}
