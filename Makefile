CC					= clang
CFLAGS			=
PROGRAM			= minishell
SRC_DIR			= src
CMD_DIR			= cmd
BIN_DIR			= bin
INC_DIR			= -Iinc -I./lib/readline/include
OBJ_DIR			= build
NAME				= $(BIN_DIR)/$(PROGRAM)
SRCS				= src/meta.c src/quote.c src/separator.c src/token.c \
	src/token_add.c src/token_append.c src/token_append_util.c src/token_util.c \
	src/util.c src/dollar.c src/dollar_util.c src/dollar_handle.c \
	src/assign_token_types.c src/lexer.c src/error.c src/exec.c src/path.c \
	src/ft_split.c src/redirect.c src/redirect_handle.c \
	src/built_in.c src/cd.c src/echo.c src/env.c src/exit.c src/export.c \
	src/pwd.c src/syntax_check_util.c src/syntax_check.c src/unset.c \
	src/signal.c src/dispose.c src/print_util.c src/token_util2.c src/exec_multi.c \
	src/util2.c src/util3.c src/quote_util.c src/exec_single.c src/exec_util.c \
	src/built_in_util.c src/pipe_fds.c

OBJS					= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CMD						= $(CMD_DIR)/$(PROGRAM).c
RM						= rm -rf
RLFLAGS				= -L./lib/readline/lib -I./lib/readline/include/readline -lreadline
DIR						= $(shell echo $(PWD))
READLINE			= ./lib/readline/lib/libreadline.a

w = 1
ifeq '$(w)' '1'
CFLAGS += -Wextra -Werror -Wall
endif

debug = 1
ifeq '$(debug)' '1'
CFLAGS += -g
endif

asan = 0
ifeq '$(asan)' '1'
CFLAGS += -fsanitize=address
endif

all: $(READLINE)
	@mkdir -p bin
	@$(MAKE) $(NAME)

$(READLINE):
	@curl -O https://ftp.gnu.org/gnu/readline/readline-8.2-rc1.tar.gz
	@tar -xvf readline-8.2-rc1.tar.gz
	@$(RM) readline-8.2-rc1.tar.gz
	@cd readline-8.2-rc1 && ./configure --prefix=$(DIR)/lib/readline && make && make install
	@$(RM) readline-8.2-rc1

$(NAME): $(CMD) $(OBJS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(RLFLAGS) $(INC_DIR) $(CMD) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) & wait

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
