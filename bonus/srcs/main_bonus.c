/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:28:11 by vintran           #+#    #+#             */
/*   Updated: 2021/03/25 01:40:29 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus.h"

void	ft_cub3d(t_var *var)
{
	if (!(var->mlx.mlx_ptr = mlx_init()))
		ft_error(var, "mlx_init() failled\n");
	mlx_get_screen_size(var->mlx.mlx_ptr, &var->screenx, &var->screeny);
	if (var->screenx < var->rx)
		var->rx = var->screenx;
	if (var->screeny < var->ry)
		var->ry = var->screeny;
	get_texture_img(var);
	var->mlx.img = mlx_new_image(var->mlx.mlx_ptr, var->rx, var->ry);
	var->mlx.addr = (int *)mlx_get_data_addr(var->mlx.img,
	&var->mlx.bits_per_pixel, &var->mlx.line_length, &var->mlx.endian);
	if (var->save == 1)
		raycasting(var);
	var->mlx.mlx_win =
		mlx_new_window(var->mlx.mlx_ptr, var->rx, var->ry, "cub3d");
	mlx_hook(var->mlx.mlx_win, 33, 1L << 17, ft_exit_cub, var);
	mlx_hook(var->mlx.mlx_win, 02, 1L << 0, key_press, var);
	mlx_hook(var->mlx.mlx_win, 03, 1L << 1, key_release, var);
	mlx_loop_hook(var->mlx.mlx_ptr, raycasting, var);
	mlx_loop(var->mlx.mlx_ptr);
}

int		main(int argc, char **argv)
{
	t_var var;

	parsing(argc, argv, &var);
	init_raycst(&var);
	init_sprite(&var);
	init_minimap(&var);
	ft_cub3d(&var);
	return (0);
}
