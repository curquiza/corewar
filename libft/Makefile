NAME = libft.a

FLAG = -Wall -Wextra -Werror
CC = gcc $(FLAG)

SRC = srcs
C_DIR = $(addprefix $(SRC)/, \
		ft \
		gnl \
		ft_printf) 

C_FILES = $(addprefix $(SRC)/, \
		  $(FT) \
		  $(GNL) \
		  $(FT_PRINTF))

FT = $(addprefix ft/, \
	  ft_memset.c \
	  ft_bzero.c \
	  ft_memcpy.c \
	  ft_memccpy.c \
	  ft_memmove.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_strlen.c \
	  ft_strdup.c \
	  ft_strcpy.c \
	  ft_strncpy.c \
	  ft_strcat.c \
	  ft_strncat.c \
	  ft_strlcat.c \
	  ft_strchr.c \
	  ft_strrchr.c \
	  ft_strstr.c \
	  ft_strnstr.c \
	  ft_strcmp.c \
	  ft_strncmp.c \
	  ft_atoi.c \
	  ft_isalpha.c \
	  ft_isdigit.c \
	  ft_isalnum.c \
	  ft_isascii.c \
	  ft_isprint.c \
	  ft_toupper.c \
	  ft_tolower.c \
	  ft_memalloc.c \
	  ft_memdel.c \
	  ft_strnew.c \
	  ft_strdel.c \
	  ft_strclr.c \
	  ft_striter.c \
	  ft_striteri.c \
	  ft_strmap.c \
	  ft_strmapi.c \
	  ft_strequ.c \
	  ft_strnequ.c \
	  ft_strsub.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_strsplit.c \
	  ft_itoa.c \
	  ft_putchar.c \
	  ft_putstr.c \
	  ft_putendl.c \
	  ft_putnbr.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_lstnew.c \
	  ft_lstdelone.c \
	  ft_lstdel.c \
	  ft_lstadd.c \
	  ft_lstiter.c \
	  ft_lstmap.c \
	  ft_countwords.c \
	  ft_intlen.c \
	  ft_lstlen.c \
	  ft_lstadd_back.c \
	  ft_lstlast.c \
	  ft_lstat.c \
	  ft_intlen_base.c \
	  ft_itoa_base.c \
	  ft_putnbr_endl.c \
	  ft_puttab.c \
	  ft_putinttab.c \
	  ft_strdeldup.c \
	  ft_convbase.c \
	  ft_tablen.c \
	  ft_sorttab_ascii.c \
	  ft_ullintlen.c \
	  ft_putstr_col.c \
	  ft_putendl_col.c \
	  ft_putnbr_col.c \
	  ft_tabdup.c \
	  ft_tabdel.c \
	  ft_strjoin3.c \
	  ft_exit.c \
	  ft_putendl2_fd.c \
	  ft_putendl3_fd.c \
	  ft_strupper.c \
	  ft_strlower.c \
	  ft_putnbr2.c \
	  ft_memjoin.c)

GNL = $(addprefix gnl/, \
	  get_next_line.c)

FT_PRINTF = $(addprefix ft_printf/, \
		  arg_lst_func.c \
		  parsing.c \
		  parsing_tools.c \
		  numeric_to_str.c \
		  conv_x_bigx.c \
		  conv_o_bigo.c \
		  conv_u_bigu.c \
		  conv_d_i_bigd.c \
		  conv_p.c \
		  conv_c.c \
		  conv_bigc.c \
		  conv_s.c \
		  conv_bigs.c \
		  conv_percent.c \
		  conv_b.c \
		  sign_flags.c \
		  precision.c \
		  padding.c \
		  display.c \
		  ft_printf.c) 

OBJ = objs/
O_DIR = $(C_DIR:$(SRC)/%=$(OBJ)/%)
O_FILES = $(C_FILES:$(SRC)/%.c=$(OBJ)/%.o)

H_DIR = includes
INCL = -I$(H_DIR)

all : $(NAME)

$(NAME) : $(O_FILES) 
	@ar rc $@ $^
	@ranlib $@

$(OBJ)/%.o: $(SRC)/%.c $(H_DIR)
	@mkdir -p $(OBJ) $(O_DIR)
	@$(CC) $(INCL) -c $< -o $@

clean :
	@rm -rf $(OBJ)
	@#echo "Make $@_libft : \033[1;33mOK\033[0m"

fclean : clean
	@rm -f $(NAME)
	@#echo "Make $@_libft : \033[1;33mOK\033[0m"

re : fclean all
