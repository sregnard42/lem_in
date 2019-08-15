# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 14:51:18 by sregnard          #+#    #+#              #
#    Updated: 2019/08/15 13:51:16 by sregnard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_IN					=	lem-in

LIBDIR					=	libft/
LIBFT					=	$(LIBDIR)libft.a

HEADDIR					=	includes/
INCLUDES				=	-I $(HEADDIR)
INCLUDES				+=	-I $(LIBDIR)$(HEADDIR)

HEADERS					=	lem_in.h	\
							ant.h		\
							link.h		\
							relative.h	\
							path.h		\
							queue.h		\
							room.h
DEPENDENCIES			:=	$(addprefix $(HEADDIR), $(HEADERS))

SRCDIR					=	srcs/
OBJDIR					=	objs/

SRCNAME					=	lem_in.c		\
							parsing.c		\
							parsing_rooms.c	\
							parsing_links.c	\
							matrice.c		\
							error.c			\
							room.c			\
							link.c			\
							ant.c			\
							path.c			\
							path_list.c		\
							queue.c			\
							bfs.c			\
							print_lem_in.c	\
							free.c			\
							tree.c			\
							relative.c		\
							paths_opti.c 	\
							repartition.c
SRC						:=	$(addprefix $(SRCDIR), $(SRCNAME))
OBJ						=	$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

CC						=	gcc
CFLAGS					=	-Wall -Wextra -Werror
XFLAGS					=	-g3

all						:	$(LIBFT) $(LEM_IN)

$(LIBFT)				:
	@make -C $(LIBDIR)

$(LEM_IN)				:	$(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(XFLAGS) $(INCLUDES) $(LIBFT) -o $@ $(OBJ)

$(OBJDIR)%.o			:	$(SRCDIR)%.c $(DEPENDENCIES)
	@mkdir -p $(OBJDIR);
	$(CC) $(CFLAGS) $(XFLAGS) $(INCLUDES) -o $@ -c $<

clean					:
	rm -rf $(OBJDIR)
	make clean -C $(LIBDIR)

fclean					:	clean
	rm -rf $(LEM_IN)
	make fclean -C $(LIBDIR)

re						:	fclean	all

li						:
	rm -rf objs/
	make
