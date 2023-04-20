#include "fractol.h"

int		iter = 300;
double	k = 1;

int	get_rgb(char r, char g, char b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

complex_t	count(complex_t z1, complex_t z2)
{
	return (comp_sum(comp_mul(z1, z1), z2));
}

bool	check(complex_t z1)
{
	if (sqrt(pow(z1.real, 2) + pow(z1.imag, 2)) > 3)
		return (0);
	return (1);
}

void	image(double k, mlx_image_t *img, double xpos, double ypos)
{	
	complex_t	z1;
	complex_t	z2;
	char		col_iter;

	for (double x = 0; x < img->width; x++)
	{
		for(double y = 0; y < img->height; y++)
		{
			double t = 0;
			z1.real = (4 / ((double)img->width) * (x + xpos) - 2.5) / k;
			z1.imag = (4 / ((double)img->width) * (y + ypos) - 2 * ((double)img->height) / ((double)img->width)) / k;
			z2 = z1;
			for (int j = 0; j < iter; j++)
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
				col_iter = (int)(sin(t / iter * M_PI) * 0xFF);
				mlx_put_pixel(img, x, y, get_rgb(col_iter / 2, (int)(col_iter / ((sin(t) + 1))) & 0xFF, col_iter)); //(int)(t / iter * 0xFF) | (0xFF000000 & 0x000000FF));
			}
		}
	}
}

void	hook(void *param)
{
	t_info	*info;

	info = (t_info *)param;
	if (mlx_is_key_down(info->mlx, MLX_KEY_UP))
	{
		k *= 1.3;
		image(k, info->image, info->xpos, info->ypos);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_DOWN))
	{
		k /= 1.3;
		image(k, info->image, info->xpos, info->ypos);
	}
	if (info->width != info->mlx->width || info->height != info->mlx->height)
	{
		info->width = info->mlx->width;
		info->height = info->mlx->height;
		mlx_resize_image(info->image, info->width, info->height);
		image(k, info->image, info->xpos, info->ypos);
	}
}

void	func(double xdelta, double ydelta, void *info)
{
	//(void) param;
	// Simple up or down detection.
	(void) xdelta;
	if (ydelta > 0)
	{
		k *= 1.3;
		image(k, ((t_info*) info)->image, ((t_info*) info)->xpos, ((t_info*) info)->ypos);
	}
	else if (ydelta < 0)
	{
		k /= 1.3;
		image(k, ((t_info*) info)->image, ((t_info*) info)->xpos, ((t_info*) info)->ypos);
	}
}

void	func_m(double xpos, double ypos, void *info)
{
	// printf("ypos = %lf\n", ypos);
	// printf("xpos = %lf\n", xpos);
	((t_info*) info)->xpos = xpos;
	((t_info*) info)->ypos = ypos;
	image(k, ((t_info*) info)->image, xpos, ypos);
	//if (ypos > 0)
	//{
		//puts(ypos);
	//}
	// if (xpos < 0)
	// 	puts("Sliiiide to the left!");
	// else if (xpos > 0)
	// 	puts("Sliiiide to the right!");
}

int32_t	main(void)
{
	mlx_t		*mlx;
	t_info		info;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, "FRACTOL", true);
	info.mlx = mlx;
	if (!mlx)
		exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	info.image = img;
	info.width = WIDTH;
	info.height = HEIGHT;
	mlx_image_to_window(mlx, img, 0, 0);
	image(k, info.image, 0, 0);
	mlx_cursor_hook(mlx, &func_m, &info);
	mlx_scroll_hook(mlx, &func, &info);
	mlx_loop_hook(mlx, &hook, &info);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
