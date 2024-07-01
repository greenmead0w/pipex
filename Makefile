CC           = gcc
LIBFT_DIR    = pipex_libft/
LIBFT        = $(LIBFT_DIR)libft.a
CFLAGS       = -Wall -Wextra -Werror
PIPEX_DIR  = ./
HEADERS      = -I $(PIPEX_DIR) -I $(LIBFT_DIR)
NAME         = pipex
RM           = rm -rf

CFILES = $(wildcard $(PIPEX_DIR)/*.c)

OFILES = $(CFILES:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OFILES) -L$(LIBFT_DIR) -lft -lm

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all