/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:45:05 by vintran           #+#    #+#             */
/*   Updated: 2021/03/12 16:00:08 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	malloc_map(t_var *var)
{
	int i;

	var->map = malloc(sizeof(char *) * var->map_lines);
	if (!var->map)
		ft_error(var, "map malloc failled\n");
	i = 0;
	while (i < var->map_lines)
	{
		var->map[i] = malloc(var->l_line + 1);
		if (!var->map[i])
			ft_error(var, "map malloc failled\n");
		i++;
	}
	var->map[0][0] = '\0';
}

void	get_map_line(char *line, t_var *var)
{
	static int	i;
	int			j;

	j = 0;
	while (line[j])
	{
		var->map[i][j] = line[j];
		j++;
	}
	while (j < var->l_line)
	{
		var->map[i][j] = ' ';
		j++;
	}
	var->map[i][j] = '\0';
	i++;
}

void	get_map(char *file, t_var *var)
{
	int		i;
	int		fd;
	int		ret;
	char	*line;

	malloc_map(var);
	i = 1;
	fd = open(file, O_RDONLY);
	while (i < var->map_beg)
	{
		get_next_line(fd, &line, var);
		free(line);
		i++;
	}
	i = 0;
	ret = 1;
	while (ret != 0 && ret != -1)
	{
		ret = get_next_line(fd, &line, var);
		if (i < var->map_lines && (!is_empty(line) ||
		(is_empty(line) && var->map[0][0])))
			get_map_line(line, var);
		free(line);
		i++;
	}
	close(fd);
}
