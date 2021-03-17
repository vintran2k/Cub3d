/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:32:50 by vintran           #+#    #+#             */
/*   Updated: 2021/03/15 18:50:03 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_map(t_var *var)
{
	int i;

	if (var->map)
	{
		i = -1;
		while (++i < var->map_lines)
			free(var->map[i]);
		free(var->map);
	}
}

void	mlx_destroy(t_var *var)
{
	if (var->mlx.img)
		mlx_destroy_image(var->mlx.mlx_ptr, var->mlx.img);
	if (var->texture[0].img)
		mlx_destroy_image(var->mlx.mlx_ptr, var->texture[0].img);
	if (var->texture[1].img)
		mlx_destroy_image(var->mlx.mlx_ptr, var->texture[1].img);
	if (var->texture[2].img)
		mlx_destroy_image(var->mlx.mlx_ptr, var->texture[2].img);
	if (var->texture[3].img)
		mlx_destroy_image(var->mlx.mlx_ptr, var->texture[3].img);
	if (var->texture[4].img)
		mlx_destroy_image(var->mlx.mlx_ptr, var->texture[4].img);
	if (var->mlx.mlx_win)
		mlx_destroy_window(var->mlx.mlx_ptr, var->mlx.mlx_win);
	if (var->mlx.mlx_ptr)
	{
		mlx_destroy_display(var->mlx.mlx_ptr);
		free(var->mlx.mlx_ptr);
	}
}

int		ft_exit_cub(t_var *var)
{
	free_map(var);
	free(var->line);
	if (var->file)
		free(var->file);
	if (var->no)
		free(var->no);
	if (var->so)
		free(var->so);
	if (var->we)
		free(var->we);
	if (var->ea)
		free(var->ea);
	if (var->sp)
		free(var->sp);
	if (var->sprite.zbuffer)
		free(var->sprite.zbuffer);
	if (var->sprite.pos)
		free(var->sprite.pos);
	if (var->sprite.order)
		free(var->sprite.order);
	if (var->sprite.dist)
		free(var->sprite.dist);
	mlx_destroy(var);
	exit(0);
}

void	ft_error(t_var *var, char *error_msg)
{
	ft_putstr("Error\n");
	ft_putstr(error_msg);
	ft_exit_cub(var);
}
