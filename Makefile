include sources.mk

NAME        := bin/cub3D
DEBUG_NAME  := bin/cub3D_debug
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g -O0 -Iincludes -Ilibft
LDFLAGS     := -lreadline
DEBUG_FLAGS := -DDEBUG=1
LIBFT_PATH  := libft/
LIBFT_LIB   := $(LIBFT_PATH)libft.a
MATH_LIB = -lm

MLX_DIR = mlx/
MLX_LIB = $(MLX_DIR)/libmlx.a

ifeq ($(shell uname), Linux)
    INCLUDES = -I/usr/include -Imlx
    MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
    INCLUDES = -I/opt/X11/include -Imlx
    MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

ifeq ($(shell uname -s), Darwin)
	READLINE_PREFIX := $(shell brew --prefix readline)
	CFLAGS += -I$(READLINE_PREFIX)/include
	LDFLAGS := -L$(READLINE_PREFIX)/lib $(LDFLAGS)
endif

BUILD_DIR     := build
BIN_DIR       := bin
OBJECTS       := $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))
DEBUG_OBJECTS := $(addprefix $(BUILD_DIR)/, $(SRC:.c=_debug.o))

.PHONY: default all clean fclean re norm test test_run

default: all

all: $(LIBFT_LIB) $(NAME) $(if $(SKIP_TESTS),,test_run)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%_debug.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(MLX_LIB) $(MLX_FLAGS) $(LIBFT_LIB) $(LDFLAGS) $(MATH_LIB)

debug: $(LIBFT_LIB) $(DEBUG_OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(DEBUG_NAME) $(DEBUG_OBJECTS) $(LIBFT_LIB) $(LDFLAGS)

$(MLX_LIB):
	@if [ ! -f $(MLX_LIB) ]; then \
		make -C $(MLX_DIR); \
	fi

$(LIBFT_LIB):
	$(MAKE) bonus -C $(LIBFT_PATH)

test:
	$(MAKE) -C test

test_run:
	$(MAKE) -C test run

clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) clean -C $(LIBFT_PATH)
	$(MAKE) clean -C test

fclean: clean
	rm -rf $(BIN_DIR)
	$(MAKE) fclean -C $(LIBFT_PATH)
	$(MAKE) fclean -C test

re: fclean all

norm:
	norminette $(SRC) includes/cub3d.h \
	            $(LIBFT_PATH)*.h $(LIBFT_PATH)*.c \
	            $(LIBFT_PATH)gnl/*.c $(LIBFT_PATH)hashmap/*.c
