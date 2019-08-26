# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 14:51:18 by sregnard          #+#    #+#              #
#    Updated: 2019/08/26 21:13:52 by sregnard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					=	lem-in

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

_RED					=	\033[1;31m
_GREEN					=	\033[1;32m
_YELLOW					=	\033[1;33m
_BLUE					=	\033[1;34m
_MAGENTA				=	\033[1;35m
_CYAN					=	\033[1;36m
_BG_RED					=	\033[1;41m
_BG_GREEN				=	\033[1;42m
_BG_YELLOW				=	\033[1;43m
_BG_BLUE				=	\033[1;44m
_BG_MAGENTA				=	\033[1;45m
_BG_CYAN				=	\033[1;46m
_RESET					=	\033[0m

all						:	$(LIBFT) $(NAME)

$(LIBFT)				:
	@make -C $(LIBDIR)

$(NAME)				:	$(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(XFLAGS) $(INCLUDES) $(LIBFT) -o $@ $(OBJ)
	@printf "\r" ; tput el
	@printf "$(_GREEN)%-10s : Executable\tbuilt.\n\a$(_RESET)" $(NAME)

$(OBJDIR)%.o			:	$(SRCDIR)%.c $(DEPENDENCIES)
	@if [ ! -d $(dir $@) ]; \
	then \
		printf "\r"; \
		tput el; \
		printf "$(_YELLOW)%-10s : %s $(_RESET)\a" $(NAME) $(dir $<); \
	fi;
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(XFLAGS) $(INCLUDES) -o $@ -c $<
	@printf "$(_BG_GREEN) $(_RESET)"

clean					:
	@printf "$(_BLUE)%-10s : Objects\tcleaned.\n$(_RESET)" $(NAME)
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBDIR)

fclean					:	clean
	@rm -rf $(LEM_IN)
	@printf "$(_MAGENTA)%-10s : Executable\tcleaned.\n$(_RESET)" $(NAME)
	@rm -rf $(LIBFT)
	@printf "$(_MAGENTA)%-10s : Library\tcleaned.\n$(_RESET)" $(notdir $(LIBFT))

re						:	fclean	all

li						:
	@rm -rf objs/
	@printf "$(_BLUE)%-10s : Objects\tcleaned.\n$(_RESET)" $(NAME)
	@rm -rf $(LEM_IN)
	@printf "$(_MAGENTA)%-10s : Executable\tcleaned.\n$(_RESET)" $(NAME)
	@make
