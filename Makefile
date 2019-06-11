# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sregnard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 14:51:18 by sregnard          #+#    #+#              #
#    Updated: 2019/06/11 17:32:36 by sregnard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_IN					=	lem-in

LIBDIR					=	libft/
LIBFT					=	$(LIBDIR)libft.a

HEADDIR					=	includes/
HEADERS					=	-I $(HEADDIR)
HEADERS					+=	-I $(LIBDIR)$(HEADDIR)

DEPENDENCIES			=	lem_in.h

SRCDIR					=	srcs/
OBJDIR					=	objs/

SRCNAME					=	lem_in.c \
							room.c \
							link.c \
							ant.c
SRC						:=	$(addprefix $(SRCDIR), $(SRCNAME))
OBJ						=	$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

CC						=	gcc	
CFLAGS					=	-Wall -Wextra -Werror
CFLAGS					=	-g3

all						:	$(LIBFT) $(LEM_IN)
	@make -C $(LIBDIR)

$(LIBFT)				:
	@make -C $(LIBDIR)

$(LEM_IN)				:	$(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(HEADERS) $(LIBFT) -o $@ $(OBJ)

$(OBJDIR)%.o			:	$(SRCDIR)%.c
	@mkdir -p $(OBJDIR);
	$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

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
