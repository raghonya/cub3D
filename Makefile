NAME	=	cub3D

CFLAGS	=	#-Wall -Wextra -Werror

f		=	-fsanitize=address -g

LIB		=	libft

DEP		=	Makefile includes/cub3d.h

OBJDIR	=	obj

SRCSDIR	=	srcs

SRCS	=	srcs/cub3d.c \
			srcs/destroy.c \
			srcs/textures.c \
			srcs/raycasting.c \
			srcs/init_walls.c \
			srcs/calculations.c \
			srcs/key_functions.c \
			srcs/pixel_actions.c \
			srcs/step_and_view.c \
			srcs/gun_animation.c \
			srcs/list_functions.c \
			srcs/render_minimap.c \
			srcs/mouse_functions.c \
			srcs/initializations.c

OBJS	=	$(SRCS:$(SRCSDIR)/%.c=$(OBJDIR)/%.o)

MLX		=	minilibx-linux

LFLAGS	=	-L libft -lft -L $(MLX) -lmlx -lm -lXext -lX11 -lz

ifeq ($(shell uname -s), Darwin)
	MLX = minilibx-MacOS
	LFLAGS = -L libft -lft -L $(MLX) -lm -lmlx -framework OpenGL -framework AppKit
endif

IFLAGS	=	-I $(MLX) -I includes -I libft

all:	objdir run_MLX run_lib $(NAME)

objdir:
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:	$(SRCSDIR)/%.c $(DEP)
	$(CC) $(CFLAGS) $(f) $(IFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(f) $(OBJS) $(IFLAGS) $(LFLAGS) -o $(NAME)

run_lib:
	make -C $(LIB)

run_MLX:
	make -C $(MLX)

clean:
	make clean -C $(LIB)
	make clean -C $(MLX)
	rm -rf $(OBJDIR)

fclean:	clean
	make fclean -C $(LIB)
	rm -rf $(NAME)

re:	fclean all

.PHONY:	all clean fclean re