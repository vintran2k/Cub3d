/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:15:11 by vintran           #+#    #+#             */
/*   Updated: 2021/03/12 16:18:16 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_str(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

int		get_line(char **line, char *file)
{
	char	*nextline;
	size_t	linelen;

	if ((nextline = ft_strchr(file, '\n')))
	{
		linelen = ft_strlen(file) - ft_strlen(nextline);
		*line = ft_substr(file, 0, linelen);
		ft_strcpy(file, nextline + 1);
		return (1);
	}
	return (0);
}

char	*strjoin_buf(char *file, char *buf)
{
	size_t	filelen;
	size_t	reslen;
	char	*res;

	filelen = 0;
	if (file)
		filelen = ft_strlen(file);
	reslen = filelen + ft_strlen(buf);
	if (!(res = malloc(reslen + 1)))
		return (NULL);
	if (file)
	{
		ft_strcpy(res, file);
		free_str(&file);
	}
	ft_strcpy(res + filelen, buf);
	return (res);
}

int		get_next_line(int fd, char **line, t_var *var)
{
	char		buf[BUFFER_SIZE + 1];
	int			ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if (var->file && get_line(line, var->file))
		return (1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!(var->file = strjoin_buf(var->file, buf)))
			return (-1);
		if (get_line(line, var->file))
			return (1);
	}
	if (var->file && *var->file)
		*line = ft_strdup(var->file);
	else
		*line = ft_strdup("");
	free_str(&var->file);
	return (ret);
}
