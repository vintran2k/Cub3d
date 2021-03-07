/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:28:36 by vintran           #+#    #+#             */
/*   Updated: 2021/03/07 18:30:12 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_delta(double *deltax, double *deltay, double raycstdirx, double raycstdiry)
{
	if (raycstdiry == 0)
		*deltax = 0;
	else if (raycstdirx == 0)
		*deltax = 1;
	else
		*deltax = sqrt(1 + (raycstdiry * raycstdiry) / (raycstdirx * raycstdirx));
	if (raycstdirx == 0)
		*deltay = 0;
	else if (raycstdiry == 0)
		*deltay = 1;
	else
		*deltay = sqrt(1 + (raycstdirx * raycstdirx) / (raycstdiry * raycstdiry));
}

void	init_step_sidedist(t_var *var)
{
	if (var->raycst.raydirx < 0)
	{
		var->raycst.stepx = -1;
		var->raycst.sidedistx = (var->raycst.posx - var->raycst.mapx) * var->raycst.deltadistx;   
	}
	else
	{
		var->raycst.stepx = 1;
		var->raycst.sidedistx = (var->raycst.mapx + 1.0 - var->raycst.posx) * var->raycst.deltadistx;
	}
	if (var->raycst.raydiry < 0)
	{
		var->raycst.stepy = -1;
		var->raycst.sidedisty = (var->raycst.posy - var->raycst.mapy) * var->raycst.deltadisty;
	}
	else
	{
		var->raycst.stepy = 1;
		var->raycst.sidedisty = (var->raycst.mapy + 1.0 - var->raycst.posy) * var->raycst.deltadisty;
	}
}

void	init_raycasting(t_var *var, int x)
{
	var->raycst.camerax = 2 * x / (double)var->rx - 1;
	var->raycst.raydirx = var->raycst.dirx + var->raycst.planex * var->raycst.camerax;
	var->raycst.raydiry = var->raycst.diry + var->raycst.planey * var->raycst.camerax;

	var->raycst.mapx = (int)var->raycst.posx;
	var->raycst.mapy = (int)var->raycst.posy;

	var->raycst.hit = 0;
	init_delta(&var->raycst.deltadistx, &var->raycst.deltadisty, var->raycst.raydirx, var->raycst.raydiry);
	init_step_sidedist(var);
}

void	get_sprite_pos(t_var *var)
{
	int x;
	int y;
	int i;

	i = 0;
	x = 0;
	while (x < var->map_lines)
	{
		y = 0;
		while (y < var->l_line)
		{
			if (var->map[x][y] == '2')
			{
				var->sprite.pos[i].x = (double)x + 0.5;
				var->sprite.pos[i].y = (double)y + 0.5;
				i++;
			}
			y++;
		}
		x++;
	}
}

void	init_sprite(t_var *var)
{
	if (!(var->sprite.zbuffer = malloc(sizeof(double) * var->rx)))
		ft_error(var, "sprite.zbuffer malloc failed\n");
	if (!(var->sprite.pos = malloc(sizeof(t_pos) * var->sprite.nb)))
		ft_error(var, "sprite.pos malloc failed\n");
	if (!(var->sprite.order = malloc(sizeof(int) * var->sprite.nb)))
		ft_error(var, "sprite.order malloc failed\n");
	if (!(var->sprite.dist = malloc(sizeof(double) * var->sprite.nb)))
		ft_error(var, "sprite.dist malloc failed\n");
	get_sprite_pos(var);
}
