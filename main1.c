#include "./MLX42/include/MLX42/MLX42.h"

int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 640, 360, "Random Image");

    void *image = mlx_new_image(mlx, 640, 360);

    mlx_loop(mlx);
}