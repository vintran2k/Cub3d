SRC =	event_key.c							\
		exit.c								\
		get_map.c							\
		get_next_line.c						\
		get_next_line_utils.c				\
		init2.c								\
		init.c								\
		main.c								\
		move.c								\
		parsing.c							\
		parsing_map.c						\
		parsing_map_params.c				\
		parsing_utils.c						\
		raycasting.c						\
		save.c								\
		sprite.c							\
		texture.c							\
		utils.c								\

NAME = Cub3D

MLX_DIR = minilibx-linux
MLX = libmlx.a
CC = clang

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DPD = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))

.c.o:
	${CC} ${CFLAGS} -c$< -o ${<:.c=.o}

all:
	@$(MAKE) -j $(NAME)

$(NAME): $(OBJ)
		${CC} $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext
		@echo $(NAME) : Created !

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | .gitignore
		@mkdir -p $(OBJ_DIR)
		${CC} $(CFLAGS) -I $(INC_DIR) -I $(MLX_DIR) -c $< -o $@

.gitignore:
		@echo $(NAME) > .gitignore

clean:
	@rm -rf $(OBJ_DIR)
	@echo "obj deleted"

fclean:	clean
	@rm -rf $(NAME)
	@echo "[$(NAME)]: deleted"

re: fclean all

.PHONY: all, clean, fclean, re

-include $(DPD)