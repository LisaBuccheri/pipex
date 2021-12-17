/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuccher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:03:44 by lbuccher          #+#    #+#             */
/*   Updated: 2021/12/15 16:03:51 by lbuccher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

void	parent(int fd_out, char *argv[], char *env[], int fd[2])
{
	int		status;
	char	*cmd[2];

	cmd[0] = argv[3];
	cmd[1] = 0;
	waitpid(-1, &status, 0);
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		return (perror("dup2 parent"));
	if (dup2(fd[0], STDIN_FILENO) < 0)
		return (perror("dup2-2 parent"));
	close(fd[1]);
	close(fd_out);
	if (execve(argv[3], cmd, env) < 0)
		return (perror("execve parent"));
}

void	child(int fd_in, char *argv[], char *env[], int fd[2])
{
	char	*cmd[2];

	cmd[0] = argv[2];
	cmd[1] = 0;
	if (dup2(fd_in, STDIN_FILENO) < 0)
		return (perror("dup2 child"));
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		return (perror("dup2-2 child"));
	close(fd[0]);
	close(fd_in);
	if (execve(argv[2], cmd, env) < 0)
		return (perror("execve child"));
}

void	pipex(int fd_in, int fd_out, char *argv[], char *env[])
{
	int	fd[2];
	int	pid;

	if (pipe(fd) < 0)
		return (perror("pipe"));
	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	else if (pid == 0)
		child(fd_in, argv, env, fd);
	else
		parent(fd_out, argv, env, fd);
}

int	main(int argc, char *argv[], char *env[])
{
	int	f_in;
	int	f_out;

	f_in = open(argv[1], O_RDONLY);
	f_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f_in < 0 || f_out < 0)
	{
		printf("error open f_in: %d\t f_out: %d\n", f_in, f_out);
		return (1);
	}
	pipex(f_in, f_out, argv, env);
	return (0);
}
