# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 16:16:41 by deelliot          #+#    #+#              #
#    Updated: 2023/01/31 19:37:32 by deelliot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
# FLAGS += -fsanitize=address -Wconversion -Ofast -flto

# Directories
SRCS_DIR = srcs
OBJS_DIR = objs
INCS = -I includes/ -I libft/includes/ -I minilibx/
HDRS = includes/RT.h \
	includes/colour_and_light.h \
	includes/matrices.h \
	includes/objects.h \
	includes/tuple.h \
	includes/world.h \
	includes/patterns.h \
	includes/parse.h \
	includes/threads.h \
	includes/user_interface.h \
	includes/input.h \

LIBFT_DIR = libft
MINILIBX_DIR = minilibx

# folders
CAMERA_DIR = camera
COMPUTATIONS_DIR = computations
COOL_INTERFACE_DIR = cool_interface
INTERSECT_DIR = intersect
LIGHTING_DIR = lighting
MATHS_DIR = maths
NORMAL_DIR = normal
PARSE_DIR = parse
PATTERNS_DIR = patterns
RENDER_DIR = render

# Source and object files
CAMERA_SRCS = camera.c transform_objects.c first_person_camera.c \
	view_transform.c

COMPUTATION_SRCS = computations_calculations.c

COOL_INTERFACE_SRCS = handle_input.c key_handlers.c mouse_input.c \
	movement_agent.c progress_bar.c scroll_effect.c zoomer.c \
	screenshot.c new_image_file.c ppm_buffer.c

INTERSECT_SRCS = intersect_plane.c intersect_sphere.c intersect_cone.c \
	intersect_cylinder.c intersect_cube.c intersect_dispatch.c

LIGHTING_SRCS = lighting.c reflections.c shade_hit.c 

MATHS_SRCS = matrix_inversion.c matrix_maths.c matrix_transformations.c \
	tuple_operations.c matrix_rotations.c tuple_w.c tuple_basic_operations.c \
	tuple_angles.c

NORMAL_SRCS = normal_at_cone.c normal_at_cube.c normal_at_cylinder.c \
	normal_at_plane.c normal_at_sphere.c normal_dispatch.c

PARSE_SRCS = default_files.c default_patterns.c parse_camera.c parse_cone.c \
	parse_cylinder.c parse_lights.c parse_single_light.c parse_plane.c \
	parse_shapes.c parse_sphere.c parse_sub_objs.c parse_utility.c parse.c \
	rt_atof.c rt_atoi.c dispatch_shape_subobjects.c parse_material.c \
	parse_transform.c parse_cone_cylinder_subobj.c parse_cube.c \
	shape_subobject_utility.c parse_patterns.c parse_faces.c parse_ppm.c \
	ppm_utility.c parse_textures.c default_textures.c parse_face_subobjects.c

PATTERNS_SRCS = pattern_dispatch.c patterns.c textures.c texture_dispatch.c \
	uv_mapping.c cube_mapping.c cube_mapping_utility.c

RENDER_SRCS = colour.c image_utility.c put_image.c ray.c threads.c

FILES = \
	main.c \
	initialise.c \
	error_handling.c \
	threads_mid.c \

OBJS = $(addprefix $(OBJS_DIR)/, \
	$(addprefix $(CAMERA_DIR)/, $(CAMERA_SRCS:.c=.o)) \
	$(addprefix $(COMPUTATIONS_DIR)/, $(COMPUTATION_SRCS:.c=.o))\
	$(addprefix $(COOL_INTERFACE_DIR)/, $(COOL_INTERFACE_SRCS:.c=.o)) \
	$(addprefix $(INTERSECT_DIR)/, $(INTERSECT_SRCS:.c=.o))\
	$(addprefix $(LIGHTING_DIR)/, $(LIGHTING_SRCS:.c=.o)) \
	$(addprefix $(MATHS_DIR)/, $(MATHS_SRCS:.c=.o))\
	$(addprefix $(NORMAL_DIR)/, $(NORMAL_SRCS:.c=.o))\
	$(addprefix $(PARSE_DIR)/, $(PARSE_SRCS:.c=.o)) \
	$(addprefix $(PATTERNS_DIR)/, $(PATTERNS_SRCS:.c=.o))\
	$(addprefix $(RENDER_DIR)/, $(RENDER_SRCS:.c=.o)) \
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
	@mkdir -p $(OBJS_DIR)/$(CAMERA_DIR)
	@mkdir -p $(OBJS_DIR)/$(COMPUTATIONS_DIR)
	@mkdir -p $(OBJS_DIR)/$(COOL_INTERFACE_DIR)
	@mkdir -p $(OBJS_DIR)/$(INTERSECT_DIR)
	@mkdir -p $(OBJS_DIR)/$(LIGHTING_DIR)
	@mkdir -p $(OBJS_DIR)/$(MATHS_DIR)
	@mkdir -p $(OBJS_DIR)/$(NORMAL_DIR)
	@mkdir -p $(OBJS_DIR)/$(PARSE_DIR)
	@mkdir -p $(OBJS_DIR)/$(PATTERNS_DIR)
	@mkdir -p $(OBJS_DIR)/$(RENDER_DIR)

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
