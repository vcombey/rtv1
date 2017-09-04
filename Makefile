# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcombey <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/30 19:59:01 by vcombey           #+#    #+#              #
#    Updated: 2017/09/04 17:14:13 by vcombey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	rt_v1

SRC =	main.c			\
		ft_pixelput.c	\
		calc.c	\
		env.c			\
		opp_double.c	\
		opp_double_vect.c	\
		opp_vect.c	\

INCLUDE = -I ./libft/includes -I ./includes -g

OBJS = $(addprefix objs/, $(SRC:.c=.o))

CFLAGS += -Wall -g -o2 -flto -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft/
	@gcc -g $(OBJS) -L libft -lft -lmlx -framework OpenGL -framework AppKit -o2 -flto -o $(NAME)

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
