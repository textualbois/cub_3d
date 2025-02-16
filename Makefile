NAME     = cub3d

SRCS     = cub3d.c loops_hooks.c init_world.c minimap_init.c \
           character_init.c movement.c mov_cursor.c draw_mini_character.c \
           window_init.c image_init.c draw.c draw_minimap.c extra_math.c \
		   minimap_view_box.c player_mini_img_centring.c \
		   draw_ray_mmap.c ray.c ray_helpers.c \
		   draw3d.c \
		   wall_collision.c \
		   ./parser/file_utils.c ./parser/libft_utils.c ./parser/parse_color.c\
		   ./parser/parse_color_utils.c ./parser/parse_line.c ./parser/parse_map.c\
		   ./parser/parse_textures_colors.c ./parser/parser_free_utils.c\
		   ./parser/string_utils.c ./parser/validate_map_utils.c\
		   ./parser/validate_map.c\
		   init_textures.c \
		   malloc_counter.c

OBJ_DIR  = obj
OBJS     = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

MLX_PATH = MLX42
MLX_BUILD_PATH = $(MLX_PATH)/build
MLX_INCLUDE  = -I $(MLX_PATH)/include
MLX42_LIBFILE = $(MLX_BUILD_PATH)/libmlx42.a

LIBFT_PATH = libft
LIBFT_LIB  = $(LIBFT_PATH)/libft.a
LIBFT_INCLUDE = -I $(LIBFT_PATH)

# Можно поправить путь к GLFW, если нужно

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)  # macOS
    LDFLAGS = -framework OpenGL -framework IOKit -framework AppKit
else  # Linux (Docker)
    LDFLAGS = -lGL -lglfw -ldl -lpthread -lX11
endif

GLFW_LIB  = -L"/usr/local/Cellar/glfw/3.3.9/lib/" -lglfw

CC      = cc
CFLAGS  = -Wall -Wextra -Werror

# FRAMEWORKS   = -framework OpenGL -framework IOKit -framework AppKit
DEPENDENCIES = -L$(MLX_BUILD_PATH) -lmlx42 $(GLFW_LIB) \
               -L$(LIBFT_PATH) -lft -lm $(LDFLAGS)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(MLX42_LIBFILE) $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(DEPENDENCIES) -o $@
	@echo "==> $(NAME) compiled!"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(MLX_INCLUDE) $(LIBFT_INCLUDE) -c $< -o $@
	@echo "Compiled $<"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(MLX42_LIBFILE):
	@if [ ! -d "$(MLX_PATH)" ]; then \
		echo "==> Cloning MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_PATH); \
	fi
	cmake $(MLX_PATH) -B $(MLX_BUILD_PATH)
	cmake --build $(MLX_BUILD_PATH) -j4
	@echo "==> MLX42 done!"

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_PATH)
	@echo "==> libft done!"

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX_PATH)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all
