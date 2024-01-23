NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra

LIBFT = libft.a
LIBFT_DIR = libft
LIB = $(addprefix $(LIBFT_DIR)/, $(LIBFT))

BUILTINS = builtins_1 builtins_2 builtins_check env cd exit unset export

EXEC = setup_exec setup_pipe

MAIN = minishell

PARSING = p_env p_error p_fd p_file_name p_free p_get_in_env p_get_line p_hdoc p_is p_len_mal p_new_str p_open p_quote parsing

TOOLS = free ft_sort_tab_n_add_dbq prompt signal utiles_env_1 utiles_env_2 utiles_exec utiles_dir utiles_export utiles_parsing utiles_parsing_2 utiles_parsing_3 utiles_path builtins_utiles

MY_SOURCES = $(addsuffix .c, $(addprefix sources/builtins/, $(BUILTINS))) \
	  $(addsuffix .c, $(addprefix sources/exec/, $(EXEC))) \
	  $(addsuffix .c, $(addprefix sources/main/, $(MAIN))) \
	  $(addsuffix .c, $(addprefix sources/parsing/, $(PARSING))) \
	  $(addsuffix .c, $(addprefix sources/tools/, $(TOOLS))) \

OBJECTS = $(MY_SOURCES:c=o)

all: $(NAME)

$(NAME) : $(OBJECTS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIB) -lreadline

clean:
	rm -rf $(OBJECTS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)/$(LIBFT)

e: all clean

re : fclean all