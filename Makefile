include sources.mk

NAME = bin/cub3D
DEBUG_NAME = bin/cub3D_debug

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes -Ilibft
LDFLAGS = -lreadline
DEBUG_FLAGS = -DDEBUG=1
LIBFT_PATH = libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

ifeq ($(shell uname -s), Darwin)
	READLINE_PREFIX := $(shell brew --prefix readline)
	CFLAGS += -I$(READLINE_PREFIX)/include
	LDFLAGS := -L$(READLINE_PREFIX)/lib $(LDFLAGS)
endif

BUILD_DIR = build
BIN_DIR = bin
OBJECTS = $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))
DEBUG_OBJECTS = $(addprefix $(BUILD_DIR)/, $(SRC:.c=_debug.o))

all: $(LIBFT_LIB) $(NAME)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%_debug.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT_LIB) $(LDFLAGS)

debug: $(LIBFT_LIB) $(DEBUG_OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(DEBUG_NAME) $(DEBUG_OBJECTS) $(LIBFT_LIB) $(LDFLAGS)

$(OBJECTS): includes/cub3d.h

$(LIBFT_LIB):
	make bonus -C $(LIBFT_PATH)

# test:
	# make -C test

# test_run:
	# make -C test run

clean:
	rm -rf $(BUILD_DIR)
	make clean -C $(LIBFT_PATH)
	# make clean -C test

fclean: clean
	rm -rf $(BIN_DIR)
	make fclean -C $(LIBFT_PATH)

re: fclean all


norm:
	norminette $(SRC) includes/cub3d.h $(LIBFT_PATH)*.h $(LIBFT_PATH)*.c $(LIBFT_PATH)gnl/*.c $(LIBFT_PATH)hashmap/*.c

.PHONY: all fclean clean re norm test test_run
