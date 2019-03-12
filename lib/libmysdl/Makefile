# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fchevrey <fchevrey@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/10 17:05:18 by fchevrey          #+#    #+#              #
#    Updated: 2019/03/12 17:33:40 by fchevrey         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmysdl.a
DIR_NAME = Libmysdl
PURPLE = [038;2;255;40;255
GREEN = [038;2;82;255;123
CYAN = [038;2;0;255;255
PINK = [038;2;255;0;137
YELLOW = [038;2;252;125;91
ORANGE = [038;2;239;138;5

## Sources ##
SRCS_DIR = srcs/
SRCS_NAME = add_new_tex.c \
			write_tex_in_tex.c \
			fill_tex_in_color.c \
			free_all_tex.c \
			free_tex.c \
			free_win.c \
			get_color.c \
			lst_tex_new.c \
			lst_tex_srch.c \
			pt_to_tex.c \
			put_tex_to_win.c \
			put_tex_to_ren.c \
			texture_new.c \
			trace_line_tex.c \
			get_pixel.c \
			win_new.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_NAME))

## Includes ##
SDL2_INC = $(shell sh ../sdl2/bin/sdl2-config --cflags)
INC =	-I ./includes/ \
		-I ../libft/includes/ \
		-I ../libpt/includes/ \
		$(SDL2_INC)

## Objects ##
OBJS_DIR = ./objets/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS_NAME:.c=.o))

## Flags ##
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all : $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
	@echo "\033$(CYAN)m➼	\033$(CYAN)33mCreating $(DIR_NAME)'s objects with flag : \033$(GREEN)36m $(CFLAGS)\033[0m"

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	@echo "\033$(PURPLE)m⧖	Creating	$@\033[0m"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(NAME) : $(OBJS)
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

re : fclean all

.PHONY : all clean fclean re
