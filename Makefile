NAME	:= pipex
LIBFT	:= libft
OBJ_DIR	:= obj/
INCLUDE	:= -I libft/include
CFLAGS	:= -Wall -Werror -Wextra
CC		:= gcc


ifdef WITH_BONUS
SRC_FILES	+= ft_pipex_bonus.c pipex_utils_bonus.c pipex_err_bonus.c
else
SRC_FILES	+= ft_pipex.c pipex_utils.c pipex_err.c
endif

SRC_FILES 	+= get_cmd_path.c
OBJ_FILES	= $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

$(OBJ_DIR):
	mkdir -p $@

$(NAME): $(OBJ_DIR) $(OBJ_FILES)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ_FILES) libft/libft.a -o $@

bonus:
	make WITH_BONUS=1 all

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJ_DIR)
fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)
re: fclean all

PHONY: all bonus clean fclean re
