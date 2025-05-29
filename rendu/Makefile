include sources.mk

NAME         := bin/cub3D
DEBUG_NAME   := bin/cub3D_debug
CC           := cc
CFLAGS       := -Wall -Wextra -Werror -g -O0 -Iincludes -Ilibft
LDFLAGS      := -lreadline
DEBUG_FLAGS  := -DDEBUG=1
LIBFT_PATH   := libft/
LIBFT_LIB    := $(LIBFT_PATH)libft.a
MATH_LIB     := -lm

MLX_DIR      := mlx
MLX_LIB      := $(MLX_DIR)/libmlx.a

ifeq ($(shell uname), Linux)
    INCLUDES  := -I/usr/include -Imlx
    MLX_FLAGS := -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
    INCLUDES  := -I/opt/X11/include -Imlx
    MLX_FLAGS := -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

ifeq ($(shell uname -s), Darwin)
    READLINE_PREFIX := $(shell brew --prefix readline)
    CFLAGS         += -I$(READLINE_PREFIX)/include
    LDFLAGS         = -L$(READLINE_PREFIX)/lib $(LDFLAGS)
endif

BUILD_DIR    := build
BIN_DIR      := bin
OBJECTS      := $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))
DEBUG_OBJECTS:= $(addprefix $(BUILD_DIR)/, $(SRC:.c=_debug.o))

.PHONY: default all clean fclean re norm

# ANSI color codes
RESET        = \033[0m
GREEN        = \033[32m
YELLOW       = \033[33m
BLUE         = \033[34m
RED          = \033[31m
UP           = \033[A
CUT          = \033[K

default: all

all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)
	@printf "\n"
	@printf "$(GREEN)  ____    _   _    ____     _____    ____   \n$(RESET)"
	@printf "$(GREEN) / ___|  | | | |  | __ )   |___ /   |  _ \\  \n$(RESET)"
	@printf "$(GREEN)| |      | | | |  |  _ \\     |_ \\   | | | | \n$(RESET)"
	@printf "$(GREEN)| |___   | |_| |  | |_) |   ___) |  | |_| | \n$(RESET)"
	@printf "$(GREEN) \\____|   \\___/   |____/   |____/   |____/  \n$(RESET)"
	@printf "\n"
	@printf "$(YELLOW)[*] Please run the program with:$(RESET)\n"
	@printf "    $(BLUE)bin/cub3D maps/rd.cub$(RESET)\n"

# 1) mlx
$(MLX_LIB):
	@printf "$(BLUE)[1/3] Checking for MinilibX in '$(MLX_DIR)'...$(RESET)\n"
	@if [ ! -d "$(MLX_DIR)" ]; then \
	  printf "$(RED)[✗] MinilibX not found in '$(MLX_DIR)'.$(RESET)\n"; \
	  printf "$(YELLOW)Please clone it here:$(RESET)\n"; \
	  printf "  $(BLUE)git clone git@github.com:42paris/minilibx-linux.git mlx$(RESET)\n"; \
	  exit 1; \
	fi
	@printf "$(GREEN)[→] Found mlx/, building MinilibX...$(RESET)\n"
	@$(MAKE) -C $(MLX_DIR)
	@printf "$(GREEN)[✓] MinilibX built successfully$(RESET)\n\n"

# 2) libft
$(LIBFT_LIB):
	@printf "$(BLUE)[2/3] Building libft...$(RESET)\n"
	$(MAKE) bonus -C $(LIBFT_PATH)
	@printf "$(GREEN)[✓] libft built successfully$(RESET)\n\n"

# 3) program
$(NAME): $(OBJECTS)
	@printf "$(BLUE)[3/3] Compiling and linking cub3D...$(RESET)\n"
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(MLX_LIB) $(MLX_FLAGS) $(LIBFT_LIB) $(LDFLAGS) $(MATH_LIB)
	@printf "$(GREEN)[✓] $(NAME) is ready!$(RESET)\n\n"

# Debug build also depends on and links mlx
debug: $(LIBFT_LIB) $(MLX_LIB) $(DEBUG_OBJECTS)
	@printf "$(BLUE)[debug] Building debug version...$(RESET)\n"
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(DEBUG_NAME) \
	  $(DEBUG_OBJECTS) $(MLX_LIB) $(MLX_FLAGS) $(LIBFT_LIB) $(LDFLAGS)
	@printf "$(GREEN)[✓] $(DEBUG_NAME) is ready!$(RESET)\n\n"

# intermediate object rules
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%_debug.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# cleanup
clean:
	@printf "$(YELLOW)Cleaning build artifacts...$(RESET)\n"
	rm -rf $(BUILD_DIR)
	$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	@printf "$(YELLOW)Removing binaries...$(RESET)\n"
	rm -rf $(BIN_DIR)
	$(MAKE) fclean -C $(LIBFT_PATH)

re: fclean all

norm:
	norminette $(SRC) includes/cub3d.h \
	            $(LIBFT_PATH)*.h $(LIBFT_PATH)*.c \
	            $(LIBFT_PATH)gnl/*.c $(LIBFT_PATH)hashmap/*.c
