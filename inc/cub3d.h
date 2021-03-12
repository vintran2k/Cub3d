/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:04:19 by vintran           #+#    #+#             */
/*   Updated: 2021/03/12 15:59:46 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"

# define BUFFER_SIZE	4096
# define ROTATE_L		65361
# define ROTATE_R		65363
# define FORWARD_W		119
# define BACK_S			115
# define LEFT_A			97
# define RIGHT_D		100
# define ESC			65307

typedef struct	s_raycst
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
}				t_raycst;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			width;
	int			height;
	int			endian;
}				t_mlx;

typedef struct	s_move
{
	int			forward;
	int			back;
	int			left;
	int			right;
	int			rotate_left;
	int			rotate_right;
	double		movespeed;
	double		rotspeed;
}				t_move;

typedef struct	s_texel
{
	int			dir;
	double		wallx;
	int			texx;
	int			texy;
	double		step;
	double		texpos;
}				t_texel;

typedef struct	s_pos
{
	double		x;
	double		y;
}				t_pos;

typedef struct	s_sprite
{
	int			nb;
	double		*zbuffer;
	t_pos		*pos;
	int			*order;
	double		*dist;
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			spriteheight;
	int			spritewidth;
	int			drawstartx;
	int			drawstarty;
	int			drawendy;
	int			drawendx;
	int			stripe;
	int			texx;
	int			texy;
}				t_sprite;

typedef struct	s_var
{
	char		*file;
	char		*line;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*sp;
	int			screenx;
	int			screeny;
	int			rx;
	int			ry;
	int			player_x;
	int			player_y;
	char		player_dir;
	int			f;
	int			c;
	int			save;
	int			map_beg;
	int			map_lines;
	int			l_line;
	char		**map;
	t_mlx		mlx;
	t_raycst	raycst;
	t_move		move;
	t_mlx		texture[5];
	t_texel		texel;
	t_sprite	sprite;
}				t_var;

//GNL:
size_t			ft_strlen(const char *s);          //
char			*ft_strchr(const char *s, int c);  //
char			*ft_strcpy(char *dst, char *src);
char			*ft_strdup(const char *s);         //
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				get_next_line(int fd, char **line, t_var *var);

//CUB3D:
void			ft_error(t_var *var, char *error_msg);
int				ft_exit_cub(t_var *var);
void			init_var(t_var *var);
void			parsing(int argc, char **argv, t_var *var);
void			parsing_file(char *file, t_var *var);
void			ft_putstr(char *str);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strndup(const char *s, size_t n);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
int				is_empty(char *str);
int				through_space(char *str);
int				is_longest(char *line, int prev);
void			get_path_texture(t_var *var, char *line, char **path);
void			get_resolution(t_var *var, char *line);
void			get_rgb(t_var *var, char *line, int *color);
void			get_map(char *file, t_var *var);
void			parsing_map(t_var *var);
int				check_map_char(char *line);
void			get_texture_img(t_var *var);
void			draw_wall(t_var *var, int x, int y);
void			init_raycasting(t_var *var, int x);
void			init_raycst(t_var *var);
int				raycasting(t_var *var);
int				key_press(int keycode, t_var *var);
int				key_release(int keycode, t_var *var);
void			move_rotate_player(t_var *var);
void			init_sprite(t_var *var);
void			put_sprite(t_var *var);
void			ft_save(t_var *var);

#endif
