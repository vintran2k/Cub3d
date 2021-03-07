/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:55:59 by vintran           #+#    #+#             */
/*   Updated: 2021/03/07 18:11:17 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		check_map_char(t_var *var)
{
	int y;
	int x;

	x = 0;
	while (x < var->map_lines)
	{
		y = 0;
		while (y < var->l_line)
		{
			if (var->map[x][y] != '0' && var->map[x][y] != '1' &&
			var->map[x][y] != '2' && var->map[x][y] != ' ' && var->map[x][y] != 'N' &&
			var->map[x][y] != 'S' && var->map[x][y] != 'E' && var->map[x][y] != 'W')
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

void	get_player_pos(t_var *var)
{
	int x;
	int y;

	x = 0;
	while (x < var->map_lines)
	{
		y = 0;
		while (var->map[x][y])
		{
			if (var->map[x][y] == 'N' || var->map[x][y] == 'S'
			|| var->map[x][y] == 'E' || var->map[x][y] == 'W')
			{
				if (var->player_x != -1)
					ft_error(var, "Many player in the map\n");
				var->player_x = x;
				var->player_y = y;
				var->player_dir = var->map[x][y];
				var->map[x][y] = '0';
			}
			y++;
		}
		x++;
	}
	if (var->player_x == -1)
		ft_error(var, "No player in the map\n");
}

int		check_arround(t_var *var, int x, int y)
{
	if (y == 0 || y == var->l_line || x == 0 || x == var->map_lines)
		return (0);
	if (var->map[x][y - 1] != '0' && var->map[x][y - 1] != '1' && var->map[x][y - 1] != '2')
		return (0);
	if (var->map[x][y + 1] != '0' && var->map[x][y + 1] != '1' && var->map[x][y + 1] != '2')
		return (0);
	if (var->map[x - 1][y] != '0' && var->map[x - 1][y] != '1' && var->map[x - 1][y] != '2')
		return (0);
	if (var->map[x + 1][y] != '0' && var->map[x + 1][y] != '1' && var->map[x + 1][y] != '2')
		return (0);
	return (1);
}

void	parsing_map(t_var *var)
{
	int x;
	int y;

	if (!check_map_char(var))
		ft_error(var, "Invalid precision in the map\n");
	get_player_pos(var);
	x = 0;
	while (x < var->map_lines)
	{
		y = 0;
		while (var->map[x][y])
		{
			if (var->map[x][y] == '2')
				var->sprite.nb++;
			if (var->map[x][y] == '0' || var->map[x][y] == '2')
				if (!check_arround(var, x, y))
					ft_error(var, "The map is not closed\n");
			y++;
		}
		x++;
	}
}
