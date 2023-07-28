#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <libft.h>
# include <stdlib.h>
# include <fcntl.h>

# ifdef __linux__
#  define ESC 65307
#  define ARRUP 65362
#  define ARRRIGHT 65363
#  define ARRDOWN 65364
#  define ARRLEFT 65361
#  define KEYW 119
#  define KEYD 100
#  define KEYS 115
#  define KEYA 97
# else
#  define ESC 53
#  define UP 13
#  define RIGHT 2
#  define DOWN 1
#  define LEFT 0
#  define UP2 126
#  define RIGHT2 124
#  define DOWN2 125
#  define LEFT2 123
# endif

# define W map_width
# define H map_height

typedef struct s_view
{
	void	*north;
	void	*south;
	void	*west;
	void	*east;
}	t_view;

typedef struct s_ray
{
	double	rayX;
	double	rayY;
	double	cameraX;
}	t_ray;

typedef struct s_player
{
	t_view	view;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}	t_player;

typedef struct	img
{
	void	*img;
	char	*addr;
	void	*black;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
}	t_mlx;

typedef struct s_cub
{
	t_ray		ray;
	t_mlx		mlx;
	t_img		img;
	char		**map;
	int			mapX;
	int			mapY;
	t_player	player;
	int			map_width;
	int			map_height;
}	t_cub;

void	printmap(t_cub cub);
void	err_msg(int condition, char *msg);
void	find_player(t_cub *cub, char player);
int		quit_game(t_cub *cub);
void	create_img(t_cub *cub);
int		key_up(int key, t_cub *cub);
int		key_down(int key, t_cub *cub);
void	raycaster(t_cub *cub);
int		trgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);


#endif