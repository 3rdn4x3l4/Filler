NAME= alagache.filler

LIBDIR= libft

LIBA= $(LIBDIR)/libft.a

CFLAGS= -Wall -Werror -Wextra

CC= clang

SRCS= main.c\
	  parsing.c\
	  tools.c\

OBJ= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBA)
	$(CC) $(CFLAGS) -o $(NAME) $^
	echo "filler build complete"

$(LIBA): .FORCE
	$(MAKE) -C libft

.FORCE:

%.o : %.c
	$(CC) -I $(LIBDIR) $(CFLAGS) -o $@ -c $<

clean:
		$(RM) -rf $(OBJ)
		echo "filler objects cleaned"
		$(MAKE) clean -C $(LIBDIR)

fclean:
		$(MAKE) fclean -s -C $(LIBDIR)
		$(RM) -f $(NAME) $(OBJ)
		echo "filler objects cleaned"
		echo "filler project cleaned"

re: fclean all

.PHONY: all clean fclean re .FORCE
.SILENT: all clean fclean re .FORCE $(OBJ) $(NAME)
