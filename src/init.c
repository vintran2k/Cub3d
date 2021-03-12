/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:39:10 by vintran           #+#    #+#             */
/*   Updated: 2021/03/12 16:12:44 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = s;
	i = -1;
	while (++i < n)
	{
		str[i] = 0;
	}
	s = str;
}

/*void	init_null_ptr(t_var *var)
{
	var->map = NULL;
	var->no = NULL;
	var->so = NULL;
	var->we = NULL;
	var->ea = NULL;
	var->sp = NULL;
	var->sprite.zbuffer = NULL;
	var->sprite.pos = NULL;
	var->sprite.order = NULL;
	var->sprite.dist = NULL;
	var->mlx.mlx_win = NULL;
	var->mlx.img = NULL;
	var->texture[0].img = NULL;
	var->texture[1].img = NULL;
	var->texture[2].img = NULL;
	var->texture[3].img = NULL;
	var->texture[4].img = NULL;
	//ft_bzero(var, sizeof(t_var));
	//ft_bzero(&var->mlx, sizeof(var->mlx));
}*/

void	init_var(t_var *var)
{
	ft_bzero(var, sizeof(t_var));
	ft_bzero(&var->mlx, sizeof(var->mlx));
	ft_bzero(&var->sprite, sizeof(t_sprite));
	var->player_x = -1;
	var->player_y = -1;
	var->f = -1;
	var->c = -1;
	var->map_beg = 1;
	//init_null_ptr(var);
}

void	init_direction(t_var *var)
{
	var->raycst.dirx = 0;
	var->raycst.diry = 0;
	var->raycst.planex = 0;
	var->raycst.planey = 0;
	if (var->player_dir == 'N')
	{
		var->raycst.dirx = -1;
		var->raycst.planey = 0.66;
	}
	if (var->player_dir == 'S')
	{
		var->raycst.dirx = 1;
		var->raycst.planey = -0.66;
	}
	if (var->player_dir == 'E')
	{
		var->raycst.diry = 1;
		var->raycst.planex = 0.66;
	}
	if (var->player_dir == 'W')
	{
		var->raycst.diry = -1;
		var->raycst.planex = -0.66;
	}
}

void	init_raycst(t_var *var)
{
	var->raycst.posx = (double)var->player_x + 0.5;
	var->raycst.posy = (double)var->player_y + 0.5;
	init_direction(var);
	var->move.forward = 0;
	var->move.back = 0;
	var->move.left = 0;
	var->move.right = 0;
	var->move.rotate_left = 0;
	var->move.rotate_right = 0;
	var->move.movespeed = 0.09;
	var->move.rotspeed = 0.033 * 2;
}
