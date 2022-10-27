# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thakala <thakala@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 13:04:07 by deelliot          #+#    #+#              #
#    Updated: 2022/10/27 12:58:25 by thakala          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# Directories
SRC_DIR = srcs
OBJ_DIR = obj
INC_DIR = includes

#folders
VEC_DIR = vec
LIST_DIR = list_funcs
STRING_DIR = strings
MEM_DIR = mem_funcs
PRINT_DIR = print
ASCII_DIR = ascii
VOID_DIR = void
CONVERSIONS_DIR = conversions
MATHS_DIR = maths
INPUT_DIR = input
GRAPHICS_DIR = graphics

# Source and object files

VEC_SRCS = vec.c

LIST_SRCS = ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
	ft_lstadd_back.c ft_lstmap.c

STRING_SRCS = ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
	ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
	ft_strtrim.c ft_strsplit.c ft_strlen.c ft_strdup.c ft_strcpy.c \
	ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
	ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_strrev.c \
	ft_stderror.c  ft_strndup.c ft_count_words.c

MEM_SRCS = ft_memset.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
	ft_memcmp.c ft_memdel.c ft_memallocarray.c ft_memdelarray.c \
	ft_memdelchararray.c ft_memalloc.c del.c ft_bzero.c

PRINT_SRCS = ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_print_array.c \
	ft_print_list.c ft_print_int_array.c

ASCII_SRCS = ft_isuppercase.c ft_islowercase.c ft_isalpha.c ft_isdigit.c \
	ft_isalnum.c ft_isascii.c ft_isspace.c ft_isprint.c

CONVERSION_SRCS = ft_toupper.c ft_tolower.c ft_atoi.c ft_itoa.c

MATHS_SRCS = ft_abs.c  ft_sqrt.c ft_find_next_sqrt.c ft_max.c \
	ft_linear_conversion.c ft_create_range.c ft_normalise_data.c

INPUT_SRCS = get_next_line.c

GRAPHICS_SRCS = rgb_to_hex.c hex_to_rgb.c

OBJ = $(addprefix $(OBJ_DIR)/,\
	$(addprefix $(VEC_DIR)/,$(VEC_SRCS:.c=.o)) \
	$(addprefix $(LIST_DIR)/,$(LIST_SRCS:.c=.o)) \
	$(addprefix $(STRING_DIR)/,$(STRING_SRCS:.c=.o)) \
	$(addprefix $(MEM_DIR)/,$(MEM_SRCS:.c=.o)) \
	$(addprefix $(ASCII_DIR)/,$(ASCII_SRCS:.c=.o)) \
	$(addprefix $(CONVERSIONS_DIR)/,$(CONVERSION_SRCS:.c=.o)) \
	$(addprefix $(MATHS_DIR)/,$(MATHS_SRCS:.c=.o)) \
	$(addprefix $(INPUT_DIR)/,$(INPUT_SRCS:.c=.o)) \
	$(addprefix $(GRAPHICS_DIR)/,$(GRAPHICS_SRCS:.c=.o)))

#Rules
all: obj-rule $(NAME)

obj-rule:
	@mkdir -p $(OBJ_DIR)/$(VEC_DIR)
	@mkdir -p $(OBJ_DIR)/$(LIST_DIR)
	@mkdir -p $(OBJ_DIR)/$(STRING_DIR)
	@mkdir -p $(OBJ_DIR)/$(MEM_DIR)
	@mkdir -p $(OBJ_DIR)/$(ASCII_DIR)
	@mkdir -p $(OBJ_DIR)/$(CONVERSIONS_DIR)
	@mkdir -p $(OBJ_DIR)/$(MATHS_DIR)
	@mkdir -p $(OBJ_DIR)/$(INPUT_DIR)
	@mkdir -p $(OBJ_DIR)/$(GRAPHICS_DIR)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
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

.PHONY: all clean fclean re obj-rule