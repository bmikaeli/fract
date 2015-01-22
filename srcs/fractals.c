#include "fractals.h"

void julia(t_mlx *mlx) {
    int i, y = 0;
    float Za, temp, Zb;
    int color;
    temp = 0;
    for (int x = 0; x < mlx->img_height; x++) {
        for (y = 0; y < mlx->img_width; y++) {

            Za = mlx->zoom * (float) x / WIDTH - (mlx->zoom / 2);
            Zb = -mlx->zoom * (float) y / HEIGHT + (mlx->zoom / 2);

            for (i = 0; Za * Za + Zb * Zb <= 4 && i < mlx->N ; i++) {
                temp = Za;

                Za = Za * Za - Zb * Zb + mlx->Ca;
                Zb = 2 * temp * Zb + mlx->Cb;
            }
            color = ((255 - i * 255) / mlx->N) << 8;
//            color = i / mlx-> N  * 255 << 16;
//            color += i / mlx-> N  * 255 << 8;
//            color += i / mlx-> N  * 255;
            pixel_put_to_image(mlx, color, x, y);
        }
    }
}
