NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra 

LIBFT = libft.a
LIBFT_DIR = libft
LIB = $(addprefix $(LIBFT_DIR)/, $(LIBFT))

MY_SOURCES = 	minishell.c \
				prompt.c \
				terminal.c \
				signal.c \
				env.c \
				export.c \
				unset.c \
				free.c \
				cd.c \
				builtins.c \
				utiles_builtins.c \
				ft_sort_tab_n_add_dbq.c \
				parsing.c \
				p_line.c \
				p_count.c \
				p_is.c \
				p_sep.c \
				p_hdoc.c \
				p_hdoc_2.c \
				p_env.c \
				p_quote.c \
				p_utils.c \
				p_utils_2.c \
				p_free.c \

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