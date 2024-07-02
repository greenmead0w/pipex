CC  = gcc
LIBFT_DIR  = pipex_libft/
LIBFT  = $(LIBFT_DIR)libft.a
CFLAGS  = -Wall -Wextra -Werror
MANDATORY_DIR = mandatory/
BONUS_DIR = bonus/
HEADERS  = -I $(MANDATORY_DIR) -I $(BONUS_DIR) -I $(LIBFT_DIR)
NAME = pipex
NAME2 = pipex_bonus
RM  = rm -rf

MANDATORY_CFILES = $(wildcard $(MANDATORY_DIR)*.c) main.c
BONUS_CFILES = $(wildcard $(BONUS_DIR)*.c) main_bonus.c

MANDATORY_OFILES = $(MANDATORY_CFILES:.c=.o)
BONUS_OFILES = $(BONUS_CFILES:.c=.o)

all: $(NAME)

bonus: check_bonus

check_bonus:
ifeq ($(wildcard $(NAME)),)
	@echo "Compiling bonus executable..."
	$(MAKE) $(NAME2)
	mv $(NAME2) $(NAME)
else
	@echo "pipex exec found: use 'make fclean' to erase mandatory, else bonus up to date"
endif

$(NAME): $(LIBFT) $(MANDATORY_OFILES)
	$(CC) $(CFLAGS) -o $(NAME) $(MANDATORY_OFILES) -L$(LIBFT_DIR) -lft -lm

$(NAME2): $(LIBFT) $(BONUS_OFILES)
	$(CC) $(CFLAGS) -o $(NAME2) $(BONUS_OFILES) -L$(LIBFT_DIR) -lft -lm

$(LIBFT):
	make -C $(LIBFT_DIR)

clean_mandatory:
	$(RM) $(MANDATORY_OFILES)

clean:
	$(RM) $(MANDATORY_OFILES) $(BONUS_OFILES)

fclean: clean
	$(RM) $(NAME) $(NAME2)

fclean_mandatory: clean_mandatory
	$(RM) $(NAME) $(NAME2)

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re


