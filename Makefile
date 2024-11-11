# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epinaud <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 16:30:14 by epinaud           #+#    #+#              #
#    Updated: 2024/11/11 08:13:35 by epinaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE = so_long

CC = cc

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I. -Ilibft -Ilibft/printf -I/usr/include -Iminilibx

LDLIBS = -Llibft -lft -Lminilibx -lmlx -lmlx_Linux -L/usr/lib/X11 -lXext -lX11

OBJ_DIR = .obj

MLX_DIR = minilibx

OS_NAME := $(shell uname -s | tr A-Z a-z)

$(OBJ_DIR)/%.o : %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

all: ftbranch libft $(OBJ_DIR) $(EXE)

$(EXE) :
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

os:
	@echo $(OS_NAME)

so_long: .obj/so_long.o .obj/map_parsing.o .obj/draw.o .obj/events.o \
			.obj/map_rendering.o .obj/so_long_utils.o .obj/player_movement.o

libft:
	@make -C libft
	@make -C $(MLX_DIR)

relibft:
	@make re -C libft

.obj:
	@mkdir -p .obj

ftbranch:
	@git -C libft checkout main

clean:
	@rm -f $(EXE)
	@make clean -C libft

fclean:  clean
	@rm -rf $(OBJ_DIR)
	@make fclean -C libft

re: ftbranch fclean relibft $(OBJ_DIR) $(EXE)

.PHONY:  all clean fclean re bonus libft relibft
