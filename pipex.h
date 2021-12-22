/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuccher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 22:18:29 by lbuccher          #+#    #+#             */
/*   Updated: 2021/12/21 18:15:23 by lbuccher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>

typedef struct s_fd
{
	int	f_in;
	int	f_out;
}	t_fd;

size_t	ft_strlen(const char *s);

int		count(char const *s, char c);

void	close_pipe(t_fd fds, int fd[2]);
void	parent(t_fd fds, char *argv[], char *env[], int fd[2]);
void	child(t_fd fds, char *argv[], char *env[], int fd[2]);
void	pipex(t_fd fds, char *argv[], char *env[]);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	**get_path(char *env[]);
char	**null_return(int i, char **t);
char	**alloc_memory(int len, char **t, char const *s, char c);
char	**ft_split(char const *s, char c);

#endif
