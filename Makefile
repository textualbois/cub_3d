NAME = cub3d

SRCS_NAME = cub3d.c loops_hooks.c init_character.c init_world.c init_minimap.c mover.c
SRCS_PATH = ./
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

MLX_PATH = ./MLX42/
MLX_INCL = -I $(MLX_PATH)include
MLX = $(MLX_PATH)build/libmlx42.a

LIBFT_PATH = ./libft/
LIBFT_INCL = -I $(LIBFT_PATH)
LIBFT_LIB = $(LIBFT_PATH)libft.a

MLX_LIB = -L$(MLX_PATH)build -lmlx42
GLFW_LIB = -L"/usr/local/Cellar/glfw/3.3.9/lib/" -lglfw
LIBS = $(MLX_LIB) $(GLFW_LIB) -L$(LIBFT_PATH) -lft -lm

FRAMEWORKS = -framework OpenGL -framework IOKit -framework AppKit
DEPENDENCIES = $(LIBS) $(FRAMEWORKS)

OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS_NAME:.c=.o))

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(LIBFT_LIB) $(MLX) $(NAME)
	@echo "all DONE"

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)
	@echo "LIBFT DONE"

$(MLX):
	@cmake $(MLX_PATH) -B $(MLX_PATH)/build && make -C $(MLX_PATH)/build -j4
	@echo "MLX DONE"

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(DEPENDENCIES) -o $(NAME)
	@echo "NAME DONE"


$(OBJ_DIR)%.o: %.c
	@$(CC) $(CFLAGS) $(MLX_INCL) -c $< -o $@
	@echo "o:c DONE"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "OBJ_DIR DONE"

clean:
	rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_PATH)
	@echo "CLEAN DONE"

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX_PATH)build
	@make fclean -C $(LIBFT_PATH)
	@echo "fclean DONE"

re: fclean all
	@echo "re DONE"

.PHONY: all clean fclean re
