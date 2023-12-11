NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra 

LIBFT = libft.a
LIBFT_DIR = libft
LIB = $(addprefix $(LIBFT_DIR)/, $(LIBFT))

MY_SOURCES = parsing.c \
		free_parsing.c \

SOURCES_DIR = sources
SOURCES = $(addprefix $(SOURCES_DIR)/, $(MY_SOURCES))

MY_OBJECTS = $(MY_SOURCES:.c=.o)
OBJECTS_DIR = object
OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(MY_OBJECTS))

all: $(NAME)

$(NAME) : $(OBJECTS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIB)

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
	@mkdir -p $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)/$(LIBFT)

re : fclean all