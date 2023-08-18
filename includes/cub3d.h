/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:51:53 by raghonya          #+#    #+#             */
/*   Updated: 2023/08/08 15:51:54 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define TEXWIDTH 64
# define TEXHEIGHT 64

typedef struct s_draw
{
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		draw_end;
	int		draw_start;
	int		line_height;
}	t_draw;

typedef struct s_ray
{
	int		hit;
	int		side;
	double	ray_x;
	double	ray_y;
	double	camera_x;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perp_wall_dist;
}	t_ray;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	int		map_x;
	int		map_y;
	double	dir_x;
	double	dir_y;
	int		step_x;
	int		step_y;
	double	plane_x;
	double	plane_y;
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
	t_list		*gun;
	t_img		*texs;
	char		**map;
	int			map_wd;
	int			map_ht;
	t_player	player;
	int			bullet_count;
}	t_cub;

void			printmap(t_cub cub);
int				quit_game(t_cub *cub);
void			create_img(t_cub *cub);
void			destroy_map(char **map);
void			wall_textures(t_cub *cub);
t_list			*ft_lstnew(void *content);
void			find_step_dir(t_cub *cub);
void			dda_algorithm(t_cub *cub);
void			initialization(t_cub *cub);
int				calc_texture_x(t_cub *cub);
void			create_wall_img(t_cub *cub);
t_img			*choose_texture(t_cub *cub);
void			destroy_gun_imgs(t_cub *cub);
void			destroy_textures(t_cub *cub);
int				key_press(int key, t_cub *cub);
int				key_release(int key, t_cub *cub);
int				trgb(int t, int r, int g, int b);
void			err_msg(int condition, char *msg);
void			gun_anim(t_cub *cub, t_list *anim);
void			calc_ray_pos(t_cub *cub, int pixel);
int				mouse_move(int x, int y, t_cub *cub);
void			find_player(t_cub *cub, char player);
void			calc_draw_ends(t_cub *cub, t_draw *tex);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			draw_texture(t_cub *cub, int x, int tex_x);
unsigned int	my_mlx_color_taker(t_img *data, int x, int y);
void			re_render(t_cub *cub,t_img *img, int bul_change);
void			print_gun(t_img *pic, t_img *game, int w, int h);
int				mouse_press(int button, int x, int y, t_cub *cub);
void			change_view(t_cub *cub, int side, double rotSpeed);
void			step_fwd_back(t_cub *cub, int side, double moveSpeed);
void			raycaster(t_cub *cub, t_img *anim, int bullet_change);
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
void			step_right_left(t_cub *cub, double moveSpeed, int move);
void			rotate(t_cub *cub, double oDX, double oPX, double rotSpeed);

#endif
