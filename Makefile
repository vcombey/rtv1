# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcombey <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/30 19:59:01 by vcombey           #+#    #+#              #
#    Updated: 2017/09/05 05:12:29 by vcombey          ###   ########.fr        #
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

INCLUDE = -I ./libft/ -I ./includes -g

OBJS = $(addprefix objs/, $(SRC:.c=.o))

CFLAGS += -Wall -g -o2 -flto -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft/
	@gcc -g $(OBJS) $(SANITIZER) -L libft -lft -lmlx -framework OpenGL -framework AppKit -o2 -flto -o $(NAME)

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
