# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/30 19:59:01 by vcombey           #+#    #+#              #
#    Updated: 2017/09/24 14:51:34 by vcombey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

APPEND=
ASAN=
TEST_FILE=

OPTIMIZATION ?= -O0

ifeq ($(ASAN),yes)
	SANITIZER ?= -fsanitize=address
endif

NAME =	rtv1

SRC =	main.c			\
		ft_pixelput.c	\
		key_pressed.c	\
		key_event.c	\
		parse_lights.c	\
		parsing.c	\
		env.c			\
		parse_scene.c	\
		parse_objects.c	\
		get_coordinates.c	\
		cl_get_error_string.c \
		cl_methods.c \
		mouse/mouse_ray.c \
		mouse/opp_double.c \
		mouse/opp_double_vect.c \
		mouse/opp_vect.c \
		mouse/rot.c \
		mouse/figures.c	\

INCLUDE = -I ./libft -I ./includes -I ./minilibx_macos/

OBJS = $(addprefix objs/, $(SRC:.c=.o))

CFLAGS += -Wall -g3 -O0 -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft/
	./builter.sh
	@gcc -g $(OBJS) $(SANITIZER) -L libft -lft -L minilibx_macos -lmlx -framework OpenGL -framework OpenCl -framework AppKit -g3 -O0 -o $(NAME)

clean:
	make clean -C ./libft/
	/bin/rm -rf objs

fclean: clean
	/bin/rm -f ./libft/libft.a
	/bin/rm -f $(NAME)

re: fclean all

objs/%.o : src/%.c
	mkdir -p ./objs/mouse
	@/bin/mkdir -p objs
	gcc $(INCLUDE) $(SANITIZER) $(CFLAGS) -c -o $@ $<

.PHONY: all clean fclean re
