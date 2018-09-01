NAME = wolf3d
DIR_NAME = Wolf3D

## Colors ##
PURPLE = [038;2;255;40;255
GREEN = [038;2;82;255;123
CYAN = [038;2;0;255;255
PINK = [038;2;255;0;137
YELLOW = [038;2;252;125;91
ORANGE = [038;2;239;138;5

## Sources ##
SRCS_DIR = srcs

SRCS = main.c ft_exit.c data_init.c scale_map_and_real.c ft_error.c \
		sound_init.c\
		\
		parse/parse.c parse/parse2.c parse/free_parse.c \
		\
		event/ft_event.c event/ft_mouse.c event/ft_mouse_wheel.c \
		event/ft_keyboard.c event/fill_funar_key_event.c event/move.c \
		event/look.c event/check_collision.c event/sound.c \
		event/acrobatic.c event/move_stop.c event/stand.c\
		\
		raycast/calc_distance.c raycast/draw_wall.c raycast/ray.c \
		raycast/calc_offset.c raycast/skybox.c\
		\
		math/deg_rad.c \
		\
		mini_map/mini_map.c mini_map/mini_map2.c \
		\
		assets/get_wall_tex.c \
		\
		tga/parse_tga.c

## Objects ##
OBJS = $(SRCS:.c=.o)
OBJS_DIR = ./objs
OBJS_SUB_DIRS = parse event math raycast mini_map assets tga
OBJS_PRE = $(addprefix $(OBJS_DIR)/, $(OBJS))

## Lib dirs ##
LIB_DIR = ./lib
LIBFT_DIR = $(LIB_DIR)/libft
LIBMYSDL_DIR = $(LIB_DIR)/libmysdl
LIBPT_DIR = $(LIB_DIR)/libpt

## Macros for sdl2 installation ##
MAIN_DIR_PATH = $(shell pwd)
SDL_PATH = $(addprefix $(MAIN_DIR_PATH), /lib/sdl2)
SDL_MIXER_PATH = $(addprefix $(MAIN_DIR_PATH), /lib/sdl2_mixer)
SDL_TTF_PATH = $(addprefix $(MAIN_DIR_PATH), /lib/sdl2_ttf)
VORBIS_PATH = $(addprefix $(MAIN_DIR_PATH), /lib/vorbis)
SDL_VER = 2.0.8
SDL_MIXER_VER = 2.0.2
SDL_TTF_VER = 2.0.14
VORBIS_VER = 1.3.6

## Includes ##
INC = -I ./includes/
SDL2_INC = $(shell sh ./lib/sdl2/bin/sdl2-config --cflags)
LIB_INCS =	-I $(LIBFT_DIR)/includes/ \
			-I $(LIBMYSDL_DIR)/includes/ \
			-I $(LIBPT_DIR)/includes/ \
			-I $(SDL_MIXER_PATH)/include/SDL2 \
			-I $(SDL_TTF_PATH)/include/SDL2 \
			$(SDL2_INC)

INCS = $(INC) $(LIB_INCS)

## FLAGS ##
CC = gcc
SDL2_LFLAGS = $(shell sh ./lib/sdl2/bin/sdl2-config --libs)
#SDL_MIXER_LFLAGS = $(shell pkg-config --libs SDL2_mixer)

LFLAGS =	-L $(LIBFT_DIR) -lft \
			-L $(LIBPT_DIR) -lpt \
			-L $(LIBMYSDL_DIR) -lmysdl \
			-lm \
			$(SDL2_LFLAGS) \
			-L $(SDL_MIXER_PATH)/lib/ -lSDL2_mixer
			#$(SDL_MIXER_LFLAGS) 
			#-L $(SDL_MIXER_PATH)/lib -lSDL2_mixer
#			-L $(SDL_TTF_PATH)/lib -lSDL2_ttf
CFLAGS = -Wall -Wextra -Werror -g3

MESSAGE = "make[1]: Nothing to be done for 'all'"
DONE_MESSAGE = "\033$(GREEN)2m✓\t\033$(GREEN)mDONE !\033[0m\
				\n ========================================\n"

## RULES ##

all: SDL2 LIBFT LIBPT MYSDL print_name $(NAME) print_end

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@echo "\033$(PURPLE)m⧖	Creating	$@\033[0m"
	@export PKG_CONFIG_PATH=$(PKG_CONFIG_PATH):$(addprefix $(SDL_PATH), /lib/pkgconfig) &&\
	export PKG_CONFIG_PATH=$(PKG_CONFIG_PATH):$(addprefix $(SDL_MIXER_PATH), /lib/pkgconfig) &&\
	export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(addprefix $(SDL_MIXER_PATH), /lib) &&\
	export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(addprefix $(VORBIS_MIXER_PATH), /lib) &&\
	gcc $(CFLAGS) $(INCS) -c $^ -o $@

$(OBJS_DIR):
	@echo "\033$(CYAN)m➼	\033$(CYAN)mCreating $(DIR_NAME)'s objects \
	with flag : \033$(GREEN)m $(CFLAGS)\033[0m"
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(addprefix $(OBJS_DIR)/, $(OBJS_SUB_DIRS))

$(NAME): $(OBJS_DIR) $(OBJS_PRE)
	@echo "\033$(GREEN)m➼\t\033$(GREEN)32mCreating $(DIR_NAME)'s executable\033[0m"
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJS_PRE) $(LFLAGS)
	@$(eval MESSAGE = $(DONE_MESSAGE))

rm_obj:
	@rm -rf $(OBJS_DIR)
	@echo "\033$(PINK)36m✗	\033[0m\033$(PINK)31m$(DIR_NAME)'s object removed\033[0m"

clean: rm_obj
	@make -C $(LIBFT_DIR) clean
	@make -C $(LIBPT_DIR) clean
	@make -C $(LIBMYSDL_DIR) clean

fclean: rm_obj
	@rm -rf $(NAME)
	@echo "\033$(PINK)36m✗	\033[0m\033$(PINK)31m$(NAME) removed\033[0m"
	@make -C $(LIBFT_DIR) fclean
	@make -C $(LIBPT_DIR) fclean
	@make -C $(LIBMYSDL_DIR) fclean

re: fclean all

exe: rm_obj all

rm_vorbis:
	@rm -rf $(VORBIS_PATH)
	@echo "\033$(PINK)36m✗	libvorbis-$(VORBIS_VER) removed\033[0m"

rm_SDL2:
	@rm -rf $(SDL2_PATH) $(SDL_MIXER_PATH) $(SDL_TTF_PATH)
	@echo "\033$(PINK)36m✗	SDL2-$(SDL_VER) removed\033[0m"

re_SDL2: fclean rm_SDL2 all

MODE_DEBUG: change_cflag all

re_MODE_DEBUG: rm_obj MODE_DEBUG

change_cflag:
	@$(eval CFLAGS = -fsanitize=address)

VORBIS :
	@if [ ! -d "./lib/vorbis" ]; then \
		echo "\033$(PINK)m⚠\tlibvorbis is not installed ! ...\033[0m"; \
		echo "\033$(CYAN)m➼\tCompiling libvorbis-$(VORBIS_VER) ...\033[0m"; \
		printf "\r\033$(YELLOW)m\tIn 3 ...\033[0m"; sleep 1; \
		printf "\r\033$(YELLOW)m\tIn 2 ...\033[0m"; sleep 1; \
		printf "\r\033$(YELLOW)3m\tIn 1 ...\033[0m"; sleep 1; printf "\n"; \
		curl -OL https://ftp.osuosl.org/pub/xiph/releases/vorbis/libvorbis-$(VORBIS_VER).tar.gz && \
		tar -zxvf libvorbis-$(VORBIS_VER).tar.gz && \
		rm libvorbis-$(VORBIS_VER).tar.gz && \
		mkdir -p $(VORBIS_PATH) && \
		cd libvorbis-$(VORBIS_VER) && \
			sh configure --prefix=$(VORBIS_PATH) && \
			make && \
			make install && \
		cd .. && \
		rm -rf SDL2-$(VORBIS_VER);\
		echo "\033$(GREEN)m✓\tlibvorbis-$(VORBIS_VER) installed !\033[0m"; \
	else \
		echo "\033$(GREEN)m✓\tlibvorbis-$(VORBIS_VER) already installed\033[0m"; \
	fi

SDL2 : VORBIS
	@if [ ! -d "./lib/sdl2" ]; then \
		echo "\033$(PINK)m⚠\tSDL2 is not installed ! ...\033[0m"; \
		echo "\033$(CYAN)m➼\tCompiling SDL2-$(SDL_VER) ...\033[0m"; \
		printf "\r\033$(YELLOW)m\tIn 3 ...\033[0m"; sleep 1; \
		printf "\r\033$(YELLOW)m\tIn 2 ...\033[0m"; sleep 1; \
		printf "\r\033$(YELLOW)3m\tIn 1 ...\033[0m"; sleep 1; printf "\n"; \
		curl -OL http://www.libsdl.org/release/SDL2-$(SDL_VER).tar.gz && \
		tar -zxvf SDL2-$(SDL_VER).tar.gz && \
		rm SDL2-$(SDL_VER).tar.gz && \
		mkdir -p $(SDL_PATH) && \
		cd SDL2-$(SDL_VER) && \
			sh configure --prefix=$(SDL_PATH) && \
			make && \
			make install && \
		cd .. && \
		rm -rf SDL2-$(SDL_VER);\
		echo "\033$(GREEN)m✓\tSDl2-$(SDL_VER) installed !\033[0m"; \
	else \
		echo "\033$(GREEN)m✓\tSDl2-$(SDL_VER) already installed\033[0m"; \
	fi
	@if [ ! -d "./lib/sdl2_mixer" ]; then \
		export SDL2_CONFIG=$(addprefix $(SDL_PATH), /bin/sdl2-config); \
	export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(addprefix $(VORBIS_MIXER_PATH), /lib) &&\
		echo "\033$(CYAN)m➼\tCompiling SDL2_MIXER-$(SDL_MIXER_VER) ...\033[0m"; \
		curl -OL http://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-$(SDL_MIXER_VER).tar.gz && \
		tar -zxvf SDL2_mixer-$(SDL_MIXER_VER).tar.gz && \
		rm SDL2_mixer-$(SDL_MIXER_VER).tar.gz && \
		mkdir -p $(SDL_MIXER_PATH) && \
		cd SDL2_mixer-$(SDL_MIXER_VER) && \
			sh configure --prefix=$(SDL_MIXER_PATH) && \
			make && \
			make install && \
		cd .. && \
		rm -rf SDL2_mixer-$(SDL_MIXER_VER);\
	else \
		echo "\033$(GREEN)m✓\tSDl2_mixer-$(SDL_MIXER_VER) already installed\033[0m"; \
	fi
	@if [ ! -d "./lib/sdl2_ttf" ]; then \
		export SDL2_CONFIG=$(addprefix $(SDL_PATH), /bin/sdl2-config); \
		echo "\033$(CYAN)m➼\tCompiling SDL2_TTF-$(SDL_TTF_VER) ...\033[0m"; \
		curl -OL http://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-$(SDL_TTF_VER).tar.gz && \
		tar -zxvf SDL2_ttf-$(SDL_TTF_VER).tar.gz && \
		rm SDL2_ttf-$(SDL_TTF_VER).tar.gz && \
		mkdir -p $(SDL_TTF_PATH) && \
		cd SDL2_ttf-$(SDL_TTF_VER) && \
			sh configure --prefix=$(SDL_TTF_PATH) && \
			make && \
			make install && \
		cd .. && \
		rm -rf SDL2_ttf-$(SDL_TTF_VER); \
	else \
		echo "\033$(GREEN)m✓\tSDl2_ttf-$(SDL_TTF_VER) already installed\033[0m"; \
	fi
LIBFT:
	@echo "\033[033m➼\t\033[033mCompiling Libft ...\033[0m"
	@make -C $(LIBFT_DIR)

LIBPT:
	@echo "\033[033m➼\t\033[033mCompiling Libpt ...\033[0m"
	@make -C$(LIBPT_DIR)

MYSDL:
	@echo "\033[033m➼\t\033[033mCompiling Libmysdl ...\033[0m"
	@make -C $(LIBMYSDL_DIR)

print_name:
	@echo "\033[033m➼\t\033[033mCompiling $(DIR_NAME) ...\033[0m"

print_end:
	@echo $(MESSAGE)

.PHONY: all clean fclean re rm_obj exe SDL2 VORBIS LIBFT LIBPT MYSDL rm_SDL2 re_SDL2 \
		MODE_DEBUG re_MODE_DEBUG change_cflag print_name print_end FMOD
