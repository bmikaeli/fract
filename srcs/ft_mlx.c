#include "fractol.h"


void pixel_put_to_image(t_mlx *e, ulong img_color, int x, int y) {
    char *data;
    uint colorR;
    uint colorG;
    uint colorB;

    data = mlx_get_data_addr(e->img_ptr, &(e->bpp), &(e->size_line), &(e->endian));
    colorB = mlx_get_color_value(e->mlx_ptr, (img_color & 0xff));
    colorG = mlx_get_color_value(e->mlx_ptr, (img_color & 0xff00) >> 8);
    colorR = mlx_get_color_value(e->mlx_ptr, (img_color & 0xff0000) >> 16);
    *(data + y * e->size_line + (e->bpp / 8) * x) = colorB;
    *(data + y * e->size_line + (e->bpp / 8) * x + 1) = colorG;
    *(data + y * e->size_line + (e->bpp / 8) * x + 2) = colorR;
}

void draw_line_to_image(t_mlx *env, int x1, int x2, int y1, int y2, int color) {
    pixel_put_to_image(env, 0xffffff, x1, y1);
    pixel_put_to_image(env, 0xffffff, x2, y2);
    pixel_put_to_image(env, 0xffffff, abs(x2 - x1) / 2, abs(y2 - y1) / 2);
}

void ft_add_infos(t_mlx *mlx) {
    mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 20, 0xff0000, "zoom :");
    mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 60, 20, 0xff0000, ft_itoa(mlx->zoom));
    mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 80, 20, 0xff0000, "iterations :");
    mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 160, 20, 0xff0000, ft_itoa(mlx->iteration));
}

int ft_gere_expose(t_mlx *mlx) {
    if (mlx->name == JULIA)
        julia(mlx);
    if (mlx->name == MANDELBROT)
        mandelbrot(mlx);
    if (mlx->name == SIERPINSKI)
        drawSierpinski(mlx, 10, HEIGHT - 10, WIDTH - 10, HEIGHT - 10, WIDTH / 2, 10);

    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
    ft_add_infos(mlx);
    return (0);
}

int handle_mouse_motion(int x, int y, t_mlx *mlx) {
    if (x > mlx->last_x)
        mlx->Cb += 0.01f;
    if (x < mlx->last_x)
        mlx->Cb -= 0.01f;
    if (y > mlx->last_y)
        mlx->Ca += 0.01f;
    if (y < mlx->last_y)
        mlx->Ca -= 0.01f;
    if (!mlx->lock) {

    }
    mlx->last_x = x;
    mlx->last_y = y;
    ft_gere_expose(mlx);
    return 0;
}

int handle_mouse_button(int button, int x, int y, t_mlx *mlx) {
    if (button == 4)
        mlx->zoom -= 0.025f;
    if (button == 5)
        mlx->zoom += 0.025f;
    (void) y;
    (void) x;
    ft_gere_expose(mlx);
    return (0);
}

int key_hook(int keycode, t_mlx *mlx) {
    if (keycode == 99) {
        mlx->color_shift++;
        if (mlx->color_shift >= 12)
            mlx->color_shift = 4;
    }
    if (keycode == ECHAP)
        exit(1);

    if (keycode == UP)
        mlx->mouse_y += 0.003 / mlx->zoom;
    if (keycode == DOWN)
        mlx->mouse_y -= 0.003 / mlx->zoom;
    if (keycode == LEFT)
        mlx->mouse_x -= 0.003 / mlx->zoom;
    if (keycode == RIGHT)
        mlx->mouse_x += 0.003 / mlx->zoom;

    if (keycode == MINUS && mlx->iteration > 1)
        mlx->iteration -= 1;
    if (keycode == PLUS)
        mlx->iteration += 1;
    ft_gere_expose(mlx);
    return (0);
}