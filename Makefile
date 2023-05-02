# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikhalil <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2022/11/12 17:15:07 by mikhalil      #+#    #+#                  #
#    Updated: 2023/05/02 17:25:10 by mikhalil      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRC =	main.c \
		complex.c \
		utils.c \
		param.c \
		draw.c

MLX = MLX42/libmlx42.a

LIBFT = ./libft/libft.a

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -Ofast 

NAME = fractol

INCLUDE = -I ./

CC = cc

all: $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(MLX):
	$(MAKE) -C MLX42
	
$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $^ -o $@ -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

%.o: %.c fractol.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C libft
	$(MAKE) clean -C MLX42

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft
	$(MAKE) fclean -C MLX42

re: fclean all

.PHONY: all re fclean clean
