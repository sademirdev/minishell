CC				= clang
CFLAGS			=
PROGRAM			= minishell
LIB				= lib
SRC_DIR			= src
CMD_DIR			= cmd
BIN_DIR			= bin
INC_DIR			= -Iinc -I./lib/readline/include
OBJ_DIR			= build
NAME			= $(BIN_DIR)/$(PROGRAM)
SRCS			= src/meta.c src/quote.c src/separator.c src/token.c \
	src/token_add.c src/token_append.c src/token_append_util.c src/token_util.c \
	src/util.c src/dollar.c src/dollar_util.c src/dollar_handle.c \
	src/assign_token_types.c src/lexer.c src/error.c src/exec.c src/path.c \
	src/ft_split.c src/redirect.c src/redirect_handle.c \
	src/built_in.c src/cd.c src/echo.c src/env.c src/exit.c src/export.c \
	src/pwd.c src/syntax_check_util.c src/syntax_check.c src/unset.c \
	src/signal.c src/dispose.c src/print_util.c src/token_util2.c src/exec_multi.c \
	src/util2.c src/util3.c src/quote_util.c src/exec_single.c src/exec_util.c

OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CMD				= $(CMD_DIR)/$(PROGRAM).c
DEPENDENCIES	=
RM				= rm -rf
RLFLAGS			= -L./lib/readline/lib -I./lib/readline/include/readline -lreadline
DIR				= $(shell echo $(PWD))
READLINE		= ./lib/readline/lib/libreadline.a

F_INFO_LIB_LINUX = -ltinfo

MURMUR_EVAL = $(LIB)/murmur.eval-master/murmur_eval/build/libmurmureval.a
# os = ${shell uname -s}
# ifeq '$(os)' 'Darwin'
# NPROCS = $(shell sysctl -n hw.ncpu)
# else ifeq '$(os)' 'Linux'
# NPROCS = $(shell nproc)
# MAKEFLAGS += -j$(NPROCS)

w = 1
ifeq '$(w)' '1'
CFLAGS += -Wextra -Werror -Wall
endif

debug = 1
ifeq '$(debug)' '1'
CFLAGS += -g
endif

# asan = 1
# ifeq '$(asan)' '1'
# CFLAGS += -fsanitize=address
# # CFLAGS += -fsanitize=thread
# endif

test = 0
ifeq '$(test)' '1'
./$(attest) .
endif

all: $(DEPENDENCIES) $(READLINE)
	@mkdir -p bin
	@$(MAKE) $(NAME)

$(READLINE):
	@curl -O https://ftp.gnu.org/gnu/readline/readline-8.2-rc1.tar.gz
	@tar -xvf readline-8.2-rc1.tar.gz
	@$(RM) readline-8.2-rc1.tar.gz
	@cd readline-8.2-rc1 && ./configure --prefix=$(DIR)/lib/readline && make && make install
	@$(RM) readline-8.2-rc1

$(MURMUR_EVAL):
	@curl -L -O https://github.com/murmurlab/murmur.eval/archive/refs/heads/master.zip
	@unzip -d $(LIB) master.zip
	@$(RM) master.zip
	@make -C $(LIB)/murmur.eval-master/murmur_eval

$(NAME): $(CMD) $(OBJS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(RLFLAGS) $(F_INFO_LIB_LINUX) $(INC_DIR) $(CMD) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_DIR)  -c $< -o $@

r: all
	./$(NAME)

clean:
	$(RM) $(OBJS)
c: clean

fclean: clean
	$(RM) $(NAME) & wait
	# $(RM) lib/readline
f: fclean

re: fclean
	$(MAKE) all

mt: $(MURMUR_EVAL)
	clang test/handle_dollar_test.c src/*.c test/libs/tin/equal_primitive.c lib/readline/lib/libreadline.dylib lib/readline/lib/libhistory.dylib -I lib/murmur.eval-master/murmur_eval/incs/ -I inc/ -I lib/readline/include/ -L ./lib/readline/lib/ -lreadline lib/murmur.eval-master/murmur_eval/build/libmurmureval.a -D TEST=1 && ./a.out

t:
	@mkdir -p bin
	$(CC) $(CFLAGS) $(RLFLAGS) \
		$(INC_DIR) \
		-Itest/libs \
		test/libs/tin/equal_primitive.c \
		test/tests/asdsec_tests/separator_test.c \
		test/main.c \
		-D TEST=1 $(SRCS) -o bin/test
	@./bin/test

.PHONY: all clean fclean re run
