# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbuccher <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 13:37:52 by lbuccher          #+#    #+#              #
#    Updated: 2021/12/21 13:37:54 by lbuccher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = 	main.c \
		utils.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_split.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_strnstr.c \
		ft_substr.c \

OBJ = $(SRCS:.c=.o)

INCLUDE = pipex.h

FLAGS = -Wall -Werror -Wextra

CC = gcc

.c.o:
	$(CC) $(FLAGS) -I $(INCLUDE) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
