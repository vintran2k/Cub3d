/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:53:02 by vintran           #+#    #+#             */
/*   Updated: 2021/03/08 16:22:46 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	bmp_header(t_var *var, int fd)
{
	int temp;

	write(fd, "BM", 2);
	temp = 14 + 40 + 4 * var->rx * var->ry;
	write(fd, &temp, 4);
	temp = 0;
	write(fd, &temp, 2);
	write(fd, &temp, 2);
	temp = 54;
	write(fd, &temp, 4);
	temp = 40;
	write(fd, &temp, 4);
	write(fd, &var->rx, 4);
	write(fd, &var->ry, 4);
	temp = 1;
	write(fd, &temp, 2);
	write(fd, &var->mlx.bits_per_pixel, 2);
	temp = 0;
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
}

void	ft_save(t_var *var)
{
	int fd;
	int x;
	int y;

	fd = -1;
	while (fd == -1)
		fd = open("./save.bmp", O_RDWR | O_CREAT);
	bmp_header(var, fd);
	y = var->ry;
	while (y >= 0)
	{
		x = 0;
		while (x < var->rx)
		{
			write(fd, &var->mlx.addr[y * var->mlx.line_length / 4 + x], 4);
			x++;
		}
		y--;
	}
	system("chmod 777 save.bmp");
	ft_exit_cub(var);
}
