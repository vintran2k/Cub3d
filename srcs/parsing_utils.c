/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:53:31 by vintran           #+#    #+#             */
/*   Updated: 2021/02/25 16:22:06 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int		ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int		is_empty(char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

int		is_longest(char *line, int prev)
{
	int len;

	len = 0;
	while (*line)
	{
		if (!is_empty(line))
			len++;
		line++;
	}
	if (prev < len)
		prev = len;
	return (prev);
}

int		through_space(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}
