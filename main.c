/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuccher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:03:44 by lbuccher          #+#    #+#             */
/*   Updated: 2021/12/17 16:57:51 by lbuccher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	**get_path(char *env[])
{
	int		i;
	char	*all_path;
	char	**split_path;

	i = 0;
	while (*env)
	{
		if (ft_strnstr(*env, "PATH", 4) != 0)
			break ;
		(*env)++;
	}
	all_path = ft_substr(*env, 5, ft_strlen(*env) - 5);
	split_path = ft_split(all_path, ':');
	free(all_path);
	return (split_path);
}

void	parent(t_fd fds, char *argv[], char *env[], int fd[2])
{
	int		i;
	char	**cmd;
	char	**paths;
	char	*cmd_path;

	i = -1;
	cmd = ft_split(argv[3], ' ');
	paths = get_path(env);
	if (dup2(fds.f_out, STDOUT_FILENO) < 0)
		return (perror("fds.f_out"));
	if (dup2(fd[0], STDIN_FILENO) < 0)
		return (perror("fd[0]"));
	close_pipe(fds, fd);
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmd[0]);
		if (access(cmd_path, F_OK) == 0)
			break ;
		free(cmd_path);
	}
	execve(cmd_path, cmd, env);
	perror(cmd_path);
	free(paths);
	free(cmd);
	if (access(cmd_path, F_OK) != 0)
		exit(0);
}

void	child(t_fd fds, char *argv[], char *env[], int fd[2])
{
	int		i;
	char	**cmd;
	char	**paths;
	char	*cmd_path;

	i = -1;
	cmd = ft_split(argv[2], ' ');
	paths = get_path(env);
	if (dup2(fds.f_in, STDIN_FILENO) < 0)
		return (perror("fds.f_in"));
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		return (perror("fd[1]"));
	close_pipe(fds, fd);
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmd[0]);
		if (access(cmd_path, F_OK) == 0)
			break ;
		free(cmd_path);
	}
	execve(cmd_path, cmd, env);
	perror(cmd_path);
	free(paths);
	free(cmd);
	if (access(cmd_path, F_OK) != 0)
		exit(0);
}

void	pipex(t_fd fds, char *argv[], char *env[])
{
	int	fd[2];
	int	pid;

	if (pipe(fd) < 0)
		return (perror("pipe"));
	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	else if (pid == 0)
		child(fds, argv, env, fd);
	else
		parent(fds, argv, env, fd);
}

int	main(int argc, char *argv[], char *env[])
{
	t_fd	fds;

	if (argc < 4)
		exit(1);
	fds.f_in = open(argv[1], O_RDONLY);
	fds.f_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fds.f_in < 0 || fds.f_out < 0)
		exit(1);
	pipex(fds, argv, env);
	close(fds.f_in);
	close(fds.f_out);
	return (0);
}
