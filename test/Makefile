CC        := cc
# use pkg-config for Criterion
#CFLAGS    := -Wall -Wextra -Werror -g --coverage \
#             $(shell pkg-config --cflags criterion) \
#             -I../includes
#LDFLAGS   := --coverage \
#             $(shell pkg-config --libs criterion)

CFLAGS = -Wall -Wextra -Werror -g -O0 --coverage -I/usr/local/include -I../includes
LDFLAGS = --coverage -lcriterion

BUILD_DIR := build
BIN_DIR   := bin
OUTPUT    := $(BIN_DIR)/test_suite

LIBFT_PATH := ../libft/
LIBFT_LIB  := $(LIBFT_PATH)libft.a

SRCS := \
    ../src/parser/configuration_line_parser.c \
		../src/parser/configuration_line_parser_utils.c \
	   ../libft/arraylist/ft_array_list_add.c \
	   ../libft/arraylist/ft_array_list_create.c \
	   ../libft/arraylist/ft_array_list_get.c \
    ../libft/arraylist/ft_array_list_remove.c

TESTS := unit/test_configuration_line_parser.c

.PHONY: all test run clean fclean coverage

all: test

# ensure libft is built
$(LIBFT_LIB):
	$(MAKE) bonus -C $(LIBFT_PATH)

# build & link
test: $(LIBFT_LIB) $(TESTS)
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRCS) $(TESTS) \
	      -o $(OUTPUT) $(LIBFT_LIB) $(LDFLAGS)

# run tests with verbose output
run: test
	$(OUTPUT) --verbose

# remove objects, bins, coverage data
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	find . -name '*.gcda' -o -name '*.gcno' | xargs rm -f || true

# remove reports
fclean: clean
	rm -f coverage.html

# generate coverage report
coverage: test
	$(OUTPUT)
	gcovr --exclude-unreachable-branches \
	      --exclude-throw-branches \
	      --html --html-details \
	      -o coverage.html
