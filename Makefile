NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra 

LIBFT = libft.a
LIBFT_DIR = libft
LIB = $(addprefix $(LIBFT_DIR)/, $(LIBFT))

MY_SOURCES = 	minishell.c \
				prompt.c \
				signal.c \
				free.c \
				builtins_1.c \
				builtins_2.c \
				builtins_check.c \
				builtins_utiles.c \
				cd.c \
				env.c \
				export.c \
				unset.c \
				utiles_env_1.c \
				utiles_env_2.c \
				utiles_export.c \
				utiles_path.c \
				setup_exec.c \
				utiles_exec.c \
				ft_sort_tab_n_add_dbq.c \
				parsing.c \
				utiles_parsing.c \
				p_fd.c \
				p_free.c \
				p_open.c \
				p_get_line.c \
				p_is.c \
				p_hdoc.c \
				p_new_str.c \
				p_quote.c \
				p_env.c \
				p_get_in_env.c \

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