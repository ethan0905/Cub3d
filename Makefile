# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esafar <esafar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/22 15:43:36 by esafar            #+#    #+#              #
#    Updated: 2022/06/22 15:45:25 by esafar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	srcs/main.c \
		srcs/check_args.c \
		srcs/parsing.c \
		srcs/parsing_texture.c \
		srcs/parsing_map.c \
		srcs/exit.c \
        srcs/check_map.c \
		srcs/parsing_player.c \
		srcs/mini_map.c \
		srcs/start.c \
        srcs/check_move.c \
		srcs/render.c \
		srcs/check_x_rays.c \
		srcs/check_y_rays.c \
        srcs/dist.c srcs/utils_game.c \
		srcs/render_utils.c \
		srcs/get_color.c

LIBFT = libft/ft_lstrlen.c \
		libft/get_next_line.c \
		libft/ft_isalpha.c \
		libft/ft_free_ls.c \
		libft/ft_atoi.c \
		libft/ft_isdigit.c \
		libft/ft_strncmp.c \
		libft/ft_strlen.c \
		libft/ft_strjoin_and_free_s1.c \
		libft/ft_split.c \
		libft/ft_putendl_fd.c \
		libft/ft_calloc.c \
		libft/ft_putstr_fd.c \
		libft/ft_strdup.c \
		libft/ft_putchar_fd.c \
		libft/ft_bzero.c \
		libft/ft_substr.c

OBJS 		= ${SRCS:.c=.o} ${LIBFT:.c=.o}

UNAME		:= $(shell uname)

PATH_MLX	= mlx
PATH_LIB	= libft
INCL		= ./includes/cub3d.h
CC 			= gcc
CFLAGS		= -g3 -Wall -Wextra -Werror -D BUFFER_SIZE=1
RM			= rm -f
NAME		= cub3d
FLAGS		= -ldl -Imlx -Lmlx -lmlx -lm -lbsd -lXext -lX11 -Wl,-rpath=./bass/,-rpath=./mlx/,-rpath=./delay/
#FLAGS		= -ldl -Imlx -Lmlx -lmlx -lm -lz -lXext -lX11 -Wl,-rpath=./bass/,-rpath=./mlx/,-rpath=./delay/

all: 		${NAME} $(INCL)

.c.o:
			${CC} ${CFLAGS} -Imlx -Ibass -c $< -o ${<:.c=.o}

$(NAME): 	$(OBJS) $(INCL)
			make -C $(PATH_MLX)
			make -C $(PATH_LIB)
			${CC} $(CFLAGS) -o $(NAME) $(OBJS) $(FLAGS)

bonus:		${OBJS} ${OBJS_B}
			make -C $(PATH_MLX)
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} $(FLAGS)

clean:
			make -C $(PATH_MLX) clean
			make -C $(PATH_LIB) clean
			${RM} ${OBJS}
fclean: 	clean
			make -C $(PATH_MLX) clean
			make -C $(PATH_LIB) clean
			${RM} ${NAME}

re: 		fclean all

.PHONY:		bonus all clean fclean re