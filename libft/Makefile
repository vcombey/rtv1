#fields ************************** DEFINING COLORS ************************************** #

COLOR_CLEAR		= \033[2K
COLOR_UP		= \033[A
COLOR_NOCOLOR	= \033[0m
COLOR_BOLD		= \033[1m
COLOR_UNDERLINE	= \033[4m
COLOR_BLINKING	= \033[5m
COLOR_BLACK		= \033[1;30m
COLOR_RED		= \033[1;31m
COLOR_GREEN		= \033[1;32m
COLOR_YELLOW	= \033[1;33m
COLOR_BLUE		= \033[1;34m
COLOR_VIOLET	= \033[1;35m
COLOR_CYAN		= \033[1;36m
COLOR_WHITE		= \033[1;37m

# **************************************************************************** #

SRC = \
	  ft_lst_len.c \
	  ft_lst_last.c \
      ft_strjoin3_free.c \
      ft_is_executable.c \
	  ft_strlen.c \
	  ft_strchr.c \
	  ft_strrchr.c \
	  ft_strichr.c \
	  ft_strcpy.c \
	  ft_strcmp.c \
	  ft_strncmp.c \
	  ft_strncpy.c \
	  ft_strdup.c \
	  ft_strstr.c \
	  ft_strnstr.c \
	  ft_strncat.c \
	  ft_strlcat.c \
	  ft_strcat.c \
	  ft_strchange.c \
	  ft_abs.c \
	  ft_lst_iteri.c \
	  get_next_line.c \
	  ft_putnstr.c \
	  ft_arraymax_f.c \
	  ft_arraychr.c \
	  ft_arraylen.c \
	  palloc.c \
	  ft_putstr.c \
	  ft_putchar.c \
	  ft_bzero.c \
	  ft_memset.c \
	  ft_memalloc.c \
	  ft_calloc.c \
	  ft_memcpy.c \
	  ft_memcmp.c \
	  ft_memccpy.c \
	  ft_memchr.c \
	  ft_memmove.c \
	  ft_arraydup.c \
	  ft_atoi.c \
	  ft_is_1.c \
	  ft_is_2.c \
	  ft_toupper.c \
	  ft_tolower.c \
	  ft_memdel.c \
	  ft_putnbr.c \
	  ft_strnew.c \
	  ft_strdel.c \
	  ft_strclr.c \
	  ft_striter.c \
	  ft_striteri.c \
	  ft_strmap.c \
	  ft_strmapi.c \
	  ft_strequ.c \
	  ft_strnequ.c \
	  ft_strsub.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_strsplit.c \
	  ft_strsplit_keep.c \
	  charcmp.c \
	  ft_itoa.c \
	  ft_arraydel.c \
	  fatal.c \
	  free.c \
	  ft_buff_wchar.c \
	  ft_lst_add.c \
	  ft_lst_create.c \
	  ft_lst_del_one.c \
	  ft_lst_dup.c \
	  ft_lst_for_n.c \
	  ft_lst_foreach.c \
	  ft_lst_get_n.c \
	  ft_lst_pushback.c \
	  ft_lst_remove.c \
	  ft_lst_return_if.c \
	  ft_lst_sort_insert.c \
	  ft_chartostr.c \
	  ft_strmatch.c \
	  ft_strnreplace.c \
	  ft_strsurround.c \
	  ft_realloc.c \
	  ft_is_3.c \
	  ft_strrstr.c \
	  ft_strrcmp.c \
	  ft_strrequ.c \
	  ft_simple_lst_del_one.c \

NAME ?= libft.a


# Defining those variables allows auto completion to occure.
APPEND=
ASAN=
TEST_FILE=

OPTIMIZATION ?= -O0

ifeq ($(ASAN),yes)
	SANITIZER ?= -fsanitize=address -fno-omit-frame-pointer
endif

SRC_DIR = srcs
OBJ_DIR = objs
LOCAL_INC = includes
CFLAGS ?= -g -Wall -Wextra -Werror
CC = gcc
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))


all: Hello_word $(OBJ_DIR) $(NAME)
	@printf "$(COLOR_CLEAR)$(COLOR_GREEN)Successfully created $(COLOR_BLUE)$(NAME) !!!$(COLOR_NOCOLOR)\n"

Hello_word:
	@printf "$(COLOR_VIOLET)$(COLOR_UNDERLINE)Compiling$(COLOR_NOCOLOR) $(COLOR_BLUE)$(NAME) ...$(COLOR_NOCOLOR)\n"

$(NAME): $(OBJ)
	@printf "$(COLOR_GREEN)Successfully created objects files for library $(COLOR_BLUE)$(NAME) !!!$(COLOR_NOCOLOR)\n"
	@printf "$(COLOR_VIOLET)Creating $(NAME) ... $(COLOR_NOCOLOR)\n"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "$(COLOR_UP)$(COLOR_CLEAR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "$(COLOR_VIOLET)Creating objects files for library $(COLOR_BLUE)$(NAME) ... \n$(COLOR_CYAN)"
	$(CC) $(OPTIMIZATION) $(CFLAGS) -I$(LOCAL_INC) $(SANITIZER) $(APPEND) -c -o $@ $^ 
	@printf "\n$(COLOR_NOCOLOR)$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_UP)$(COLOR_CLEAR)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/printf

clean:
	@printf "$(COLOR_RED)Removing object files ...$(COLOR_NOCOLOR)\n"
	@rm -rf $(OBJ_DIR)
	@printf "$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_GREEN)Removed object files !!!$(COLOR_NOCOLOR)\n"

fclean: clean
	@printf "$(COLOR_RED)Removing library $(COLOR_BLUE)$(NAME) ...$(COLOR_NOCOLOR)\n"
	@rm -rf $(NAME)
	@printf "$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_GREEN)Removed library $(COLOR_BLUE)$(NAME) !!!$(COLOR_NOCOLOR)\n"

re: fclean all

test: all 
	@printf "$(COLOR_VIOLET)Compiling test $(TEST_FILE) ... $(COLOR_RESET)\n"
	@$(CC) -g $(TEST_FILE) -I$(LOCAL_INC) -L. -lft $(SANITIZER) $(APPEND)
	@printf "$(COLOR_GREEN)Done !!! Launching $(TEST_FILE) now !!!\n$(COLOR_NOCOLOR)"
	@./a.out

.PHONY: all clean fclean re
