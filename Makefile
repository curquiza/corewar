COREWAR_DIR = vm/
COREWAR = $(COREWAR_DIR)/corewar

ASM_DIR = asm/
ASM = $(ASM_DIR)/asm

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)/libft.a

################################################################################
#################################### RULES #####################################
################################################################################

all : $(LIBFT) $(COREWAR) $(ASM)

$(LIBFT) :
	@make -C $(LIBFT_DIR)

$(COREWAR) :
	@printf "\033[1;33m%s\033[0m\n" "== COREWAR ===================================="
	@make -C $(COREWAR_DIR)

$(ASM) :
	@printf "\033[1;33m%s\033[0m\n" "== ASM ========================================"
	@make -C $(ASM_DIR)

clean :
	@make clean -C $(COREWAR_DIR)
	@make clean -C $(ASM_DIR)

fclean : clean
	@make fclean -C $(COREWAR_DIR)
	@make fclean -C $(ASM_DIR)

fclean_lib :
	@make fclean -C $(LIBFT_DIR)

fclean_all : fclean_lib fclean

run_tests:
	@make run_tests -C $(COREWAR_DIR)
	@make run_tests -C $(ASM_DIR)

re : fclean all

re_with_lib : fclean_all all
