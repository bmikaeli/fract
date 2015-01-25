CC = gcc
CFLAGS = -std=c99 -O3 -Wall -Wextra
SRCS_D = srcs/
OBJS_D = objs/
HEADERS = includes/
SRCS = main.c fractals.c ft_mlx.c

OBJS = $(SRCS:.c=.o)
OBJS_P = $(addprefix $(OBJS_D), $(OBJS))
LDIR = libft
LFLAGS = -L$(LDIR) -lft

NAME = fractol

all: lib $(NAME)

$(NAME): $(LDIR)/libft.a $(OBJS_P)
	$(CC) -o $(NAME) $(OBJS_P) $(CFLAGS) $(LFLAGS)

$(addprefix $(OBJS_D), %.o): $(addprefix $(SRCS_D), %.c)
	@mkdir -p $(OBJS_D)
	$(CC) -c -o $@ $^ $(CFLAGS) -I $(HEADERS) -I $(LDIR)/includes -I /usr/X11/include -I /opt/X11/include/X11 -g -L/usr/X11/lib -lX11 -lmlx -lXext

lib:
	make -C $(LDIR)

clean:
	rm -f $(OBJS_P)
	make clean -C $(LDIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LDIR)

re: fclean all

.PHONY: clean, fclean, re, all
