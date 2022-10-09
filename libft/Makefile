# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 13:04:07 by deelliot          #+#    #+#              #
#    Updated: 2022/08/30 15:27:26 by deelliot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

# Directories
SRC_DIR = ./srcs/
OBJ_DIR = ./obj/
INC_DIR = ./includes/

# Source and object files
SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
	ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c \
	ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c \
	ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isuppercase.c \
	ft_islowercase.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	ft_isspace.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c \
	ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
	ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
	ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c \
	ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
	ft_lstiter.c ft_lstadd_back.c ft_lstmap.c ft_strndup.c get_next_line.c \
	ft_abs.c ft_memallocarray.c ft_sqrt.c ft_find_next_sqrt.c ft_max.c \
	ft_print_array.c ft_count_words.c ft_strrev.c ft_normalise_data.c \
	rgb_to_hex.c hex_to_rgb.c ft_memdelarray.c ft_memdelchararray.c \
	ft_print_list.c del.c ft_print_int_array.c ft_stderror.c \
	ft_linear_conversion.c ft_create_range.c

OBJ_FILES = $(SRCS:.c=.o)

# Paths
SRC = $(addprefix $(SRC_DIR), $(SRCS))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

#Rules
all: obj $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@gcc -c -I $(INC_DIR) $(FLAGS) -o $@  $<

$(NAME): $(OBJ)
	@clear
	@echo "***** $(NAME) generated *****"
	@ar rc $(NAME) $(OBJ)


clean:
	@rm -f $(OBJS)
	@rm -Rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f a.out

re: fclean all

.PHONY: all clean fclean re