/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   param.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikhalil <mikhalil@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 23:09:16 by mikhalil      #+#    #+#                 */
/*   Updated: 2023/04/25 22:57:48 by mikhalil      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	colors_check(t_info *info)
{
	if (mlx_is_key_down(info->mlx, MLX_KEY_R)
		|| mlx_is_key_down(info->mlx, MLX_KEY_G)
		|| mlx_is_key_down(info->mlx, MLX_KEY_B))
	{
		if (mlx_is_key_down(info->mlx, MLX_KEY_R))
			(info->colors)[0] = ((info->colors)[0] + 3) % 0xFF;
		if (mlx_is_key_down(info->mlx, MLX_KEY_G))
			(info->colors)[1] = ((info->colors)[1] + 3) % 0xFF;
		if (mlx_is_key_down(info->mlx, MLX_KEY_B))
			(info->colors)[2] = ((info->colors)[2] + 3) % 0xFF;
		image(info->k, info->image, info);
	}
}

void	arrows_check(t_info *info)
{
	double	kk;

	kk = info->k * 2;
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(info->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(info->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(info->mlx, MLX_KEY_DOWN))
	{
		if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
			(info->arrows)[0] -= 1 / kk;
		if (mlx_is_key_down(info->mlx, MLX_KEY_UP))
			(info->arrows)[1] -= 1 / kk;
		if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
			(info->arrows)[0] += 1 / kk;
		if (mlx_is_key_down(info->mlx, MLX_KEY_DOWN))
			(info->arrows)[1] += 1 / kk;
		image(info->k, info->image, info);
	}
}

void	scroll_pos(double xdelta, double ydelta, void *info)
{
	t_info	*inf;

	(void) xdelta;
	inf = (t_info *)info;
	if (ydelta > 0)
	{
		inf->k *= 1.3;
		image(inf->k, inf->image, inf);
	}
	else if (ydelta < 0)
	{
		inf->k /= 1.3;
		image(inf->k, inf->image, inf);
	}
}

void	mouse_pos(double xpos, double ypos, void *info)
{
	t_info	*inf;

	inf = (t_info *)info;
	if ((xpos != inf->xpos) || (ypos != inf->ypos))
	{
		inf->xx += 4 * (inf->xpos - xpos) / inf->k / inf->width;
		inf->yy += (4 * (inf->ypos - ypos) / inf->k / inf->width)
			* (inf->height / inf->width);
		inf->xpos = xpos;
		inf->ypos = ypos;
		if (inf->fractal == 'J')
			image(inf->k, inf->image, inf);
	}
}
