# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 16:16:41 by deelliot          #+#    #+#              #
#    Updated: 2022/11/29 13:34:28 by deelliot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
# FLAGS += -fsanitize=address -Wconversion -Ofast -flto

# Directories
SRCS_DIR = srcs
OBJS_DIR = objs
INCS = -I includes/ -I libft/includes/ -I minilibx/
HDRS = includes/RTv1.h \
	includes/colour_and_light.h \
	includes/matrices.h \
	includes/objects.h \
	includes/tuple.h \
	includes/world.h \
	includes/parse.h
LIBFT_DIR = libft
MINILIBX_DIR = minilibx

# folders
PARSE_DIR = parse
MATHS_DIR = maths
OBJECTS_DIR = objects
INTERSECT_DIR = intersect

# Source and object files
PARSE_SRCS = default_files.c parse_camera.c parse_cone.c parse_cylinder.c \
	parse_lights.c parse_single_light.c parse_plane.c parse_shapes.c \
	parse_sphere.c parse_sub_objs.c parse_utility.c parse.c rt_atof.c \
	rt_atoi.c dispatch_subobjects.c parse_material.c parse_transform.c \
	parse_cone_cylinder_subobj.c

OBJECTS_SRCS = camera.c transform_objects.c\

MATHS_SRCS = matrix_inversion.c matrix_maths.c matrix_transformations.c \
	tuple_operations.c matrix_rotations.c tuple_w.c tuple_basic_operations.c \

INTERSECT_SRCS = intersect_plane.c intersect_sphere.c intersect_cone.c \
	intersect_cylinder.c intersect_dispatch.c

FILES = \
	main.c \
	initialise.c \
	image.c \
	error_handling.c \
	handle_input.c \
	normal_utility.c \
	normal_dispatch.c \
	reflections.c \
	view_transform.c \
	shading.c \
	ray.c \
	render.c \
	colour.c \
	computation_dispatch.c \
	computations.c \

OBJS = $(addprefix $(OBJS_DIR)/, \
	$(addprefix $(PARSE_DIR)/, $(PARSE_SRCS:.c=.o)) \
	$(addprefix $(OBJECTS_DIR)/, $(OBJECTS_SRCS:.c=.o)) \
	$(addprefix $(MATHS_DIR)/, $(MATHS_SRCS:.c=.o))\
	$(addprefix $(INTERSECT_DIR)/, $(INTERSECT_SRCS:.c=.o))\
	$(FILES:.c=.o))

# Paths
LIBFT_A = $(LIBFT_DIR)/libft.a
MINILIBX_A = $(MINILIBX_DIR)/libmlx.a
LIBS = $(LIBFT_A) $(MINILIBX_A)

# Libraries
LINKS = \
	-lm \
	-L $(LIBFT_DIR) -lft \
	-L $(MINILIBX_DIR) -lmlx \
	-framework OpenGL -framework Appkit

# iMac minilibx:
# LINKS = -L /usr/local/lib -lmlx -I /usr/local/include -framework \
# 	OpenGL -framework AppKit

#Rules
all: libft $(NAME)

$(NAME): .prerequisites $(LIBS) $(OBJS) Makefile
	touch .prerequisites
	gcc $(FLAGS) $(INCS) $(LINKS) $(OBJS) -o $(NAME)
	@echo "Usage: ./RTV1 + option"
	@echo "options: >> ??"

$(OBJS): $(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c $(HDRS) Makefile
	gcc $(FLAGS) $(INCS) -o $@ -c $<

.prerequisites: $(OBJS_DIR)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)/$(PARSE_DIR)
	@mkdir -p $(OBJS_DIR)/$(MATHS_DIR)
	@mkdir -p $(OBJS_DIR)/$(OBJECTS_DIR)
	@mkdir -p $(OBJS_DIR)/$(INTERSECT_DIR)


libft:
	make -C $(LIBFT_DIR)
$(MINILIBX_A):
	make -C $(MINILIBX_DIR)

clean:
	/bin/rm -Rf $(OBJS_DIR)
	make clean -C $(LIBFT_DIR)
	@echo " Objects removed"

fclean: clean
	/bin/rm -f $(NAME) .prerequisites
	make -C $(LIBFT_DIR) fclean
	@echo " $(NAME) removed "

re: fclean all

.PHONY: all clean fclean re libft
