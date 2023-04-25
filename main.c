/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikhalil <mikhalil@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 23:09:01 by mikhalil      #+#    #+#                 */
/*   Updated: 2023/04/25 23:28:29 by mikhalil      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	lyap(t_info *info, double k)
{
	double	r0;
	double	r1;
	double	lia;
	double	x0;
	double	x1;

	for (double x = 0; x < info->width; x++)
	{
		for(double y = 0; y < info->height; y++)
		{
			r0 = 4 * x / info->width / k + (info->arrows)[0];                            //(4 * (x - info->xpos) / (info->width)) / k - info->xx;
			r1 = (4 - 4 * y / info->height) / k - (info->arrows)[1];                           //(4 * (y - info->ypos) / (info->width)) / k - info->yy;
			x0 = 0.7;
			lia = 0;
			for (int i = 0; i < info->iter; i++)                                       // think about number of iterations
			{
				if (i % 2 == 0)
				{
					if (x0 != 0.5)
						lia += log(absolut(r0 * (1 - (2 * x0))));
					x1 = r0 * x0 * (1 - x0);
				}
				else
				{
					lia += log(absolut(r1 * (1 - (2 * x1))));
					x0 = r1 * x1 * (1 - x1);
				}
			}
			//lia /= 10;
			//printf("lia = %f\n", lia);
			mlx_put_pixel(info->image, x, y, get_rgb(
						(int)(lia + (info->colors)[0]) % 0xFF,
						(int)(lia + (info->colors)[1]) % 0xFF,
						(int)(lia + (info->colors)[2]) % 0xFF));
		}
	}
}

void	image(double k, mlx_image_t *img, t_info *info)
{	
	t_complex	z1;
	t_complex	z2;
	char		col_iter;

	if (info->fractal == 'L')
	{
		lyap(info, k);
		return ;
	}
	for (double x = 0; x < img->width; x++)
	{
		for(double y = 0; y < img->height; y++)
		{
			double t = 0;
			z1.real = (4 * (x - info->xpos) / (info->width)) / k + (info->arrows)[0] - info->xx;
			z1.imag = (4 * (y - info->ypos) / (info->width)) / k + (info->arrows)[1] - info->yy;
			if (info->fractal == 'M')
				z2 = z1;
			else if (info->fractal == 'J')
			{
				z2.real = (info->arrows)[0] - info->xx;
				z2.imag = (info->arrows)[1] - info->yy;
			}
			//z2.real = -0.79;
			//z2.imag = 0.15;
			for (int j = 0; j < info->iter; j++)
			{
				t = j;
				z1 = count(z1, z2);
				if (!check(z1))
					break;
				if (info->fractal == 'J' && j == ITER / 3)
					break;
			}
			if (check(z1))
				mlx_put_pixel(img, x, y, get_rgb(0, 0, 0));
			else
			{
				col_iter = (int)(sin(t / ITER * M_PI) * 0xFF);
				mlx_put_pixel(img, x, y, get_rgb(
						(int)(col_iter + (info->colors)[0]) % 0xFF,
						(int)(col_iter + (info->colors)[1]) % 0xFF,
						(int)(col_iter + (info->colors)[2]) % 0xFF));
			}
			// if (z1.real == 0 && z1.imag == 0)
			// 	mlx_put_pixel(img, x, y, get_rgb(0xFF, 0xFF, 0xFF));
		}
	}
}

void	hook(void *param)                                                   // think of resize later
{
	t_info	*info;

	info = (t_info *)param;
	arrows_check(info);
	colors_check(info);
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	if (mlx_is_key_down(info->mlx, MLX_KEY_I))
	{
		info->iter += 10;
		image(info->k, info->image, info);
	}
	if (info->width != info->mlx->width || info->height != info->mlx->height)
	{
		info->xx /= info->width;
		//(info->arrows)[0] /= info->width;
		info->yy /= info->height;
		//(info->arrows)[1] /= info->height;
		info->width = (double)info->mlx->width;
		info->xx *= info->width;
		//(info->arrows)[0] *= info->width;
		info->height = (double)info->mlx->height;
		info->yy *= info->height;
		//(info->arrows)[1] *= info->height;
		mlx_resize_image(info->image, info->width, info->height);
		image(info->k, info->image, info);
	}
}

bool	input_check(mlx_t *mlx, int argc, char **argv)
{
	if (argc == 1)                                                       // no arg
		return (write(1, "L, M, J", 7));
	if (argv[1][0] == 'M' && argv[1][0] == 0 && argc == 2)               // mandelbrot
		return (0);
	return (!mlx || argv[1][1] != 0 ||
		(argv[1][0] != 'M' && argv[1][0] != 'J' && argv[1][0] != 'L'));
}

int32_t	main(int argc, char **argv)
{
	mlx_t		*mlx;
	t_info		info;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, "FRACTOL", true);
	if (input_check(mlx, argc, argv))
		exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	new_info(&info, mlx, img, argv[1][0]);
	mlx_image_to_window(mlx, img, 0, 0);
	image(info.k, info.image, &info);
	mlx_cursor_hook(mlx, &mouse_pos, &info);
	mlx_scroll_hook(mlx, &scroll_pos, &info);
	mlx_loop_hook(mlx, &hook, &info);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}