/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikhalil <mikhalil@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 23:09:16 by mikhalil      #+#    #+#                 */
/*   Updated: 2023/04/25 22:59:37 by mikhalil      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_rgb(char r, char g, char b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

double	absolut(double num)
{
	if (num > 0)
		return (num);
	else
		return (num * -1);
}

void	new_info(t_info *info, mlx_t *mlx, mlx_image_t *img, char id)
{
	info->mlx = mlx;
	info->image = img;
	info->width = (double)WIDTH;
	info->height = (double)HEIGHT;
	info->k = 1;
	info->xpos = (2.5 / 4) * WIDTH;
	info->xx = 0;
	info->yy = 2 * (info->height) / (info->width);
	info->fractal = id;
    info->iter = ITER;
	ft_bzero(info->arrows, 2);
	ft_bzero(info->colors, 3);
}
