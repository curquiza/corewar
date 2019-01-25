NAME = asm

FLAG = -Wall -Wextra -Werror -g
CC = gcc $(FLAG)

SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, \
		lexer.c \
		token.c \
		token_types.c \
		\
		op.c \
		parser.c \
		parse_name.c \
		parse_comment.c \
		parse_instr.c \
		parse_params_1.c \
		parse_params_2.c \
		ast.c \
		\
		read_file.c \
		output_file.c \
		output_stdout.c \
		\
		symbol_table.c \
		encode.c \
		encode_ocp.c \
		encode_indirect.c \
		encode_direct.c \
		encode_tools.c \
		\
		option.c \
		error.c \
		tools.c \
		print_lexer.c \
		print_ast.c \
		print_symbol_table.c \
		\
		main.c )
OBJ_DIR = objs
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_H = $(LIBFT_DIR)/include

H_DIR = include
H_DIR_VM = ../vm/include
INCL = -I$(H_DIR) -I$(LIBFT_H) -I$(H_DIR_VM)


################################################################################
#################################### RULES #####################################
################################################################################

all : $(NAME)

$(LIBFT) :
	@make -C $(LIBFT_DIR)
	@printf "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

$(NAME) : $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) -o $@ $(LIBFT)
	@printf "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(H_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INCL) -c $< -o $@
	@printf "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -f $(NAME)

fclean_lib :
	@make fclean -C $(LIBFT_DIR)

fclean_all : fclean_lib fclean

clean_tests :
	@echo "cleaning old tests files..."
	@rm -f tests/input/*.cor

run_tests : clean_tests
	@printf "\033[1;33m---------\n%s\n---------\033[0m\n" "ARGUMENTS"
	@./tests/run_tests.sh
	@printf "\033[1;33m--------------------\n%s\n--------------------\033[0m\n" "ASM PARSING + OUTPUT"
	@python3 tests/main.py

re : fclean all

re_with_lib: fclean_all all
