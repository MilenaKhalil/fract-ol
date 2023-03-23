#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <complex.h>
#include <math.h>
#define WIDTH 1024
#define HEIGHT 512

static mlx_image_t	*g_img;
int iter = 180;
double	k = 1.1;

int get_rgb(int r, int g, int b)
{
    return (r << 24 | g << 16 | b << 8 | 0xFF);
}

double complex count(double complex z1, double complex z2)
{
    return (z1 * z1 + z2);
}

bool check(double complex z1)
{
    if (sqrt(pow(creal(z1), 2) + pow(cimag(z1), 2)) > 2)
        return (0);
    return (1);
}

void	image(double k)
{	
    double complex z1;
    double complex z2;

	for (double x = 0; x < g_img->width; x++)
   	{
		double y = 0;
		for(double y = 0; y < g_img->height; y++)
       	{
			double t = 0;
           	z1 = (x / 256 - 2.5) / k + 0.25 + ((y / 256 - 1)) / k * I;
           	z2 = z1;
           	for (int j = 0; j < iter; j++)
           	{
				t = j;
               	z1 = count(z1, z2);
				if (!check(z1))
                   	break;
           	}
           	if (check(z1))
		    	mlx_put_pixel(g_img, x, y, get_rgb(0, 0, 0));
           	else
               	mlx_put_pixel(g_img, x, y, (int)(t / iter * 0xFFFFFFFF) % 0xFFFFFF00 + 0x000000FF);//get_rgb((t / iter) * 0xFF, 0, ((int) t) % 0xFF));
       	}
   	}
}

void	hook(void* param)
{
	mlx_t* mlx;
	mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image(++k);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image(--k);
}

int32_t	main(void)
{
	mlx_t*    mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "FRACTOL", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, 1024, 512);
	mlx_image_to_window(mlx, g_img, 0, 0);
	image(k);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

