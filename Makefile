# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 16:16:41 by deelliot          #+#    #+#              #
#    Updated: 2022/10/12 22:11:29 by thakala          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address -Wconversion

# Directories
SRC_DIR = ./srcs/
OBJ_DIR = ./obj/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/
MINILBX_DIR = ./minilibx/

# Source and object files
SRCS = main.c
SRCS += initialise.c
SRCS += image.c
SRCS += error_handling.c
SRCS += tuple_operations.c
SRCS += matrix_maths.c
SRCS += matrix_inversion.c
SRCS += handle_input.c


OBJ_FILES = $(SRCS:.c=.o)

# Paths
SRC = $(addprefix $(SRC_DIR), $(SRCS))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
MINLBX = $(addprefix $(MINILBX_DIR), libmlx.a)

# Libraries
LINKS =  -L $(LIBFT_DIR) -lft
LINKS +=  -L $(MINILBX_DIR) -lmlx -Ofast -framework OpenGL -framework Appkit
# LINKS += -L /usr/local/lib -lmlx -I /usr/local/include -framework \
# 	OpenGL -framework AppKit


#Rules
all: obj $(LIBFT) $(MINLBX) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@gcc $(FLAGS) -I $(MINILBX_DIR) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<
$(LIBFT):
	@make -C $(LIBFT_DIR)
$(MINLBX):
	@make -C $(MINILBX_DIR)

$(NAME): $(OBJ)
	@gcc $(OBJ) $(FLAGS) $(LINKS) -lm -o $(NAME)
	@echo "Usage: ./RTV1 + option"
	@echo "options: >> ??"

clean:
	@rm -Rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo " Objects removed"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo " $(NAME) removed "

re: fclean all

.PHONY: all clean fclean re
