/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:08:30 by vintran           #+#    #+#             */
/*   Updated: 2021/03/25 01:40:33 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus.h"

void	draw_x_outline(t_var *var, int x, int y)
{
	var->mlx.addr[y * var->mlx.line_length / 4 + x] = var->mc.color[1];
	var->mlx.addr[y * var->mlx.line_length / 4 + x + 1] = var->mc.color[1];
	var->mlx.addr[y * var->mlx.line_length / 4 + (var->mc.rx - 1)] =
	var->mc.color[1];
	var->mlx.addr[y * var->mlx.line_length / 4 + var->mc.rx] = var->mc.color[1];
}

void	draw_outline(t_var *var)
{
	int x;
	int y;

	y = var->mc.edge;
	while (y <= var->mc.ry)
	{
		x = var->mc.edge;
		if (y == var->mc.edge || y == var->mc.edge + 1 ||
				y == var->mc.ry - 1 || y == var->mc.ry)
		{
			while (x <= var->mc.rx)
			{
				var->mlx.addr[y * var->mlx.line_length / 4 + x] =
				var->mc.color[1];
				x++;
			}
		}
		else
			draw_x_outline(var, x, y);
		y++;
	}
}

void	draw_case(t_var *var, int x, int y, int v)
{
	var->mc.drawstarty = (y + 1) * var->mc.case_s + var->mc.edge;
	var->mc.drawendy = var->mc.drawstarty + var->mc.case_s;
	while (var->mc.drawstarty < var->mc.drawendy)
	{
		var->mc.drawstartx = (x + 1) * var->mc.case_s + var->mc.edge;
		var->mc.drawendx = var->mc.drawstartx + var->mc.case_s;
		while (var->mc.drawstartx < var->mc.drawendx)
		{
			if (v == 1)
				var->mlx.addr[var->mc.drawstarty * var->mlx.line_length /
				4 + var->mc.drawstartx] = var->mc.color[v];
			else
				var->mlx.addr[var->mc.drawstarty * var->mlx.line_length / 4 +
				var->mc.drawstartx] =
				var->mlx.addr[var->mc.drawstarty * var->mlx.line_length / 4 +
				var->mc.drawstartx] + var->mc.color[v];
			if (x == (int)var->raycst.posy && y == (int)var->raycst.posx)
				var->mlx.addr[var->mc.drawstarty * var->mlx.line_length / 4 +
				var->mc.drawstartx] = 16711680;
			var->mc.drawstartx++;
		}
		var->mc.drawstarty++;
	}
}

void	print_minimap(t_var *var)
{
	int x;
	int y;

	if (!var->minimapkey)
		return ;
	y = -1;
	while (y < var->map_lines + 1)
	{
		x = -1;
		while (x < var->l_line + 1)
		{
			if (x >= 0 && x < var->l_line && y >= 0 &&
			y < var->map_lines && var->map[y][x] == '1')
				draw_case(var, x, y, 1);
			else if (x >= 0 && x < var->l_line && y >= 0 &&
			y < var->map_lines && var->map[y][x] == '2')
				draw_case(var, x, y, 2);
			else
				draw_case(var, x, y, 0);
			x++;
		}
		y++;
	}
	draw_outline(var);
}
