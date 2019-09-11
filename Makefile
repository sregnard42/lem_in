# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 14:51:18 by sregnard          #+#    #+#              #
#    Updated: 2019/09/11 15:41:02 by sregnard         ###   ########.fr        #
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
SRC						:=	$(SRC)

SUBDIR					=	lem_in/
SRCNAME					=	lem_in.c		\
							error.c			\
							options.c		\
							print.c
SRC						+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR					=	parsing/
SRCNAME					=	parsing.c		\
							parsing_rooms.c	\
							already_exists.c\
							parsing_links.c
SRC						+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR					=	ant/
SRCNAME					=	ant.c
SRC						+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR					=	room/
SRCNAME					=	room.c			\
							relative.c
SRC						+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR					=	link/
SRCNAME					=	link.c
SRC						+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR					=	path/
SRCNAME					=	path.c			\
							path_list.c		\
							path_opti.c 	\
							path_utils.c
SRC						+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR					=	algo/
SRCNAME					=	bfs.c			\
							queue.c			\
							repartition.c	\
							tree.c
SRC						+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR					=	free/
SRCNAME					=	free_all.c		\
							free_paths.c	\
							free_rooms.c
SRC						+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

OBJDIR					=	objs/
OBJ						=	$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

CC						=	gcc
CFLAGS					=	-Wall -Wextra -Werror

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
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBFT) -o $@ $(OBJ)
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
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
	@printf "$(_BG_GREEN) $(_RESET)"

clean					:
	@printf "$(_BLUE)%-10s : Objects\tcleaned.\n$(_RESET)" $(NAME)
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBDIR)

fclean					:	clean
	@rm -rf $(NAME)
	@printf "$(_MAGENTA)%-10s : Executable\tcleaned.\n$(_RESET)" $(NAME)
	@rm -rf $(LIBFT)
	@printf "$(_MAGENTA)%-10s : Library\tcleaned.\n$(_RESET)" $(notdir $(LIBFT))

re						:	fclean	all

li						:
	@rm -rf objs/
	@printf "$(_BLUE)%-10s : Objects\tcleaned.\n$(_RESET)" $(NAME)
	@rm -rf $(NAME)
	@printf "$(_MAGENTA)%-10s : Executable\tcleaned.\n$(_RESET)" $(NAME)
	@make
