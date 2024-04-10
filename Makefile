# declare makefile variables
NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

# libft path and flags
LIBFT = libft.a
LIB_DIR = ./libft
LIB_FLAGS = -L $(LIB_DIR) -lft
INC = -I ./includes

#------------------------------------------------------------------------

# mlx path and flags
ifeq ($(shell uname), Linux)
	MLX_DIR = ./mlx_linux
	MLX_NAME = libmlx_Linux.a
	MLX_LIB = $(addprefix $(MLX_DIR)/, $(MLX_NAME))
	MLX_INC = -I/usr/include -I $(MLX_DIR)
	MLX_FLAGS = -L $(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 $(MLX_INC)
else
	MLX_DIR = ./mlx_macos
	MLX_NAME = libmlx.dylib
	MLX_LIB = $(addprefix $(MLX_DIR)/, $(MLX_NAME))
	MLX_INC = -I/opt/X11/include -I $(MLX_DIR)
	MLX_FLAGS = -L $(MLX_DIR) -lmlx -L/usr/X11/lib -lXext -lX11 \
	-framework OpenGL -framework AppKit $(MLX_INC)
endif

#------------------------------------------------------------------------

# cub3d targets
# init
INIT = main_yx.c
INIT_SRCS = $(addprefix srcs/init/, $(INIT))

GRAPHICS = image_utils.c
GRAPHICS_SRCS = $(addprefix srcs/graphics/, $(GRAPHICS))

# temp; unsure where to put these yet
MISC = movement.c exit_utils.c
MISC_SRCS = $(addprefix srcs/misc/, $(MISC))

SRCS = $(INIT_SRCS) $(GRAPHICS_SRCS) $(MISC_SRCS)
# SRCS = srcs/main.c
OBJS = $(SRCS:.c=.o)

#------------------------------------------------------------------------

# colours
GREEN = \033[0;32m
B_GREEN = \033[1;32m
BROWN = \033[0;33m
B_BROWN = \033[1;33m
END = \033[0m

#------------------------------------------------------------------------

# RULES
# all = create library from sub-make

all: $(MLX_LIB) $(LIBFT) mandatory

mandatory: $(OBJS) $(MLX_LIB) $(LIBFT)
	@echo "\n$(B_BROWN)[ COMPILING: $(NAME) ]$(END)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB_FLAGS) $(MLX_FLAGS) $(INC)
	@echo "$(B_GREEN)$(NAME) compiled.$(END)"

$(OBJS): %.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "\t$(BROWN)$< compiled.$(END)"

$(LIBFT):
	@echo "\n$(B_BROWN)[ COMPILING: $(LIBFT) ]$(END)"
	@make -s -C $(LIB_DIR)

$(MLX_LIB):
	@echo "\n$(B_BROWN)[ COMPILING: $(MLX_LIB) ]$(END)"
	@make -s -C $(MLX_DIR)
	@cp $(MLX_LIB) ./
	@echo "$(B_GREEN)$(MLX_LIB) compiled.$(END)"

# remove temporary generated files
clean:
	@$(RM) $(OBJS)
	@make clean -s -C $(LIB_DIR)
	@make clean -s -C $(MLX_DIR)

# remove library and executable file
fclean: clean
	@$(RM) $(NAME) && $(RM) $(MLX_NAME)
	@cd $(LIB_DIR) && $(RM) $(LIBFT)
	@echo "$(B_GREEN)Removed $(NAME), $(MLX_NAME) and $(LIBFT).$(END)"

re: fclean all

#------------------------------------------------------------------------

# declare phony
.PHONY: all bonus clean fclean mandatory re
