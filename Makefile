NAME				=	cub3D
SRCS_DIR			=	./srcs/
MLX_DIR				=	./minilibx-linux/
SRCS_BONUS_DIR		=	./bonus/srcs/
SRCS				=	main.c						\
						get_next_line.c				\
						get_next_line_utils.c		\
						utils.c						\
						parsing_utils.c				\
						init.c						\
						init2.c						\
						parsing.c					\
						parsing_map_params.c		\
						parsing_map.c				\
						get_map.c					\
						event_key.c					\
						texture.c					\
						move.c						\
						raycasting.c				\
						sprite.c					\
						save.c						\
						exit.c					
SRCS_BONUS			=	main_bonus.c				\
						event_key_bonus.c			\
						exit_bonus.c				\
						floor_bonus.c				\
						get_map_bonus.c				\
						get_next_line_bonus.c		\
						get_next_line_utils_bonus.c	\
						init2_bonus.c				\
						init_bonus.c				\
						minimap_bonus.c				\
						move_bonus.c				\
						parsing_bonus.c				\
						parsing_map_bonus.c			\
						parsing_map_params_bonus.c	\
						parsing_utils_bonus.c		\
						raycasting_bonus.c			\
						save_bonus.c				\
						sprite_bonus.c				\
						texture_bonus.c				\
						utils_bonus.c
SRCS_BASENAME		=	$(addprefix $(SRCS_DIR), $(SRCS))
SRCS_BONUS_BASENAME	=	$(addprefix $(SRCS_BONUS_DIR), $(SRCS_BONUS)) 
OBJS				=	$(SRCS_BASENAME:.c=.o)
OBJS_BONUS			=	$(SRCS_BONUS_BASENAME:.c=.o)
CC					=	gcc
FLAGS				=	-Wall -Werror -Wextra -I$(MLX_DIR)

.c.o		:
			$(CC) -c $< -o $(<:.c=.o) $(FLAGS)

$(NAME)		:	$(OBJS)
			make -C $(MLX_DIR)
			$(CC) $(OBJS) $(FLAGS) -o $(NAME) -L$(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext
			@echo [$(NAME)] : Created !

all			:	$(NAME)

clean		:
			rm -rf $(OBJS) $(OBJS_BONUS)
			make clean -C $(MLX_DIR)
			@echo [OBJS] : Deleted !

fclean		:	clean
			rm -f $(NAME)
			@echo [$(NAME)] : Deleted !

re			:	fclean all

bonus		:	fclean $(OBJS_BONUS)
			make -C $(MLX_DIR)
			$(CC) $(OBJS_BONUS) $(FLAGS) -o $(NAME) -L$(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext
			@echo [$(NAME)] : Created !
