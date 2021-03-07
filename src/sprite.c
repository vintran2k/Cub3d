/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:47:15 by vintran           #+#    #+#             */
/*   Updated: 2021/03/03 15:22:46 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_sprite_dist(t_var *var)
{
	int i;

	i = 0;
	while (i < var->sprite.nb)
	{
		var->sprite.order[i] = i;
		var->sprite.dist[i] = ((var->raycst.posx - var->sprite.pos[i].x)
				* (var->raycst.posx - var->sprite.pos[i].x)
				+ (var->raycst.posy - var->sprite.pos[i].y)
				* (var->raycst.posy - var->sprite.pos[i].y));
		i++;
	}
}

void	sort_sprite(t_var *var)
{
	int i;
	double temp;
	
	get_sprite_dist(var);
	i = 0;
	while (i < var->sprite.nb - 1)
	{
		if (var->sprite.dist[i] < var->sprite.dist[i + 1])
		{
			temp = var->sprite.dist[i];
			var->sprite.dist[i] = var->sprite.dist[i + 1];
			var->sprite.dist[i + 1] = temp;
			temp = var->sprite.order[i];
			var->sprite.order[i] = var->sprite.order[i + 1];
			var->sprite.order[i + 1] = temp;
			i = -1;
		}
		i++;
	}
}

void	get_draw_startend(t_sprite *sp, t_raycst ray, int rx, int ry, int i)
{
	sp->spritex = sp->pos[sp->order[i]].x - ray.posx;
	sp->spritey = sp->pos[sp->order[i]].y - ray.posy;
	sp->invdet = 1.0 / (ray.planex * ray.diry - ray.dirx * ray.planey);
	sp->transformx = sp->invdet * (ray.diry * sp->spritex - ray.dirx * sp->spritey);
	sp->transformy = sp->invdet * (-ray.planey * sp->spritex + ray.planex * sp->spritey);
	sp->spritescreenx = (int)(rx / 2) * (1 + sp->transformx / sp->transformy);
	sp->spriteheight = abs((int)(ry / (sp->transformy)));
	sp->drawstarty = -sp->spriteheight / 2 + ry / 2;
	if (sp->drawstarty < 0)
		sp->drawstarty = 0;
	sp->drawendy = sp->spriteheight / 2 + ry / 2;
	if (sp->drawendy >= ry)
		sp->drawendy = ry - 1;
	sp->spritewidth = abs((int)(ry / (sp->transformy)));
	sp->drawstartx = -sp->spritewidth / 2 + sp->spritescreenx;
	if (sp->drawstartx < 0)
		sp->drawstartx = 0;
	sp->drawendx = sp->spritewidth / 2 + sp->spritescreenx;
	if (sp->drawendx >= rx)
		sp->drawendx = rx - 1;
	sp->stripe = sp->drawstartx;
}

void	draw_sprite(t_var *var)
{
	int y;
	int d;
	int color;

	y = var->sprite.drawstarty;
	while (y < var->sprite.drawendy)
	{
		d = (y) * 256 - var->ry * 128 + var->sprite.spriteheight * 128;
		var->sprite.texy = ((d * var->texture[4].height)
			/ var->sprite.spriteheight) / 256;
		color = var->texture[4].addr[var->sprite.texy *
			var->texture[4].line_length / 4 + var->sprite.texx];
		if ((color & 0x00FFFFFF) != 0)
			var->mlx.addr[y * var->mlx.line_length / 4 + var->sprite.stripe] = color;
		y++;
	}	
}

void	put_sprite(t_var *var)
{
	int i;

	sort_sprite(var);
	i = 0;
	while (i < var->sprite.nb)
	{
		get_draw_startend(&var->sprite, var->raycst, var->rx, var->ry, i);
		while (var->sprite.stripe < var->sprite.drawendx)
		{
			var->sprite.texx = (int)(256 * (var->sprite.stripe - (-var->sprite.spritewidth / 2
				+ var->sprite.spritescreenx)) * var->texture[4].width
				/ var->sprite.spritewidth) / 256;
			if (var->sprite.transformy > 0 && var->sprite.stripe >= 0
					&& var->sprite.stripe < var->rx &&
					var->sprite.transformy < var->sprite.zbuffer[var->sprite.stripe])
				draw_sprite(var);
			var->sprite.stripe++;
		}
		i++;
	}
}