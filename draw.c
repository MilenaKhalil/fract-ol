/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikhalil <mikhalil@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 23:09:16 by mikhalil      #+#    #+#                 */
/*   Updated: 2023/05/02 19:58:08 by mikhalil      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	color_pixel(t_info *info, double x, double y, double mul)
{
	mlx_put_pixel(info->image, x, y, get_rgb(
			(int)(mul + (info->colors)[0]) % 0xFF,
			(int)(mul + (info->colors)[1]) % 0xFF,
			(int)(mul + (info->colors)[2]) % 0xFF));
}

double	lyap_calculate(t_info *info, double r[2], double *x0, double *x1)
{
	int		i;
	double	lia;

	i = 0;
	lia = 0;
	*x0 = 0.7;
	*x1 = 0;
	while (i < info->iter / 0.5)
	{
		if ((info->liap)[i % ft_strlen(info->liap)] == 'A')
		{
			if (*x0 != 0.5)
				lia += log(absolut(r[0] * (1 - (2 * (*x0)))));
			*x1 = r[0] * ((*x0) * (1 - (*x0)));
		}
		else
		{
			if (*x1 == 0)
				(*x1) = *x0;
			lia += log(absolut(r[1] * (1 - (2 * (*x1)))));
			*x0 = r[1] * (*x1) * (1 - (*x1));
		}
		i++;
	}
	return (lia / 10);
}

void	lyap(t_info *info, double k)
{
	double	r[2];
	double	x[2];
	double	lia;
	double	z;
	double	y;

	z = 0;
	while (z < info->width)
	{
		y = 0;
		while (y < info->height)
		{
			r[0] = (4 * (z - info->xpos) / info->width) / k
				+ (info->arrows)[0] - info->xx;
			r[1] = 4 - ((4 * (y - info->ypos)) / info->width / k
					+ (info->arrows)[1] - info->yy);
			lia = lyap_calculate(info, r, &x[0], &x[1]);
			color_pixel(info, z, y, lia);
			y++;
		}
		z++;
	}
}

void	draw_imag(t_complex z1, t_info *info, double x, double y)
{
	double		j;
	t_complex	z2;

	j = 0;
	if (info->fractal == 'M')
		z2 = z1;
	if (info->fractal == 'J')
	{
		z2.real = info->jr;
		z2.imag = info->ji;
	}
	while (j < info->iter)
	{
		z1 = count(z1, z2);
		if (!check(z1))
			break ;
		j++;
	}
	if (check(z1))
		mlx_put_pixel(info->image, x, y, get_rgb(0, 0, 0));
	else
		color_pixel(info, x, y, (sin(j / ITER * M_PI) * 0xFF));
}

void	image(double k, mlx_image_t *img, t_info *info)
{	
	t_complex	z1;
	double		x;
	double		y;

	if (info->fractal == 'L')
	{
		lyap(info, k);
		return ;
	}
	x = 0;
	while (x < img->width)
	{
		y = 0;
		while (y < img->height)
		{
			z1.real = (4 * (x - info->xpos) / (info->width)) / k
				+ (info->arrows)[0] - info->xx;
			z1.imag = 4 - ((4 * (y - info->ypos)) / info->width / k
					+ (info->arrows)[1] - info->yy);
			draw_imag(z1, info, x, y);
			y++;
		}
		x++;
	}
}
