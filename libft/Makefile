NAME		= libft.a
SRC_FR		= src/
OBJ_FR		= obj/
INCLUDES	= ./include
CFLAGS		= -Wall -Werror -Wextra -I
CC		= gcc

FTIS_FR		= ft_is/
FTIS		= ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_isspace

FTTO_FR		= ft_to/
FTTO		= ft_atoi ft_itoa ft_tolower ft_toupper ft_stou ft_btoa

FTSTR_FR	= ft_str/
FTSTR		= ft_split ft_strdup ft_strjoin ft_strlcpy ft_strmapi ft_strnstr ft_strtrim ft_strchr \
		  ft_striteri ft_strlcat ft_strlen ft_strncmp ft_strrchr ft_substr

FTPUT_FR	= ft_put/
FTPUT		= ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd

FTMEM_FR	= ft_mem/
FTMEM		= ft_bzero ft_calloc ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset

FTLST_FR	= ft_lst/
FTLST		= ft_lstadd_back ft_lstclear ft_lstiter ft_lstmap ft_lstsize ft_lstadd_front \
		  ft_lstdelone ft_lstlast ft_lstnew

FTPRINTF_FR	= ft_printf/
FTPRINTF	= print_args print_p ft_printf_fd

SRC_FILES	+= $(addprefix $(FTIS_FR),$(FTIS))
SRC_FILES	+= $(addprefix $(FTTO_FR),$(FTTO))
SRC_FILES	+= $(addprefix $(FTSTR_FR),$(FTSTR))
SRC_FILES	+= $(addprefix $(FTPUT_FR),$(FTPUT))
SRC_FILES	+= $(addprefix $(FTMEM_FR),$(FTMEM))
SRC_FILES	+= $(addprefix $(FTLST_FR),$(FTLST))
SRC_FILES	+= $(addprefix $(FTPRINTF_FR),$(FTPRINTF))

SRCS		= $(addprefix $(SRC_FR), $(addsuffix .c, $(SRC_FILES)))
OBJS		= $(addprefix $(OBJ_FR), $(addsuffix .o, $(SRC_FILES)))

all:  ${OBJ_FR} ${NAME}

$(OBJ_FR)%.o : ${SRC_FR}%.c
	@${CC} ${CFLAGS} $(INCLUDES) -c $^ -o $@

$(OBJ_FR):
	@mkdir -p $(OBJ_FR)
	@mkdir -p $(OBJ_FR)$(FTIS_FR)
	@mkdir -p $(OBJ_FR)$(FTTO_FR)
	@mkdir -p $(OBJ_FR)$(FTSTR_FR)
	@mkdir -p $(OBJ_FR)$(FTPUT_FR)
	@mkdir -p $(OBJ_FR)$(FTMEM_FR)
	@mkdir -p $(OBJ_FR)$(FTLST_FR)
	@mkdir -p $(OBJ_FR)$(FTPRINTF_FR)

$(NAME): ${OBJ_FR} ${OBJS}
	@ar rcs $@ ${OBJS}

clean:
	rm -rf ${OBJ_FR}
fclean: clean
	rm -f ${NAME}
re: fclean all

.PHONY: all clean fclean re
