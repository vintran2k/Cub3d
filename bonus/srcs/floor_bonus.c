/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:06:46 by vintran           #+#    #+#             */
/*   Updated: 2021/03/25 01:39:54 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus.h"

void	init_fc_casting(t_var *var, int y, int t)
{
	var->fc.raydirx0 = var->raycst.dirx - var->raycst.planex;
	var->fc.raydiry0 = var->raycst.diry - var->raycst.planey;
	var->fc.raydirx1 = var->raycst.dirx + var->raycst.planex;
	var->fc.raydiry1 = var->raycst.diry + var->raycst.planey;
	var->fc.p = y - var->ry / 2;
	var->fc.posz = 0.5 * var->ry;
	var->fc.rowdistance = var->fc.posz / var->fc.p;
	var->fc.floorstepx =
	var->fc.rowdistance * (var->fc.raydirx1 - var->fc.raydirx0) / var->rx;
	var->fc.floorstepy =
	var->fc.rowdistance * (var->fc.raydiry1 - var->fc.raydiry0) / var->rx;
	var->fc.floorx = var->raycst.posx + var->fc.rowdistance * var->fc.raydirx0;
	var->fc.floory = var->raycst.posy + var->fc.rowdistance * var->fc.raydiry0;
	if (t == 5)
	{
		var->fc.floorx =
		var->raycst.posx - var->fc.rowdistance * var->fc.raydirx0;
		var->fc.floory =
		var->raycst.posy - var->fc.rowdistance * var->fc.raydiry0;
	}
}

void	get_texel_color(t_var *var, int *color, int t)
{
	var->fc.cellx = (int)(var->fc.floorx);
	var->fc.celly = (int)(var->fc.floory);
	var->fc.tx = (int)(var->texture[t].width *
	(var->fc.floorx - var->fc.cellx)) & (var->texture[t].width - 1);
	var->fc.ty = (int)(var->texture[t].height *
	(var->fc.floory - var->fc.celly)) & (var->texture[t].height - 1);
	if (t == 5)
	{
		var->fc.floorx -= var->fc.floorstepx;
		var->fc.floory -= var->fc.floorstepy;
	}
	else
	{
		var->fc.floorx += var->fc.floorstepx;
		var->fc.floory += var->fc.floorstepy;
	}
	*color = var->texture[t].addr[var->fc.ty *
	var->texture[6].line_length / 4 + var->fc.tx];
	*color = (*color >> 1) & 8355711;
}

void	fc_casting(t_var *var, int t)
{
	int y;
	int x;
	int color;
	int endy;

	y = var->ry / 2;
	endy = var->ry;
	if (t == 5)
	{
		y = 0;
		endy = var->ry / 2;
	}
	while (y < endy)
	{
		init_fc_casting(var, y, t);
		x = 0;
		while (x < var->rx)
		{
			get_texel_color(var, &color, t);
			var->mlx.addr[(var->ry - y - 1) *
			var->mlx.line_length / 4 + x] = color;
			x++;
		}
		y++;
	}
}
