#include <cub3d.h>

unsigned int	my_mlx_color_taker(t_img *data, int x, int y)
{
	char	*dst;

	if (x >= 0 && x <= data->wd && y >= 0 && y <= data->ht)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		return (*(unsigned int*)dst);
	}
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x <= data->wd && y >= 0 && y <= data->ht)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

int	trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
