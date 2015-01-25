#include "fractol.h"

void julia(t_mlx *mlx) {
    float Re;
    float temp;
    float Im;
    int color;
    int y;
    int x;
    x = 0;
    int i = 0;
    while (++x < mlx->img_height) {
        y = 0;
        while (y < mlx->img_width) {

            Re = mlx->zoom * (float) x / WIDTH - (mlx->zoom / 2) + mlx->mouse_x;
            Im = -mlx->zoom * (float) y / HEIGHT + (mlx->zoom / 2) + mlx->mouse_y;

//            Re =  (x - WIDTH / 2) / ( mlx->zoom * WIDTH);// + movex
//            Im =(y - HEIGHT / 2) / ( mlx->zoom * HEIGHT); // + movey

            i = -1;
            while (++i < mlx->iteration) {
                temp = Re;

                Re = Re * Re - Im * Im + mlx->Ca;
                Im = 2 * temp * Im + mlx->Cb;
                if (Re * Re + Im * Im > 4)
                    break;
            }
            color = (255 - i * 255) / mlx->iteration << mlx->color_shift;
            color += (255 - i * 255) / mlx->iteration;
            pixel_put_to_image(mlx, color, x, y);
            y++;
        }
    }
}

void mandelbrot(t_mlx *mlx) {
    int color;
    float newRe, newIm, oldRe, oldIm, pi, pr;
    int y;
    int x;
    x = 0;
    int i = 0;
    while (++x < mlx->img_height) {
        y = 0;
        while (y < mlx->img_width) {

            pr = mlx->zoom * (float) x / WIDTH - (mlx->zoom / 2);//+ mlx->mouse_x;
            pi = -mlx->zoom * (float) y / HEIGHT + (mlx->zoom / 2);// + mlx->mouse_y;

            newRe = newIm = oldRe = oldIm = 0;

            for (i = 0; i < mlx->iteration; i++) {
                oldRe = newRe;
                oldIm = newIm;
                newRe = oldRe * oldRe - oldIm * oldIm + pr;
                newIm = 2 * oldRe * oldIm + pi;
                if ((newRe * newRe + newIm * newIm) > 4) break;
            }
            color = (255 - i * 255) / mlx->iteration << mlx->color_shift;
            color += (255 - i * 255) / mlx->iteration;
            pixel_put_to_image(mlx, color, x, y);
            y++;
        }
    }
}

static void subTriangle(t_mlx *mlx, int n, float x1, float y1, float x2, float y2, float x3, float y3) {
    draw_line_to_image(mlx, x1, y1, x2, y2, 0xff0000);
    draw_line_to_image(mlx, x1, y1, x3, y3, 0xff0000);
    draw_line_to_image(mlx, x2, y2, x3, y3, 0xff0000);

    if (n < mlx->iteration) {
        subTriangle
                (
                        mlx,
                        n + 1,
                        (x1 + x2) / 2 + (x2 - x3) / 2,
                        (y1 + y2) / 2 + (y2 - y3) / 2,
                        (x1 + x2) / 2 + (x1 - x3) / 2,
                        (y1 + y2) / 2 + (y1 - y3) / 2,
                        (x1 + x2) / 2,
                        (y1 + y2) / 2
                );
        subTriangle
                (
                        mlx,
                        n + 1,
                        (x3 + x2) / 2 + (x2 - x1) / 2,
                        (y3 + y2) / 2 + (y2 - y1) / 2,
                        (x3 + x2) / 2 + (x3 - x1) / 2,
                        (y3 + y2) / 2 + (y3 - y1) / 2,
                        (x3 + x2) / 2,
                        (y3 + y2) / 2
                );
        subTriangle
                (
                        mlx,
                        n + 1,
                        (x1 + x3) / 2 + (x3 - x2) / 2,
                        (y1 + y3) / 2 + (y3 - y2) / 2,
                        (x1 + x3) / 2 + (x1 - x2) / 2,
                        (y1 + y3) / 2 + (y1 - y2) / 2,
                        (x1 + x3) / 2,
                        (y1 + y3) / 2
                );
    }
}

void drawSierpinski(t_mlx *mlx, float x1, float y1, float x2, float y2, float x3, float y3) {
    draw_line_to_image(mlx, x1, y1, x2, y2, 0xff0000);
    draw_line_to_image(mlx, x1, y1, x3, y3, 0xff0000);
    draw_line_to_image(mlx, x2, y2, x3, y3, 0xff0000);

    subTriangle
            (
                    mlx,
                    1,
                    (x1 + x2) / 2,
                    (y1 + y2) / 2,
                    (x1 + x3) / 2,
                    (y1 + y3) / 2,
                    (y2 + y3) / 2
            );
}
