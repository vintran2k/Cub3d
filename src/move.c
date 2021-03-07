/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:56:22 by vintran           #+#    #+#             */
/*   Updated: 2021/02/28 16:25:49 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_forward_back(t_var *var)
{
	if (var->move.forward == 1)
	{
		if (var->map[(int)(var->raycst.posx + (var->raycst.dirx * var->move.movespeed * 2))][(int)var->raycst.posy] == '0')
			var->raycst.posx += var->raycst.dirx * var->move.movespeed;
		if (var->map[(int)(var->raycst.posx)][(int)(var->raycst.posy + (var->raycst.diry * var->move.movespeed * 2))] == '0')
			var->raycst.posy += var->raycst.diry * var->move.movespeed;
	}
	if (var->move.back == 1)
	{
		if (var->map[(int)(var->raycst.posx - (var->raycst.dirx * var->move.movespeed * 2))][(int)(var->raycst.posy)] == '0')
			var->raycst.posx -= var->raycst.dirx * var->move.movespeed;
		if (var->map[(int)(var->raycst.posx)][(int)(var->raycst.posy -
					(var->raycst.diry * var->move.movespeed * 2))] == '0')
			var->raycst.posy -= var->raycst.diry * var->move.movespeed;
	}
}

void	move_left_right(t_var *var)
{
 	if (var->move.right == 1)
	{
		if (var->map[(int)(var->raycst.posx + var->raycst.diry * (var->move.movespeed * 2))][(int)var->raycst.posy] == '0')
			var->raycst.posx += var->raycst.diry * var->move.movespeed;
		if (var->map[(int)var->raycst.posx][(int)(var->raycst.posy - var->raycst.dirx * (var->move.movespeed * 2))] == '0')
			var->raycst.posy -= var->raycst.dirx * var->move.movespeed;
	}
	if (var->move.left == 1)
	{
		if (var->map[(int)(var->raycst.posx - var->raycst.diry * (var->move.movespeed * 2))][(int)var->raycst.posy] == '0')
			var->raycst.posx -= var->raycst.diry * var->move.movespeed;
		if (var->map[(int)var->raycst.posx][(int)(var->raycst.posy + var->raycst.dirx * (var->move.movespeed * 2))] == '0')
			var->raycst.posy += var->raycst.dirx * var->move.movespeed;
	}
}

void	rotate_left(t_var *var)
{
	double olddirx;
	double oldplanex;

	olddirx = var->raycst.dirx;
	var->raycst.dirx = var->raycst.dirx * cos(var->move.rotspeed / 2) -
		var->raycst.diry * sin(var->move.rotspeed / 2);
	var->raycst.diry = olddirx * sin(var->move.rotspeed / 2) + var->raycst.diry * cos(var->move.rotspeed / 2);
	oldplanex = var->raycst.planex;
	var->raycst.planex = var->raycst.planex * cos(var->move.rotspeed / 2) -
		var->raycst.planey * sin(var->move.rotspeed / 2);
	var->raycst.planey = oldplanex * sin(var->move.rotspeed / 2) +
		var->raycst.planey * cos(var->move.rotspeed / 2);

}

void	rotate_right(t_var *var)
{
	double olddirx;
	double oldplanex;

	olddirx = var->raycst.dirx;
	var->raycst.dirx = var->raycst.dirx * cos(-var->move.rotspeed / 2) -
		var->raycst.diry * sin(-var->move.rotspeed / 2);
	var->raycst.diry = olddirx * sin(-var->move.rotspeed / 2) +
		var->raycst.diry * cos(-var->move.rotspeed / 2);
	oldplanex = var->raycst.planex;
	var->raycst.planex = var->raycst.planex * cos(-var->move.rotspeed / 2)
		- var->raycst.planey * sin(-var->move.rotspeed / 2);
	var->raycst.planey = oldplanex * sin(-var->move.rotspeed / 2) +
		var->raycst.planey * cos(-var->move.rotspeed / 2);
}

void	move_rotate_player(t_var *var)
{
	move_forward_back(var);
	move_left_right(var);
	if (var->move.rotate_left == 1)
		rotate_left(var);
	if (var->move.rotate_right == 1)
		rotate_right(var);
}