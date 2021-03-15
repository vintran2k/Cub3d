/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:55:59 by vintran           #+#    #+#             */
/*   Updated: 2021/03/15 14:40:54 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		check_map_char(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' &&
		line[i] != '2' && line[i] != ' ' && line[i] != 'N' &&
		line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
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
	if (y == 0 || y == var->l_line || x == 0 || x == var->map_lines -1)
		return (0);
	if (var->map[x][y - 1] != '0'
	&& var->map[x][y - 1] != '1' && var->map[x][y - 1] != '2')
		return (0);
	if (var->map[x][y + 1] != '0'
	&& var->map[x][y + 1] != '1' && var->map[x][y + 1] != '2')
		return (0);
	if (var->map[x - 1][y] != '0'
	&& var->map[x - 1][y] != '1' && var->map[x - 1][y] != '2')
		return (0);
	if (var->map[x + 1][y] != '0'
	&& var->map[x + 1][y] != '1' && var->map[x + 1][y] != '2')
		return (0);
	return (1);
}

void	parsing_map(t_var *var)
{
	int x;
	int y;

	get_player_pos(var);
	x = 0;
	while (x < var->map_lines)
	{
		if (!check_map_char(var->map[x]))
			ft_error(var, "Invalid character in the map\n");
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
