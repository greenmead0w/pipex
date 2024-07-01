CC           = gcc
LIBFT_DIR    = pipex_libft/
LIBFT        = $(LIBFT_DIR)libft.a
CFLAGS       = -Wall -Wextra -Werror
MANDATORY_DIR = ./mandatory/
BONUS_DIR    = ./bonus/
HEADERS      = -I $(MANDATORY_DIR) -I $(BONUS_DIR) -I $(LIBFT_DIR)
NAME         = pipex
RM           = rm -rf

MANDATORY_CFILES = $(wildcard $(MANDATORY_DIR)/*.c) main.c
BONUS_CFILES = $(wildcard $(BONUS_DIR)/*.c) main_bonus.c

MANDATORY_OFILES = $(MANDATORY_CFILES:.c=.o)
BONUS_OFILES = $(BONUS_CFILES:.c=.o)

all: $(LIBFT) mandatory

mandatory: $(MANDATORY_OFILES)
	$(CC) $(CFLAGS) -o $(NAME) $(MANDATORY_OFILES) -L$(LIBFT_DIR) -lft -lm

bonus: $(LIBFT) $(BONUS_OFILES)
	$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OFILES) -L$(LIBFT_DIR) -lft -lm

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(MANDATORY_OFILES) $(BONUS_OFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all
