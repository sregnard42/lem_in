# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 14:51:18 by sregnard          #+#    #+#              #
#    Updated: 2019/08/25 14:39:17 by sregnard         ###   ########.fr        #
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

_RED			=	\033[1;31m
_GREEN			=	\033[1;32m
_YELLOW			=	\033[1;33m
_BLUE			=	\033[1;34m
_MAGENTA		=	\033[1;35m
_CYAN			=	\033[1;36m
_RESET			=	\033[0m

all						:	$(LIBFT) $(LEM_IN)

$(LIBFT)				:
	@make -C $(LIBDIR)

$(LEM_IN)				:	$(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(XFLAGS) $(INCLUDES) $(LIBFT) -o $@ $(OBJ)
	@printf "\r" ; tput el
	@printf "$(_GREEN)Building lem-in...\tDone.\n$(_RESET)"

$(OBJDIR)%.o			:	$(SRCDIR)%.c $(DEPENDENCIES)
	@mkdir -p $(OBJDIR);
	@printf "\r" ; tput el
	@printf "$(_YELLOW)Building lem-in...\t$<$(_RESET)"
	@$(CC) $(CFLAGS) $(XFLAGS) $(INCLUDES) -o $@ -c $<

clean					:
	@printf "$(_BLUE)%-10s : Objects\tcleaned.\n$(_RESET)" "lem-in"
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBDIR)

fclean					:	clean
	@printf "$(_MAGENTA)%-10s : Executable\tcleaned.\n$(_RESET)" "lem-in"
	@rm -rf $(LEM_IN)
	@printf "$(_MAGENTA)%-10s : Library\tcleaned.\n$(_RESET)" "libft"
	@rm -rf $(LIBFT)

re						:	fclean	all

li						:
	@printf "$(_BLUE)%-10s : Objects\tcleaned.\n$(_RESET)" "lem-in"
	@printf "$(_MAGENTA)%-10s : Executable\tcleaned.\n$(_RESET)" "lem-in"
	@rm -rf objs/
	@rm -rf $(LEM_IN)
	@make
