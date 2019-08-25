# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 14:51:18 by sregnard          #+#    #+#              #
#    Updated: 2019/08/25 13:53:41 by sregnard         ###   ########.fr        #
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
	@$(CC) $(CFLAGS) $(XFLAGS) $(INCLUDES) $(LIBFT) -o $@ $(OBJ)
	@printf "\033[1;32m\rBuilding lem-in...\tDone.\n\033[0m"

$(OBJDIR)%.o			:	$(SRCDIR)%.c $(DEPENDENCIES)
	@mkdir -p $(OBJDIR);
	@printf "\033[1;36m\rBuilding lem-in...\t\033[0m"
	@$(CC) $(CFLAGS) $(XFLAGS) $(INCLUDES) -o $@ -c $<

clean					:
	@printf "\033[1;33m%-10s : Objects\tcleaned.\n\033[0m" "lem-in"
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBDIR)

fclean					:	clean
	@printf "\033[1;31m%-10s : Executable\tcleaned.\n\033[0m" "lem-in"
	@rm -rf $(LEM_IN)
	@make fclean -C $(LIBDIR)

re						:	fclean	all

li						:
	@printf "\033[1;33m%-10s : Objects\tcleaned.\n\033[0m" "lem-in"
	@printf "\033[1;31m%-10s : Executable\tcleaned.\n\033[0m" "lem-in"
	@rm -rf objs/
	@make
