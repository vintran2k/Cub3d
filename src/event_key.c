/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 16:49:36 by vintran           #+#    #+#             */
/*   Updated: 2021/03/07 17:18:32 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		key_press(int keycode, t_var *var)
{
	if (keycode == ESC)
		ft_exit_cub(var);
	else if (keycode == FORWARD_W)
		var->move.forward = 1;
	else if (keycode == BACK_S)
		var->move.back = 1;
	else if (keycode == LEFT_A)
		var->move.left = 1;
	else if (keycode == RIGHT_D)
		var->move.right = 1;
	else if (keycode == ROTATE_L)
		var->move.rotate_left = 1;
	else if (keycode == ROTATE_R)
		var->move.rotate_right = 1;
	return (0);
}

int		key_release(int keycode, t_var *var)
{
	if (keycode == FORWARD_W)
		var->move.forward = 0;
	else if (keycode == BACK_S)
		var->move.back = 0;
	else if (keycode == LEFT_A)
		var->move.left = 0;
	else if (keycode == RIGHT_D)
		var->move.right = 0;
	else if (keycode == ROTATE_L)
		var->move.rotate_left = 0;
	else if (keycode == ROTATE_R)
		var->move.rotate_right = 0;
	return (0);
}
