NAME = cub3d

SRCS_NAME = cub3d.c loops_hooks.c init_world.c minimap_init.c \
			character_init.c movement.c \
			draw_mini_character.c window_init.c \
			image_init.c #fps.c  \

SRCS_PATH = ./
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

# Пути и параметры MLX42
MLX_PATH = ./MLX42/
MLX_BUILD_PATH = $(MLX_PATH)build/
MLX_INCLUDE = -I $(MLX_PATH)include
MLX_LIB = -L$(MLX_BUILD_PATH) -lmlx42

# GLFW для MLX42
GLFW_LIB = -L"/usr/local/Cellar/glfw/3.3.9/lib/" -lglfw
GLFW_REPO = https://github.com/glfw/glfw.git

# Параметры библиотеки Libft
LIBFT_PATH = ./libft/
LIBFT_INCLUDE = -I $(LIBFT_PATH)
LIBFT_LIB = $(LIBFT_PATH)libft.a

LIBS = $(MLX_LIB) $(GLFW_LIB) -L$(LIBFT_PATH) -lft -lm
FRAMEWORKS = -framework OpenGL -framework IOKit -framework AppKit
DEPENDENCIES = $(LIBS) $(FRAMEWORKS)

OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS_NAME:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(LIBFT_LIB) mlx42 $(NAME)
	@echo "all DONE"

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)
	@echo "LIBFT DONE"

mlx42:
	@if [ ! -d $(MLX_PATH) ]; then \
		echo "Cloning MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_PATH); \
	fi
	@cmake $(MLX_PATH) -B $(MLX_BUILD_PATH) && cmake --build $(MLX_BUILD_PATH) -j4
	@echo "MLX42 DONE"

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(DEPENDENCIES) -o $(NAME)
	@echo "$(NAME) DONE"

$(OBJ_DIR)%.o: %.c
	@$(CC) $(CFLAGS) $(MLX_INCLUDE) -c $< -o $@
	@echo "Compiled $<"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "OBJ_DIR CREATED"

clean:
	rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_PATH)
	@echo "CLEAN DONE"

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX_PATH)
	@make fclean -C $(LIBFT_PATH)
	@echo "Fclean DONE: MLX42 and $(NAME) removed"

re: fclean all
	@echo "REBUILD DONE"

.PHONY: all clean fclean re mlx42
