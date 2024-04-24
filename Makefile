CC						= clang
CFLAGS				=
PROGRAM				= minishell
LIB						=	lib
SRC_DIR				=	src
CMD_DIR				=	cmd
BIN_DIR				=	bin
INC_DIR				= -Iinc
OBJ_DIR				=	build
NAME					= $(BIN_DIR)/$(PROGRAM)
SRCS					= src/meta.c src/quote.c src/separator.c src/token.c \
	src/token_add.c src/token_append.c src/token_append_util.c src/token_util.c \
	src/util.c src/dollar.c src/dollar_util.c src/dollar_handle.c src/assign_token_types.c 
OBJS					= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CMD						= $(CMD_DIR)/$(PROGRAM).c
DEPENDENCIES	=

os = ${shell uname -s}
ifeq '$(os)' 'Darwin'
NPROCS = $(shell sysctl -n hw.ncpu)
else ifeq '$(os)' 'Linux'
NPROCS = $(shell nproc)
endif
# MAKEFLAGS += -j$(NPROCS)

w = 1
ifeq '$(w)' '1'
CFLAGS += -Wextra -Werror -Wall
endif

debug = 1
ifeq '$(debug)' '1'
CFLAGS += -g
endif

asan = 1
ifeq '$(asan)' '1'
CFLAGS += -fsanitize=address
# CFLAGS += -fsanitize=thread
endif

test = 0
ifeq '$(test)' '1'
./$(attest) .
endif

all: $(DEPENDENCIES)
	@mkdir -p bin
	@$(MAKE) $(NAME)

$(NAME): $(CMD) $(OBJS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) $(CMD) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

r: all
	./$(NAME)

clean:
	$(RM) $(OBJS)
c: clean

fclean: clean
	$(RM) $(NAME) & wait
f: fclean

re: fclean
	$(MAKE) all

# t:
# 	@mkdir -p bin
# 	@$(CC) $(CFLAGS) $(INC_DIR) test/separator_test.c src/separator.c src/util.c src/token.c -o bin/separator_test
# 	@./bin/separator_test
t:
	@mkdir -p bin
	@$(CC) $(CFLAGS) $(INC_DIR) test/testing.c test/token_test.c test/dollar_test.c test/equal_primitive.c $(SRCS) -o bin/test
	@./bin/test

.PHONY: all clean fclean re run
