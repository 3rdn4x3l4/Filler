# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alagache <alagache@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/27 11:23:02 by alagache          #+#    #+#              #
#    Updated: 2020/04/27 11:31:33 by alagache         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= alagache.filler

LIBDIR= libft

LIBA= $(LIBDIR)/libft.a

CFLAGS= -Wall -Werror -Wextra 
#CFLAGS += -g -fsanitize=address -fno-omit-frame-pointer

HEADER= includes/
LIBHEADER= $(LIBDIR)/includes

CC= clang

SRCS=	main.c\
		init_parse.c\
		tools.c\
		parse.c\
		print.c\
		init_arrs.c\
		fill_arrs.c\
		heatmap.c\
		diff.c\
		offset.c\
		read.c\
		#.c\

OBJDIR= obj

OBJ= $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) $(LIBA)
	$(CC) $(CFLAGS) -I $(HEADER) -I $(LIBHEADER) -o $(NAME) $^
	echo "filler build complete"

$(OBJDIR):
	mkdir -p $(OBJDIR)

obj/%.o : srcs/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I $(HEADER) -I $(LIBHEADER) -o $@ -c $<

$(LIBA): .FORCE
	$(MAKE) -s -C libft

.FORCE:

%.o : %.c
	$(CC) -I $(LIBDIR) $(CFLAGS) -o $@ -c $<

clean:
		$(RM) -rf $(OBJDIR)
		echo "filler objects cleaned"
		$(MAKE) clean -s -C $(LIBDIR)

fclean:
		$(MAKE) fclean -s -C $(LIBDIR)
		$(RM) -rf $(NAME) $(OBJDIR)
		echo "filler objects cleaned"
		echo "filler project cleaned"

re: fclean all

.PHONY: all clean fclean re .FORCE
.SILENT: all clean fclean re .FORCE $(NAME) $(OBJ) $(LIBA) $(OBJDIR)
