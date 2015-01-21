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

void julia(t_mlx *mlx) {
    int i, y = 0;
    float Za, temp, Zb;
    temp = 0;
    for (int x = 0; x < HEIGHT; x++) {
        for (y = 0; y < WIDTH; y++) {

            Za = 4 * (float) x / WIDTH - 2;
            Zb = -4 * (float) y / HEIGHT + 2;

            for (i = 0; Za * Za + Zb * Zb <= 4 && i < N; i++) {
                temp = Za;
                Za = Za * Za - Zb * Zb + mlx->Ca;
                Zb = 2 * temp * Zb + mlx->Cb;
            }
            pixel_put_to_image(mlx, ((255 - i * 255 / N) << 16) + ((255 - i * 255 / N) << 8) + (255 - i * 255 / N), x, y);
        }
    }
}

int ft_gere_expose(t_mlx *mlx) {

    julia(mlx);
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
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
    ft_gere_expose(mlx);
    return (0);
}


int main() {
    t_mlx mlx;


    mlx.mlx_ptr = mlx_init();
    mlx_do_key_autorepeaton(mlx.mlx_ptr);
    mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "Fract'Ol");
    mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, WIDTH, HEIGHT);
    mlx.Ca = 0.45001213f;
    mlx.Cb = 0;

    mlx_expose_hook(mlx.win_ptr, ft_gere_expose, &mlx);

    mlx_hook(mlx.win_ptr, 2, (1L << 0), key_hook, &mlx);
    mlx_loop(mlx.mlx_ptr);
    return (0);
}


