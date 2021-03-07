/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:48:35 by vintran           #+#    #+#             */
/*   Updated: 2021/03/07 17:45:10 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_texture(t_var *var)
{
	if (!(var->texture[0].img = mlx_xpm_file_to_image(var->mlx.mlx_ptr,
					var->no, &(var->texture[0].width),
					&(var->texture[0].height))))
		ft_error(var, "Impossible to get NO texture\n");
	if (!(var->texture[1].img = mlx_xpm_file_to_image(var->mlx.mlx_ptr,
					var->so, &(var->texture[1].width),
					&(var->texture[1].height))))
		ft_error(var, "Impossible to get SO texture\n");
	if (!(var->texture[2].img = mlx_xpm_file_to_image(var->mlx.mlx_ptr,
					var->we, &(var->texture[2].width),
					&(var->texture[2].height))))
		ft_error(var, "Impossible to get WE texture\n");
	if (!(var->texture[3].img = mlx_xpm_file_to_image(var->mlx.mlx_ptr,
					var->ea, &(var->texture[3].width),
					&(var->texture[3].height))))
		ft_error(var, "Impossible to get EA texture\n");
	if (!(var->texture[4].img = mlx_xpm_file_to_image(var->mlx.mlx_ptr,
					var->sp, &(var->texture[4].width),
					&(var->texture[4].height))))
		ft_error(var, "Impossible to get S texture\n");
}

void	get_texture_img(t_var *var)
{
	get_texture(var);
	var->texture[0].addr = (int *)mlx_get_data_addr(var->texture[0].img,
			&var->texture[0].bits_per_pixel,
			&var->texture[0].line_length, &var->texture[0].endian);
	var->texture[1].addr = (int *)mlx_get_data_addr(var->texture[1].img,
			&var->texture[1].bits_per_pixel,
			&var->texture[1].line_length, &var->texture[1].endian);
	var->texture[2].addr = (int *)mlx_get_data_addr(var->texture[2].img,
			&var->texture[2].bits_per_pixel,
			&var->texture[2].line_length, &var->texture[2].endian);
	var->texture[3].addr = (int *)mlx_get_data_addr(var->texture[3].img,
			&var->texture[3].bits_per_pixel,
			&var->texture[3].line_length, &var->texture[3].endian);
	var->texture[4].addr = (int *)mlx_get_data_addr(var->texture[4].img,
			&var->texture[4].bits_per_pixel,
			&var->texture[4].line_length, &var->texture[4].endian);
}

void	get_texture_dir(t_var *var)
{
	if (var->raycst.side == 0 && var->raycst.raydirx < 0)
		var->texel.dir = 0;
	if (var->raycst.side == 0 && var->raycst.raydirx >= 0)
		var->texel.dir = 1;
	if (var->raycst.side == 1 && var->raycst.raydiry < 0)
		var->texel.dir = 2;
	if (var->raycst.side == 1 && var->raycst.raydiry >= 0)
		var->texel.dir = 3;
}

void	get_texel_pos(t_var *var)
{
	get_texture_dir(var);
	if (var->raycst.side == 0)
		var->texel.wallx = var->raycst.posy + var->raycst.perpwalldist \
						* var->raycst.raydiry;
	else
		var->texel.wallx = var->raycst.posx + var->raycst.perpwalldist \
						* var->raycst.raydirx;
	var->texel.wallx -= floor((var->texel.wallx));
	var->texel.texx = (int)(var->texel.wallx * (double)var->texture[var->texel.dir].width);
	if (var->raycst.side == 0 && var->raycst.raydirx > 0)
		var->texel.texx = var->texture[var->texel.dir].width - var->texel.texx - 1;
	if (var->raycst.side == 1 && var->raycst.raydiry < 0)
		var->texel.texx = var->texture[var->texel.dir].width - var->texel.texx - 1;
	var->texel.step = 1.0 * var->texture[0].height / var->raycst.lineheight;
	var->texel.texpos = (var->raycst.drawstart - var->ry / 2 + var->raycst.lineheight / 2) * var->texel.step;
}

void	draw_wall(t_var *var, int x, int y)
{
	int	color;

	get_texel_pos(var);
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
