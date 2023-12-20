NAME = essai
CC = cc
CFLAGS = -Wall -Werror -Wextra

LIBFT = libft.a
LIBFT_DIR = libft
LIB = $(addprefix $(LIBFT_DIR)/, $(LIBFT))

SOURCES = ft_exec.c \
			utiles_exec.c \
			free_pipex.c \
			pipex.c \
			command_pipex.c \

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)


$(NAME) : $(OBJECTS)
		make -C $(LIBFT_DIR)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIB)

clean:
		rm -rf $(OBJECTS)
		make clean -C $(LIBFT_DIR)

fclean: clean
		rm -rf $(NAME)
		rm -f $(LIBFT_DIR)/$(LIBFT)