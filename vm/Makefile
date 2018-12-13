NAME = corewar

OS = $(shell uname)
ifeq ($(OS), Darwin)
   # MacOs
   FLAG = -Wall -Wextra -Werror
else
   # Linux
   FLAG = -Wall -Wextra
endif

CC = gcc $(FLAG)

SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, \
	  usage.c \
	  conversion.c \
	  file_syscall.c \
	  clean.c \
	  utils.c \
	  parsing_manage_flag.c \
	  parsing_manage_player.c \
	  parsing_read_bin1.c \
	  parsing_read_bin2.c \
	  parsing_base.c \
	  op.c \
	  op_parsing.c \
	  op_live.c \
	  op_and.c \
	  op_zjmp.c \
	  op_sti.c \
	  vm_setup.c \
	  dump_flag.c \
	  verbose_flag.c \
	  manage_end_of_period.c \
	  exec_all_processus.c \
	  visu_init.c \
	  visu_display.c \
	  visu_create_subwin.c \
	  visu_getkey.c \
	  main.c)

OBJ_DIR = objs
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_H = $(LIBFT_DIR)/include

NCURSES = -lncurses

H_DIR = include
INCL = -I$(H_DIR) -I$(LIBFT_H)


################################################################################
#################################### RULES #####################################
################################################################################

all : $(NAME)

$(LIBFT) :
	@make -C $(LIBFT_DIR)
	@printf "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

$(NAME) : $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) -o $@ $(LIBFT) $(NCURSES)
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

run_tests :
	@printf "\033[1;33m----------\n%s\n----------\033[0m\n" "VM PARSING"
	@tests/parsing.sh
	@printf "\033[1;33m------------\n%s\n------------\033[0m\n" "VM EXECUTION"
	@tests/vm_diff.sh

re : fclean all

re_with_lib: fclean_all all
