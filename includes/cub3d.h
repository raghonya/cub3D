/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:51:53 by raghonya          #+#    #+#             */
/*   Updated: 2023/08/26 18:07:25 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <libft.h>
# include <fcntl.h>
# include <stdlib.h>
# include <get_next_line.h>

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
#  define MMAP_HIDE 109
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
#  define MMAP_HIDE 46
# endif

# define STEP_FB 0.16
# define STEP_LR 0.12
# define ROTATE_ARROW 0.06
# define ROTATE_MOUSE 0.09
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define MMAP_ICON 10
# define BULL_CHANGE 1
# define MALLOC "Malloc error"

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

typedef struct s_news
{
	struct s_news	*next;
	char			*line;
	struct s_news	*prev;
}	t_news;

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
	t_img		minimap;
	int			show_map;
	int			ceil_color;
	int			floor_color;
	char		**texs_path;
	int			bullet_count;
}	t_cub;

void			free_2d(char **s);
void			printmap(t_cub cub);
int				lst_siz(t_news *news);
int				quit_game(t_cub *cub);
void			destroy_map(char **map);
void			make_news(t_news **news);
char			**create_all_map(int fd);
void			draw_minimap(t_cub *cub);
int				ft_matlen(char **matrix);
void			wall_textures(t_cub *cub);
t_list			*ft_lstnew(void *content);
void			find_step_dir(t_cub *cub);
void			dda_algorithm(t_cub *cub);
void			initialization(t_cub *cub);
int				len_ignore_zero(char *str);
int				calc_texture_x(t_cub *cub);
void			create_wall_img(t_cub *cub);
t_img			*choose_texture(t_cub *cub);
int				check_file_name(char **argv);
void			check_empty(char **map_maze);
void			destroy_gun_imgs(t_cub *cub);
void			destroy_textures(t_cub *cub);
int				key_press(int key, t_cub *cub);
int				key_release(int key, t_cub *cub);
int				trgb(int t, int r, int g, int b);
void			err_msg(int condition, char *msg);
void			gun_anim(t_cub *cub, t_list *anim);
void			replace_first_tab(char **map_maze);
void			check_map_simbols(char **map_maze);
void			check_count_player(char **map_maze);
void			calc_ray_pos(t_cub *cub, int pixel);
char			*ft_strstr(char *str, char *to_find);
int				mouse_move(int x, int y, t_cub *cub);
t_news			*find_node(t_news **news, char *line);
void			lst_pop(t_news **news, t_news *remove);
void			calc_draw_ends(t_cub *cub, t_draw *tex);
void			set_dir_and_pos(t_cub *cub, char player);
void			ft_lstadd_back(t_list **lst, t_list *new);
char			**create_map_maze(char **argv, char **map);
void			draw_texture(t_cub *cub, int x, int tex_x);
void			replace_player(t_cub *cub, char **map_maze);
void			check_color_line(t_cub *cub, char **splited);
unsigned int	my_mlx_color_taker(t_img *data, int x, int y);
void			re_render(t_cub *cub, t_img *img, int bul_change, int b);
void			print_gun(t_img *pic, t_img *game, int b);
int				mouse_press(int button, int x, int y, t_cub *cub);
void			change_view(t_cub *cub, int side, double rotSpeed);
void			create_img(t_cub *cub, t_img *img, int wd, int ht);
void			step_fwd_back(t_cub *cub, int side, double moveSpeed);
void			raycaster(t_cub *cub, t_img *anim, int bullet_change, int b);
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
void			step_right_left(t_cub *cub, double moveSpeed, int move);
void			check_before_map(t_cub *cub, char **map, t_news **news);
void			rotate(t_cub *cub, double oDX, double oPX, double rotSpeed);

#endif
