/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:03:32 by vintran           #+#    #+#             */
/*   Updated: 2021/03/07 18:02:36 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_path_texture(t_var *var, char *line, char **path)
{
	int i;
	
	if (!ft_strchr(line, '.') || !ft_strchr(line, '/') || *path != NULL)
		ft_error(var, "Invalid path texture precision in .cub\n");
	if (line[0] == 'S' && (line[1] == ' ' || line[1] == '.'))
		line += 1;
	else
		line += 2;
	while (*line != '.')
	{
		if (*line != ' ')
			ft_error(var, "Invalid path texture precision in .cub\n");
		line++;
	}
	i = 0;
	while (line[i] > 32 && line[i] < 127)
		i++;
	if (line[i + through_space(&line[i])] != '\0')
			ft_error(var, "Invalid path texture precision in .cub\n");
	*path = ft_strndup(line, i);
}

int		check_resolution_line(char *line)
{
	line += through_space(line);
	if (!ft_isdigit(*line))
		return (0);
	if (!(line = ft_strchr(line, ' ')))
		return (0);
	line += through_space(line);
	if (!ft_isdigit(*line))
		return (0);
	while (ft_isdigit(*line))
		line++;
	line += through_space(line);
	if (*line != '\0')
		return (0);
	return (1);
}

void	get_resolution(t_var *var, char *line)
{
	int i;

	i = 0;
	if (line[1] == ' ')
		line += 2;
	else
		line += 1;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ' ')
			ft_error(var, "Invalid resolution precision in .cub\n");
		i++;
	}
	if (!check_resolution_line(line) || var->rx || var->ry)
		ft_error(var, "Invalid resolution precision in .cub\n");
	line += through_space(line);
	var->rx = ft_atoi(line);
	line = ft_strchr(line, ' ');
	line += through_space(line);
	var->ry = ft_atoi(line);
	if (var->rx < 1 || var->ry < 1)
		ft_error(var, "Invalid resolution precision in .cub\n");
}

int		check_color_line(char *line)
{
	int i;

	i = -1;
	while (line[++i])
		if (line[i] != ' ' && line[i] != ',' && !ft_isdigit(line[i]))
			return (0);
	line += through_space(line);
	if (!ft_isdigit(*line))
		return (0);
	if (!(line = ft_strchr(line, ',')))
		return (0);
	line++;
	line += through_space(line);
	if (!ft_isdigit(*line))
		return (0);
	if (!(line = ft_strchr(line, ',')))
		return (0);
	line++;
	line += through_space(line);
	if (!ft_isdigit(*line))
		return (0);
	return (1);
}

void	get_rgb(t_var *var, char *line, int *color)
{
	int r;
	int g;
	int b;

	if (line[1] == ' ')
		line += 2;
	else
		line += 1;
	if (!check_color_line(line) || *color != -1)
		ft_error(var, "Invalid RGB precision in .cub\n");
	r = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	g = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	line += through_space(line);
	b = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	line += through_space(line);
	if (*line != '\0')
		ft_error(var, "Invalid RGB precision in .cub\n");
	if (r > 255 || g > 255 || b > 255)
		ft_error(var, "Invalid RGB value in .cub\n");
	*color = r << 16 | g << 8 | b;
}
