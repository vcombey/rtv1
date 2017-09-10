# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcombey <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/30 19:59:01 by vcombey           #+#    #+#              #
#    Updated: 2017/09/07 09:11:26 by vcombey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

APPEND=
ASAN=
TEST_FILE=

OPTIMIZATION ?= -O0

ifeq ($(ASAN),yes)
	SANITIZER ?= -fsanitize=address -fno-omit-frame-pointer
endif

NAME =	rtv1

SRC =	main.c			\
		ft_pixelput.c	\
		lum.c	\
		key_pressed.c	\
		key_event.c	\
		ombre.c	\
		hit.c	\
		parse_lights.c	\
		rot.c	\
		parsing.c	\
		figures.c	\
		calc.c	\
		env.c			\
		opp_double.c	\
		opp_double_vect.c	\
		opp_vect.c	\
		parse_scene.c	\
		parse_objects.c	\
		get_coordinates.c	\
		obj.c	\

INCLUDE = -I ./libft -I ./includes -I ./minilibx_macos/

OBJS = $(addprefix objs/, $(SRC:.c=.o))

CFLAGS += -Wall -g -o2 -flto -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft/
	@gcc -g $(OBJS) -L libft -lft -lmlx -framework OpenGL -framework AppKit -o2 -flto -L minilibx_macos -lmlx -o $(NAME)

clean:
	make clean -C ./libft/
	/bin/rm -rf objs

fclean: clean
	/bin/rm -f ./libft/libft.a
	/bin/rm -f $(NAME)

re: fclean all

objs/%.o : src/%.c
	@/bin/mkdir -p objs
	gcc $(INCLUDE) $(CFLAGS) -c -o $@ $<

.PHONY: all clean fclean re
