# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esafar <esafar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/03 15:40:15 by esafar            #+#    #+#              #
#    Updated: 2022/07/13 14:09:09 by esafar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_strlen.c \
	   ft_isalpha.c \
	   ft_isdigit.c \
	   ft_isprint.c \
	   ft_isalnum.c \
	   ft_toupper.c \
	   ft_tolower.c \
	   ft_memcpy.c \
	   ft_memset.c \
	   ft_memccpy.c \
	   ft_bzero.c \
	   ft_atoi.c \
	   ft_strchr.c \
	   ft_strcmp.c \
	   ft_strncmp.c \
	   ft_strrchr.c \
	   ft_strdup.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_isascii.c \
	   ft_calloc.c \
	   ft_strnstr.c \
	   ft_strlcat.c \
	   ft_itoa.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   ft_strjoin.c \
	   ft_memmove.c \
	   ft_strlcpy.c \
	   ft_substr.c \
	   ft_strtrim.c \
	   ft_strmapi.c \
	   ft_split.c \
	   ft_free_ls.c \
	   ft_lstrlen.c \
	   ft_strjoin_and_free_s1.c \
	   get_next_line.c

OBJS = $(SRCS:.c=.o)

BONUS = ft_lstsize.c \
		ft_lstadd_front.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c

OBJS_BONUS = $(BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I.
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
			ar rcs $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
			$(RM) $(NAME) bonus

re: fclean $(NAME)

bonus: $(OBJS) $(OBJS_BONUS)
			ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

.PHONY: all clean fclean re bonus
