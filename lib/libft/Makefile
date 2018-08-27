# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/10 17:05:18 by fchevrey          #+#    #+#              #
#    Updated: 2018/08/22 16:50:21 by fchevrey         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
DIR_NAME = libft

## Colors ##
PURPLE = [038;2;255;40;255
GREEN = [038;2;82;255;123
CYAN = [038;2;0;255;255
PINK = [038;2;255;0;137
YELLOW = [038;2;252;125;91
ORANGE = [038;2;239;138;5

## Sources ##
SRC_DIR = srcs/

SRCS_NAME = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
	ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c \
	ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c \
	ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c \
	ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c \
	ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c \
	ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c \
	ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c \
	ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strlower.c \
	ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
	ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c \
	ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c \
	ft_strtrim.c ft_strupper.c ft_tolower.c ft_toupper.c \
	ft_tabprint.c ft_putnbrnl.c ft_tabdel.c ft_strsubf.c \
	ft_strjoinf.c get_next_line.c ft_tablen.c print_memory.c \
	count_lines_of_file.c ft_str_is_digit.c ft_lstadd_last.c \
	ft_lstsrch.c get_next_line_multi.c ft_lstnew_cpy.c

SRCS = $(addprefix $(SRC_DIR), $(SRCS_NAME))

## Includes ##
INC = -I includes/
INCS = ./includes/libft.h

## Objects ##
OBJS_DIR = objets/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS_NAME:.c=.o))

CFLAGS = -Wall -Werror -Wextra

CC = gcc

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
	@echo "\033$(CYAN)33m➼	Creating $(DIR_NAME)'s objects with flag : \033$(GREEN)36m $(CFLAGS)\033[0m"

$(OBJS_DIR)%.o:$(SRC_DIR)%.c $(INCS)
	@echo "\033$(PURPLE)m⧖	Creating	$@\033[0m"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(NAME): $(OBJS)
	@echo "\033$(GREEN)32m✓	\033[0m\033$(GREEN)32m$(DIR_NAME)'s objects created\033[0m"
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\033$(GREEN)32m✓	\033[0m\033$(GREEN)32m$(NAME) created\033[0m"

clean :
	@rm -rf $(OBJS_DIR)
	@echo "\033$(PINK)36m✗	\033[0m\033$(PINK)31m$(DIR_NAME)'s objets removed\033[0m"

fclean : clean
	@rm -rf $(NAME)
	@echo "\033$(PINK)36m✗	\033[0m\033$(PINK)31m$(NAME) removed\033[0m"

re: fclean all

.PHONY : all clean fclean re
