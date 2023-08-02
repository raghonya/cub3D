#include <cub3d.h>

int	check_points(t_cub *cub, int beginX, int *beginY, int *endY)
{
	if (*endY < *beginY)
	{
		*beginY += *endY;
		*endY = *beginY - *endY;
		*beginY -= *endY;
	}
	if (*endY < 0 || *beginY >= cub->H  || beginX < 0 || beginX >= cub->W)
		return (1);
	if (*beginY < 0)
		*beginY = 0;
	if (*endY >= cub->W)
		*endY = cub->H - 1;
	return (0);
}

// void	draw(t_cub *cub, int beginX, int beginY, int endY, int color)
// {
// 	int		pixels;
// 	double	deltaY;
// 	double	pixelX;
// 	double	pixelY;

// 	if (check_points(cub, beginX, &beginY, &endY))
// 		return ;
// 	pixelX = beginX;
// 	pixelY = beginY;
// 	deltaY = endY - beginY;
// 	pixels = deltaY;
// 	deltaY /= pixels;
// 	while (pixels)
// 	{
// 		my_mlx_pixel_put(&cub->img, pixelX, pixelY, color);
// 		pixelY += deltaY;
// 		--pixels;
// 	}
// }
