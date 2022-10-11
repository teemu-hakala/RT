# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 16:16:41 by deelliot          #+#    #+#              #
#    Updated: 2022/10/11 10:39:03 by deelliot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# Directories
SRC_DIR = ./srcs/
OBJ_DIR = ./obj/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/

# Source and object files
SRCS = main.c
SRCS += initialise.c
SRCS += image.c
SRCS += error_handling.c
SRCS += tuple_operations.c
SRCS += matrix_maths.c
SRCS += handle_input.c

OBJ_FILES = $(SRCS:.c=.o)

# Paths
SRC = $(addprefix $(SRC_DIR), $(SRCS))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

# Libraries
LINKS =  -L $(LIBFT_DIR) -lft
LINKS += -L /usr/local/lib -lmlx -I /usr/local/include -framework \
	OpenGL -framework AppKit

#Rules
all: obj $(LIBFT) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@gcc $(FLAGS) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<
$(LIBFT):
	@make -C $(LIBFT_DIR)


$(NAME): $(OBJ)
	@gcc $(OBJ) $(FLAGS) $(LINKS) -lm -o $(NAME)
	@echo
	@echo "Usage: ./RTV1 + option"
	@echo "options: >> ??"

clean:
	@rm -Rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MINILBX_DIR)
	@echo " Objects removed"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo " $(NAME) removed "

re: fclean all

.PHONY: all clean fclean re