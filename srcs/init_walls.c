#include <cub3d.h>

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
