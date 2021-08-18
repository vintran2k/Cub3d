/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:39:10 by vintran           #+#    #+#             */
/*   Updated: 2021/03/25 01:40:20 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus.h"

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

void	init_var(t_var *var)
{
	ft_bzero(var, sizeof(t_var));
	ft_bzero(&var->mlx, sizeof(var->mlx));
	ft_bzero(&var->sprite, sizeof(t_sprite));
	ft_bzero(&var->raycst, sizeof(t_raycst));
	var->player_x = -1;
	var->player_y = -1;
	var->f = -1;
	var->c = -1;
	var->map_beg = 1;
}

void	init_direction(t_var *var)
{
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
	var->move.movespeed = 0.04;
	var->move.rotspeed = 0.05;
}

void	init_minimap(t_var *var)
{
	var->mc.rx = var->rx / 2.5;
	var->mc.ry = var->ry / 2.5;
	var->mc.case_s = var->mc.rx / var->l_line;
	if (var->mc.case_s > var->mc.ry / var->map_lines)
		var->mc.case_s = var->mc.ry / var->map_lines;
	var->mc.edge = 3 * var->mc.case_s;
	var->mc.ry = (var->map_lines + 2) * var->mc.case_s + var->mc.edge;
	var->mc.rx = (var->l_line + 2) * var->mc.case_s + var->mc.edge;
	var->mc.color[0] = 2171169;
	var->mc.color[1] = 0x000000;
	var->mc.color[2] = 0x00001A;
}
