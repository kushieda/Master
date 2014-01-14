# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/04 22:16:07 by jyim              #+#    #+#              #
#    Updated: 2014/01/12 06:48:46 by jyim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

COMPIL = -lmlx -lXext -lX11
LIBCOMPIL = -L /opt/X11/lib/
SRC = main.c parse.c raycaster.c strsplit.c strtrim.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	gcc -o wolf3d $(LIBCOMPIL) $(COMPIL) $(OBJ) -L libft/ -lft

%.o: %.c
	gcc -Wall -Werror -Wextra -c -I libft/ $<

clean:
	/bin/rm $(OBJ)
	make -C libft/ clean

fclean:
	/bin/rm -f $(OBJ)
	/bin/rm -f $(NAME)
	make -C libft/ fclean

re: fclean all
