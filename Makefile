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
SRCS					= src/spacer.c
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
	@$(MAKE) $(NAME)

$(NAME): $(CMD) $(OBJS)
	$(CC) $(CFLAGS) $(INC_DIR) $(CMD) $(OBJS) -o $(NAME)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(INC_DIR) -c $(SRCS) -o $(OBJS)

run: all
	@echo "\n\x1B[32m===================================program======================================\n\x1B[0m"
	./$(NAME)

clean:
	$(RM) $(OBJS)
c: clean

fclean: clean
	$(RM) $(NAME) & wait
f: fclean

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re run
