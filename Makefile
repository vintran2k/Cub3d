NAME			=	cub3D
CC				=	gcc

FLAGS			=	-Wall -Werror -Wextra -I $(HEADER_DIR) -I $(MLX_DIR)#-I $(LIBFT)
SRC_DIR			=	./srcs/
MLX_DIR			=	./minilibx-linux/
LIBFT_DIR		=	./libft/
HEADER_DIR		=	./inc/
SRCS			=	./srcs/main.c									\
					$(addprefix $(SRC_DIR), get_next_line.c)		\
					$(addprefix $(SRC_DIR), get_next_line_utils.c)	\
					$(addprefix $(SRC_DIR), utils.c)				\
					$(addprefix $(SRC_DIR), parsing_utils.c)		\
					$(addprefix $(SRC_DIR), init.c)					\
					$(addprefix $(SRC_DIR), init2.c)				\
					$(addprefix $(SRC_DIR), parsing.c)				\
					$(addprefix $(SRC_DIR), parsing_map_params.c)	\
					$(addprefix $(SRC_DIR), parsing_map.c)			\
					$(addprefix $(SRC_DIR), get_map.c)				\
					$(addprefix $(SRC_DIR), event_key.c)			\
					$(addprefix $(SRC_DIR), texture.c)				\
					$(addprefix $(SRC_DIR), move.c)					\
					$(addprefix $(SRC_DIR), raycasting.c)			\
					$(addprefix $(SRC_DIR), sprite.c)				\
					$(addprefix $(SRC_DIR), save.c)					\
					$(addprefix $(SRC_DIR), exit.c)					
OBJS			=	$(SRCS:.c=.o)

.c.o		:
				$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS)
			#make -C $(LIBFT)
			make -C $(MLX_DIR)
			$(CC) $(FLAGS) -o $(NAME) $(OBJS) -L $(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext
			@echo [$(NAME)] : Created !

clean		:
			rm -rf $(OBJS)
			#make clean -C $(LIBFT)
			make clean -C $(MLX_DIR)
			@echo "[OBJS] Deleted"

fclean		:	clean
			rm -f $(NAME)
			#make fclean -C $(LIBFT)
			@echo "[$(NAME)]: Deleted"

re			:	fclean all