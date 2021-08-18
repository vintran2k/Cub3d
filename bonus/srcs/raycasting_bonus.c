/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:33:00 by vintran           #+#    #+#             */
/*   Updated: 2021/03/25 01:40:58 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus.h"

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

void	draw_wall(t_var *var, int x)
{
	int	color;
	int y;

	var->raycst.drawend = var->ry - var->raycst.drawstart;
	get_texel_pos(var);
	y = var->raycst.drawstart + 1;
	while (y <= var->raycst.drawend)
	{
		var->texel.texy = (int)var->texel.texpos &
			(var->texture[var->texel.dir].height - 1);
		var->texel.texpos += var->texel.step;
		if (y < var->ry && x < var->rx)
		{
			color = var->texture[var->texel.dir].addr[var->texel.texy *
					var->texture[var->texel.dir].line_length /
						4 + var->texel.texx];
			var->mlx.addr[y * var->mlx.line_length / 4 + x] = color;
		}
		y++;
	}
}

void	draw_pixel_column(t_var *var, int x)
{
	int y;

	var->raycst.drawend = var->ry - var->raycst.drawstart;
	if (var->ct == NULL)
	{
		y = -1;
		while (++y <= var->raycst.drawstart)
			var->mlx.addr[y * var->mlx.line_length / 4 + x] = var->c;
	}
	draw_wall(var, x);
	if (var->ft == NULL)
	{
		y = var->raycst.drawend;
		while (++y < var->ry)
			var->mlx.addr[y * var->mlx.line_length / 4 + x] = var->f;
	}
}

int		raycasting(t_var *var)
{
	int	x;

	x = 0;
	if (var->ct)
		fc_casting(var, 6);
	if (var->ft)
		fc_casting(var, 5);
	while (x < var->rx)
	{
		init_raycasting(var, x);
		get_wall_pos(var);
		draw_pixel_column(var, x);
		var->sprite.zbuffer[x] = var->raycst.perpwalldist;
		x++;
	}
	put_sprite(var);
	print_minimap(var);
	if (var->save == 1)
		ft_save(var);
	mlx_put_image_to_window(var->mlx.mlx_ptr,
	var->mlx.mlx_win, var->mlx.img, 0, 0);
	move_rotate_player(var);
	return (0);
}
