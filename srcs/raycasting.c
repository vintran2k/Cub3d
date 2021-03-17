/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:33:00 by vintran           #+#    #+#             */
/*   Updated: 2021/03/08 16:44:19 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_wall_dist(t_var *var)
{
	while (var->raycst.hit == 0)
	{
		if (var->raycst.sidedistx < var->raycst.sidedisty)
		{
			var->raycst.sidedistx += var->raycst.deltadistx;
			var->raycst.mapx += var->raycst.stepx;
			var->raycst.side = 0;
		}
		else
		{
			var->raycst.sidedisty += var->raycst.deltadisty;
			var->raycst.mapy += var->raycst.stepy;
			var->raycst.side = 1;
		}
		if (var->map[var->raycst.mapx][var->raycst.mapy] == '1')
			var->raycst.hit = 1;
	}
	if (var->raycst.side == 0)
		var->raycst.perpwalldist = ((double)var->raycst.mapx - var->raycst.posx
		+ (1 - (double)var->raycst.stepx) / 2) / var->raycst.raydirx;
	else
		var->raycst.perpwalldist = ((double)var->raycst.mapy - var->raycst.posy
		+ (1 - (double)var->raycst.stepy) / 2) / var->raycst.raydiry;
}

void	get_wall_pos(t_var *var)
{
	get_wall_dist(var);
	var->raycst.lineheight = (int)(var->ry / var->raycst.perpwalldist);
	var->raycst.drawstart = -var->raycst.lineheight / 2 + var->ry / 2;
	if (var->raycst.drawstart < 0)
		var->raycst.drawstart = 0;
	var->raycst.drawend = var->raycst.lineheight / 2 + var->ry / 2;
	if (var->raycst.drawend >= var->ry)
		var->raycst.drawend = var->ry - 1;
}

void	draw_pixel_column(t_var *var, int x)
{
	int y;

	y = -1;
	var->raycst.drawend = var->ry - var->raycst.drawstart;
	while (++y <= var->raycst.drawstart)
		var->mlx.addr[y * var->mlx.line_length / 4 + x] = var->c;
	if (y <= var->raycst.drawend)
		draw_wall(var, x, y);
	y = var->raycst.drawend;
	while (++y < var->ry)
		var->mlx.addr[y * var->mlx.line_length / 4 + x] = var->f;
}

int		raycasting(t_var *var)
{
	int	x;

	x = 0;
	while (x < var->rx)
	{
		init_raycasting(var, x);
		get_wall_pos(var);
		draw_pixel_column(var, x);
		var->sprite.zbuffer[x] = var->raycst.perpwalldist;
		x++;
	}
	put_sprite(var);
	if (var->save == 1)
		ft_save(var);
	mlx_put_image_to_window(var->mlx.mlx_ptr,
	var->mlx.mlx_win, var->mlx.img, 0, 0);
	move_rotate_player(var);
	return (0);
}
