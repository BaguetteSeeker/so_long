# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epinaud <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 16:30:14 by epinaud           #+#    #+#              #
#    Updated: 2024/10/20 18:45:46 by epinaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE = so_long

INCLUDES = -I. -Ilibft -Ilibft/printf -I/usr/include -Iminilibx/

LDLIBS = libft/libft.a -Lminilibx -lmlx -L/usr/lib/X11 -lmlx_Linux -lXext -lX11

CFLAGS = -Wall -Wextra -Werror -ggdb3

OBJ_DIR = .obj

MLX_DIR = minilibx

CC = cc -D_XOPEN_SOURCE=700

$(OBJ_DIR)/%.o : %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

all: libft $(OBJ_DIR) $(EXE)

$(EXE) :
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

so_long: .obj/so_long.o

libft:
	@git -C libft pull
	@make -C libft
	@make -C $(MLX_DIR)

relibft:
	@git -C libft pull
	@make re -C libft

.obj:
	mkdir -p .obj

clean:
	@rm -f $(EXE)
	@make clean -C libft

fclean:  clean
	@rm -rf $(OBJ_DIR)
	@make fclean -C libft

re: fclean relibft $(OBJ_DIR) $(EXE)

.PHONY:  all clean fclean re bonus libft relibft
