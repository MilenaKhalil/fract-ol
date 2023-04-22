/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikhalil <mikhalil@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 23:09:01 by mikhalil      #+#    #+#                 */
/*   Updated: 2023/04/22 23:36:16 by mikhalil      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	image(double k, mlx_image_t *img, t_info *info)
{	
	t_complex	z1;
	t_complex	z2;
	char		col_iter;

	for (double x = 0; x < img->width; x++)
	{
		for(double y = 0; y < img->height; y++)
		{
			double t = 0;
			z1.real = (4 * x / ((double)img->width) - 2.5) / k + (info->arrows)[0];
			z1.imag = (4 / ((double)img->width) * y - 2 * ((double)img->height) / ((double)img->width)) / k + (info->arrows)[1];
			z2 = z1;
			for (int j = 0; j < ITER; j++)
			{
				t = j;
				z1 = count(z1, z2);
				if (!check(z1))
					break;
			}
			if (check(z1))
				mlx_put_pixel(img, x, y, get_rgb(0, 0, 0));
			else
			{
				col_iter = (int)(sin(t / ITER * M_PI) * 0xFF);
				//t = (int)(t + (info->colors)[0]) % 0xFF;
				mlx_put_pixel(img, x, y, get_rgb((int)(col_iter + (info->colors)[0]) % 150, (int)(col_iter + (info->colors)[1]) % 150, 
				(int)(col_iter + (info->colors)[2]) % 150));//get_rgb(col_iter / 2 + (info->colors)[0], 0xFF - (int)(col_iter / ((sin(t) + 1)))
				 //+ (info->colors)[1], col_iter + (info->colors)[2]));
			}
			if (z1.real == 0 && z1.imag == 0)
				mlx_put_pixel(img, x, y, get_rgb(0xFF, 0xFF, 0xFF));
		}
	}
}

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
    double kk;

    kk = info->k;
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

void	hook(void *param)
{
	t_info	*info;

	info = (t_info *)param;
	arrows_check(info);
	colors_check(info);
	if (info->width != info->mlx->width || info->height != info->mlx->height)
	{
		info->width = info->mlx->width;
		info->height = info->mlx->height;
		mlx_resize_image(info->image, info->width, info->height);
		image(info->k, info->image, info);
	}
}

void	func(double xdelta, double ydelta, void *info)
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

void	func_m(double xpos, double ypos, void *info)
{
	t_info	*inf;

	inf = (t_info *)info;
	if ((xpos != inf->xpos) || (ypos != inf->ypos))
	{
		inf->xpos = xpos;
		inf->ypos = ypos;
	}
}

void	new_info(t_info *info, mlx_t *mlx, mlx_image_t *img)
{
	info->mlx = mlx;
	info->image = img;
	info->width = WIDTH;
	info->height = HEIGHT;
	info->k = 1;
	ft_bzero(info->arrows, 2);
	ft_bzero(info->colors, 3);
}

int32_t	main(void)
{
	mlx_t		*mlx;
	t_info		info;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, "FRACTOL", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	new_info(&info, mlx, img);
	mlx_image_to_window(mlx, img, 0, 0);
	image(info.k, info.image, &info);
	mlx_cursor_hook(mlx, &func_m, &info);
	mlx_scroll_hook(mlx, &func, &info);
	mlx_loop_hook(mlx, &hook, &info);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}