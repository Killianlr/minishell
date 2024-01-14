NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra 

LIBFT = libft.a
LIBFT_DIR = libft
LIB = $(addprefix $(LIBFT_DIR)/, $(LIBFT))

MY_SOURCES = 	minishell.c \
				prompt.c \
				signal.c \
				env.c \
				export.c \
				utiles_export.c \
				unset.c \
				free.c \
				cd.c \
				builtins.c \
				builtins_2.c \
				utiles_builtins.c \
				utiles_env.c \
				ft_sort_tab_n_add_dbq.c \
				parsing.c \
				p_line.c \
				p_copy_str.c \
				p_count.c \
				p_is.c \
				p_sep.c \
				p_hdoc.c \
				p_hdoc_2.c \
				p_env.c \
				p_get_in_env.c \
				p_quote.c \
				p_utils.c \
				p_utils_2.c \
				p_free.c \
				p_new_str.c \
				ft_exec.c \
				utiles_exec.c \
				error.c \
				setup_exec.c \
				ft_open.c \
				utiles_path.c \
				main.c \
				builtins_exec.c \
				utiles_env_2.c \
				new_arg.c \
				open_to_free.c \

SOURCES_DIR = sources
SOURCES = $(addprefix $(SOURCES_DIR)/, $(MY_SOURCES))

MY_OBJECTS = $(MY_SOURCES:.c=.o)
OBJECTS_DIR = object
OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(MY_OBJECTS))

all: $(NAME)

$(NAME) : $(OBJECTS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIB) -lreadline

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
	@mkdir -p $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)/$(LIBFT)

e: all clean

re : fclean all