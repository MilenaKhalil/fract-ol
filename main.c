#include "fractol.h"

static mlx_image_t	*g_img;
int iter = 180;
double	k = 1;

int get_rgb(int r, int g, int b)
{
    return (r << 24 | g << 16 | b << 8 | 0xFF);
}

complex_t count(complex_t z1, complex_t z2)
{
    return (comp_sum(comp_mul(z1, z1), z2));
}

bool check(complex_t z1)
{
    if (sqrt(pow(z1.real, 2) + pow(z1.imag, 2)) > 2)
        return (0);
    return (1);
}

void	image(double k)
{	
    complex_t z1;
    complex_t z2;

	for (double x = 0; x < g_img->width; x++)
   	{
		double y = 0;
		for(double y = 0; y < g_img->height; y++)
       	{
			double t = 0;
			z1.real = (4 / ((double) WIDTH) * x - 2.5) / k;
			z1.imag = (4 / ((double) WIDTH) * y - 2 * ((double)HEIGHT) / ((double)WIDTH)) / k;
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
               	mlx_put_pixel(g_img, x, y, (int)(t / iter * 0xFFFFFFFF) % 0xFFFFFF00 + 0x000000FF);
       	}
   	}
}

void	hook(void* param)
{
	mlx_t* mlx;
	mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		k *= 1.3;
		image(k);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		k /= 1.3;
		image(k);
	}
}

int32_t	main(void)
{
	mlx_t*    mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "FRACTOL", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, g_img, 0, 0);
	image(k);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

