/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmikaeli <bmikaeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 16:21:26 by bmikaeli          #+#    #+#             */
/*   Updated: 2015/01/21 12:44:45 by bmikaeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void pixel_put_to_image(t_mlx *e, ulong img_color, int x, int y) {
    uint colorR;
    uint colorG;
    uint colorB;
    char *data;


    data = mlx_get_data_addr(e->img_ptr, &(e->bpp), &(e->size_line), &(e->endian));

    colorB = mlx_get_color_value(e->mlx_ptr, (img_color & 0xff));
    colorG = mlx_get_color_value(e->mlx_ptr, (img_color & 0xff00) >> 8);
    colorR = mlx_get_color_value(e->mlx_ptr, (img_color & 0xff0000) >> 16);
    *(data + y * e->size_line + (e->bpp / 8) * x) = colorB;
    *(data + y * e->size_line + (e->bpp / 8) * x + 1) = colorG;
    *(data + y * e->size_line + (e->bpp / 8) * x + 2) = colorR;
}

//void test(t_mlx *mlx) {
//    for (C.x = -W; C.x < W; C.x += INCR) {
//        for (C.y = -W; C.y < W; C.y += INCR) {
//            Z.x = Z.y = 0;
//            n = 0;
//            do {
//                n++;
//
//                Zp.x = Z.x * Z.x - Z.y * Z.y + C.x;
//                Zp.y = 2 * Z.x * Z.y + C.y;
//                Z.x = Zp.x;
//                Z.y = Zp.y;
//            } while ((Z.mod2() < 2) && (n < N));
//
//            // à changer de 'f' pour modifier les couleurs :
//            glColor3ub(f(n), f(n), f(n));
//
//            glVertex2d((C.x + Cm.x) / COEF, (C.y + Cm.y) / COEF);
//        }
//    }
//}
//#include <math.h>
//#include <complex.h>
//#define START_POS -0.5
//#define START_ZOOM (WIDTH * 0.25296875f)
//#define BAIL_OUT 2.0
//#define FLIPS 24
//#define ZOOM_FACTOR 4
//
//void test2(t_mlx *mlx) {
//    int zoom = START_ZOOM;
//    int f,x,y,n;
//    int maxiter = (WIDTH/2) * 0.049715909 * log10(zoom);
//    complex double z, c;
//    float C;
//    for (f = 0; f < FLIPS; f++) {
//        for (y = f; y < HEIGHT; y += FLIPS) {
//            for (x = 0; x < WIDTH; x++) {
///* Get the complex poing on gauss space to be calculate */
//                z = c = creal(center) + ((x - (WIDTH / 2)) / zoom) +
//                        ((cimag(center) + ((y - (HEIGHT / 2)) / zoom)) * _Complex_I);
//                #define X creal(z)
//                #define Y cimag(z)
//                /* Check if point lies within the main cardiod or
//                in the period-2 buld */
//                if ((pow(X - .25, 2) + pow(Y, 2)) * (pow(X, 2) + (X / 2) + pow(Y, 2) - .1875) < pow(Y, 2) / 4 ||
//                        pow(X + 1, 2) + pow(Y, 2) < .0625)
//                    n = maxiter;
//                else
///* Applies the actual mandelbrot formula on that point */
//                    for (n = 0; n <= maxiter && cabs(z) < BAIL_OUT; n++)
//                        z = cpow(z, 2) + c;
//                C = n - log2f(logf(cabs(z)) / M_LN2);
///* Paint the pixel calculated depending on the number
//of iterations found */
////                ((Uint32 *) surface->pixels)[(y * surface->w) + x] = (n >= maxiter) ? 0 : SDL_MapRGB(surface->format, (1 + sin(C * 0.27 + 5)) * 127., (1 + cos(C * 0.85)) * 127., (1 + sin(C * 0.15)) * 127.);
//            }
//            rects[y / FLIPS].x = 0;
//            rects[y / FLIPS].y = y;
//            rects[y / FLIPS].w = WIDTH;
//            rects[y / FLIPS].h = 1;
//        }
//    }
//};

int ft_gere_expose(t_mlx *mlx) {
    julia(mlx);
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
    return (0);
}

static int handle_mouse(t_mlx *mlx) {

    return (0);
}

static int key_hook(int keycode, t_mlx *mlx) {
    if (keycode == ECHAP) {
        exit(1);
    }
    if (keycode == UP) {
        mlx->Cb += 0.005f;
    }
    if (keycode == DOWN) {
        mlx->Cb -= 0.005f;
    }
    if (keycode == LEFT) {
        mlx->Ca += 0.005f;
    }
    if (keycode == RIGHT) {
        mlx->Ca -= 0.005f;
    }
    if (keycode == MINUS) {
        mlx->zoom += 0.05f;
//        mlx->N -= 1;
    }
    if (keycode == PLUS) {
        mlx->zoom -= 0.05f;

//        exit(1);
//        mlx->N += 1;
    }
    ft_gere_expose(mlx);
    return (0);
}


int main() {
    t_mlx mlx;


    mlx.mlx_ptr = mlx_init();
    mlx_do_key_autorepeaton(mlx.mlx_ptr);
    mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "Fract'Ol");
    mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, WIDTH, HEIGHT);
    mlx.Ca = 0;
    mlx.Cb = 0;
    mlx.N = 30;
    mlx.img_height = 1000;
    mlx.img_width = 1000;
    mlx.zoom = 4;
    julia(&mlx);
    mlx_expose_hook(mlx.win_ptr, ft_gere_expose, &mlx);
    mlx_mouse_hook(mlx.win_ptr, handle_mouse, &mlx);
    mlx_hook(mlx.win_ptr, 2, (1L << 0), key_hook, &mlx);
    mlx_loop(mlx.mlx_ptr);
    return (0);
}


