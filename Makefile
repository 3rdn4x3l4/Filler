NAME= alagache.filler

SRCS= main.c\
	  parsing.c\
	  tools.c\


OBJ= $(SRCS:.c=.o)

LIBDIR= libft

LIBA= $(LIBDIR)/libft.a

CFLAGS= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@make -s -C $(LIBDIR)
	@gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LIBA)
	@echo "filler build complete"

%.o : %.c
	@gcc -I $(LIBDIR) $(CFLAGS) -o $@ -c $<

clean:
		@rm -rf $(OBJ)
		@echo "filler objects cleaned"
		@make clean -C $(LIBDIR)

fclean:
		@make fclean -s -C $(LIBDIR)
		@rm -f $(NAME)
		@rm -rf $(OBJ)
		@echo "filler objects cleaned"
		@echo "filler project cleaned"

re: fclean all

.PHONY: all clean fclean re
