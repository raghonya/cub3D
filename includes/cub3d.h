#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <libft.h>
# include <stdlib.h>
# include <fcntl.h>

/*
Map i mej
0 - empty space
1 - walls with different pictures for all sides
2 - svastika flag
3 - prison with skeleton
*/

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
#  define SHOOT 32
# else
#  define ESC 53
#  define ARRUP 126
#  define ARRRIGHT 124
#  define ARRDOWN 125
#  define ARRLEFT 123
#  define KEYW 13
#  define KEYD 2
#  define KEYS 1
#  define KEYA 0
#  define SHOOT 49
# endif

# define W map_width
# define H map_height
# define TEXS cub->textures
# define TEXWIDTH TEXS[0].wd
# define TEXHEIGHT TEXS[0].ht

typedef struct s_view
{
	void	*north;
	void	*south;
	void	*west;
	void	*east;
}	t_view;

typedef struct s_ray
{
	int		hit;
	int		side;
	double	rayX;
	double	rayY;
	double	cameraX;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
}	t_ray;

typedef struct s_player
{
	t_view	view;
	double	posX;
	double	posY;
	int		mapX;
	int		mapY;
	double	dirX;
	double	dirY;
	int		stepX;
	int		stepY;
	double	planeX;
	double	planeY;
}	t_player;

typedef struct s_img
{
	int		wd;
	int		ht;
	void	*img;
	char	*addr;
	int		endian;
	int		bits_per_pixel;
	int		line_length;
}	t_img;

typedef struct s_list
{
	t_img			img;
	struct s_list	*next;
}	t_list;

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
	int			mapX;
	int			mapY;
	t_list		*gun;
	char		**map;
	t_player	player;
	int			map_width;
	t_img		*textures;
	int			map_height;
	int			bullet_count;
}	t_cub;

typedef struct s_draw
{
	int		texX;
	int		texY;
	double	step;
	double	texPos;
	int		drawEnd;
	int		drawStart;
	int		lineHeight;
}	t_draw;

void			printmap(t_cub cub);
int				quit_game(t_cub *cub);
void			create_img(t_cub *cub);
void			find_step_dir(t_cub *cub);
void			DDA_algorithm(t_cub *cub);
void			initialization(t_cub *cub);
int				calc_texture_x(t_cub *cub);
void			wall_textures(t_cub *cub);
t_list			*ft_lstnew(void *content);
void			create_wall_img(t_cub *cub);
t_img			*choose_texture(t_cub *cub);
int				key_press(int key, t_cub *cub);
int				key_release(int key, t_cub *cub);
int				trgb(int t, int r, int g, int b);
void			change_view(t_cub *cub, int side);
void			err_msg(int condition, char *msg);
void			gun_anim(t_cub *cub, t_list *anim);
void			raycaster(t_cub *cub, t_img *anim);
void			right(t_cub *cub, double moveSpeed);
void			step_fwd_back(t_cub *cub, int side);
void			calc_ray_pos(t_cub *cub, int pixel);
void			find_player(t_cub *cub, char player);
void			calc_draw_ends(t_cub *cub, t_draw *tex);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			draw_texture(t_cub *cub, int x, int texX);
unsigned int	my_mlx_color_taker(t_img *data, int x, int y);
void			print_gun(t_cub *cub, t_img *pic, t_img *game, int w, int h);
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
void			draw(t_cub *cub, int beginX, int beginY, int endY, int color);
void			rotate(t_cub *cub, double oDX, double oPX, double rotSpeed);

#endif
