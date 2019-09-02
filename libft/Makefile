# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sregnard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 14:51:18 by sregnard          #+#    #+#              #
#    Updated: 2019/09/02 17:14:47 by sregnard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a

HEADDIR			=	includes/
INCLUDES		=	-I $(HEADDIR)

HEADERS			=	libft.h			\
					ft_printf.h		\
					get_next_line.h	\
					list.h			\
					map.h			\
					point.h			\
					read_file.h
DEPENDENCIES	+=	$(addprefix $(HEADDIR), $(HEADERS))

SRCDIR			=	srcs/
SRC				:=	$(SRC)

SUBDIR			=	ft_mem/
SRCNAME			= 	ft_memset.c \
					ft_bzero.c \
					ft_memcpy.c \
					ft_memccpy.c \
					ft_memmove.c \
					ft_memchr.c	\
					ft_memcmp.c	\
					ft_memalloc.c \
					ft_memdel.c
SRC				+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR			=	ft_is/
SRCNAME			=	ft_isalpha.c \
					ft_isdigit.c \
					ft_isalnum.c \
					ft_isascii.c \
					ft_isprint.c \
					ft_isspace.c \
					ft_isnumber.c \
					ft_isinteger.c
SRC				+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR			=	ft_str/
SRCNAME			=	ft_strlen.c \
					ft_strdup.c \
					ft_strcpy.c \
					ft_strncpy.c \
					ft_strcat.c \
					ft_strncat.c \
					ft_strlcat.c \
					ft_strchr.c \
					ft_strrchr.c \
					ft_strstr.c \
					ft_strnstr.c \
					ft_strcmp.c \
					ft_strncmp.c \
					ft_strnew.c \
					ft_strdel.c \
					ft_strclr.c \
					ft_striter.c \
					ft_striteri.c \
					ft_strmap.c \
					ft_strmapi.c \
					ft_strequ.c \
					ft_strnequ.c \
					ft_strsub.c \
					ft_strjoin.c \
					ft_strtrim.c \
					ft_strsplit.c \
					ft_strrev.c \
					ft_stradd.c
SRC				+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR			=	ft_put/
SRCNAME			=	ft_putchar.c \
					ft_putstr.c \
					ft_putendl.c \
					ft_putln.c \
					ft_putnbr.c \
					ft_putchar_fd.c \
					ft_putstr_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c
SRC				+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR			=	ft_lst/
SRCNAME			=	ft_lstnew.c \
					ft_lstdelone.c \
					ft_lstdel.c \
					ft_lstadd.c \
					ft_lstiter.c \
					ft_lstcpy.c \
					ft_lstmap.c \
					ft_lstlen.c
SRC				+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR			=	ft_pt/
SRCNAME			=	ft_ptnew.c \
					ft_ptcpy.c \
					ft_ptset.c \
					ft_ptcmp.c \
					ft_ptprint.c \
					ft_ptfree.c
SRC				+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR			=	utils/
SRCNAME			=	ft_toupper.c \
					ft_tolower.c \
					ft_swap.c		
SRC				+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR			=	conversion/
SRCNAME			=	ft_itoa.c \
					ft_atoi.c			
SRC				+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR			=	maths/
SRCNAME			= 	ft_power.c \
					ft_sqrt.c \
					ft_factorial.c
SRC				+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR			=	tab2d/
SRCNAME			=	ft_print_tab.c \
					ft_free_tab.c \
					ft_remove_elem_tab.c \
					ft_nb_str_tab.c \
					ft_max_strlen_tab.c \
					ft_atoi_tab.c
SRC				+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR			=	read/
SRCNAME			=	get_next_line.c \
					get_next_line_custom.c \
					read_file.c
SRC				+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR			=	ft_map/
SRCNAME			=	ft_mapnew.c \
					ft_mapfrom.c \
					ft_mapfree.c
SRC				+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

SUBDIR			=	ft_printf/
SRCNAME			=	ft_printf.c \
					pf_args.c \
					pf_chars.c \
					pf_floats.c \
					pf_numbers.c \
					pf_utils.c
SRC				+=	$(addprefix $(SRCDIR)$(SUBDIR), $(SRCNAME))

OBJDIR			=	objs/
OBJ				=	$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

CC				=	gcc	
CFLAGS			=	-Wall -Wextra -Werror

_RED			=	\033[1;31m
_GREEN			=	\033[1;32m
_YELLOW			=	\033[1;33m
_BLUE			=	\033[1;34m
_MAGENTA		=	\033[1;35m
_CYAN			=	\033[1;36m
_BG_RED			=	\033[1;41m
_BG_GREEN		=	\033[1;42m
_BG_YELLOW		=	\033[1;43m
_BG_BLUE		=	\033[1;44m
_BG_MAGENTA		=	\033[1;45m
_BG_CYAN		=	\033[1;46m
_RESET			=	\033[0m

all				:	$(NAME)

$(NAME)			:	$(OBJ)
	@ar rcs $@ $?
	@printf "\r" ; tput el
	@printf "$(_GREEN)%-10s : Library\tbuilt.\n\a$(_RESET)" $(NAME)

$(OBJDIR)%.o	:	$(SRCDIR)%.c $(DEPENDENCIES)
	@if [ ! -d $(dir $@) ]; \
	then \
		printf "\r"; \
		tput el; \
		printf "$(_YELLOW)%-10s : %s $(_RESET)\a" $(NAME) $(dir $<); \
	fi;
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
	@printf "$(_BG_GREEN) $(_RESET)"

clean			:
	@printf "$(_BLUE)%-10s : Objects\tcleaned.\n$(_RESET)" $(NAME)
	@rm -rf $(OBJDIR)

fclean			:	clean
	@printf "$(_MAGENTA)%-10s : Library\tcleaned.\n$(_RESET)" $(NAME)
	@rm -rf $(NAME)

re				:	fclean	all
