# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sregnard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 14:51:18 by sregnard          #+#    #+#              #
#    Updated: 2019/06/11 14:53:39 by sregnard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_IN					=	lem-in

LIBDIR					=	libft/
LIBFT					=	$(LIBDIR)libft.a

HEADDIR					=	includes/
HEADERS					=	-I $(HEADDIR)
HEADERS					+=	-I $(LIBDIR)$(HEADDIR)

DEPENDENCIES			=	push_swap.h

SRCDIR					=	srcs/
OBJDIR					=	objs/

SRCNAME					=	lem_in.c
SRC						:=	$(addprefix $(SRCDIR), $(SRCNAME))
OBJ						=	$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

CC						=	gcc	
CFLAGS					=	-Wall -Wextra -Werror

all						:	$(LIBFT) $(CHECKER) $(PUSH_SWAP)
	@make -C $(LIBDIR)

$(LIBFT)				:
	@make -C $(LIBDIR)

$(CHECKER)				:	$(LIBFT) $(OBJ_CHECK) $(OBJ)
	$(CC) $(CFLAGS) $(HEADERS) $(LIBFT) -o $@ $(OBJ) $(OBJ_CHECK)

$(PUSH_SWAP)			:	$(LIBFT) $(OBJ_PUSH) $(OBJ)
	$(CC) $(CFLAGS) $(HEADERS) $(LIBFT) -o $@ $(OBJ) $(OBJ_PUSH)

$(OBJDIR_CHECK)%.o		:	$(SRCDIR_CHECK)%.c
	@mkdir -p $(OBJDIR_CHECK);
	$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

$(OBJDIR_PUSH)%.o		:	$(SRCDIR_PUSH)%.c
	@mkdir -p $(OBJDIR_PUSH);
	$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

$(OBJDIR)%.o			:	$(SRCDIR)%.c
	@mkdir -p $(OBJDIR);
	$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

clean					:
	rm -rf $(OBJDIR)
	make clean -C $(LIBDIR)

fclean					:	clean
	rm -rf $(CHECKER) $(PUSH_SWAP)
	make fclean -C $(LIBDIR)

re						:	fclean	all

ps						:
	rm -rf objs/
	make
