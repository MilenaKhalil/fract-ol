# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikhalil <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2022/11/12 17:15:07 by mikhalil      #+#    #+#                  #
#    Updated: 2022/11/30 19:40:39 by mikhalil      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# something I've used for running!
# gcc main2.c MLX42/libmlx42.a -o fractol -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit && ./fractol

SRC = main2.c

MLX = MLX42/libmlx42.a

LIBFT = ./libft/libft.a

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra

NAME = fractol.a

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft
	cp $(LIBFT) $(NAME)
	ar -rc $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft

re: fclean all
