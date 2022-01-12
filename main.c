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
	char	*all_path;
	char	**split_path;

	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
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
	if (dup2(fds.f_out, STDOUT_FILENO) < 0 || dup2(fd[0], STDIN_FILENO) < 0)
		return (perror("fd"));
	close_pipe(fds, fd);
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		if (ft_strncmp(cmd_path, cmd[0], ft_strlen(cmd_path)) == 0)
			break ;
		cmd_path = ft_strjoin(cmd_path, cmd[0]);
		if (access(cmd_path, F_OK) == 0)
			break ;
		if (paths[i + 1])
			free(cmd_path);
	}
	ft_end_process(cmd_path, cmd, paths, env);
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
	if (dup2(fds.f_in, STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
		return (perror("fd"));
	close_pipe(fds, fd);
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		if (ft_strncmp(cmd_path, cmd[0], ft_strlen(cmd_path)) == 0)
			break ;
		cmd_path = ft_strjoin(cmd_path, cmd[0]);
		if (access(cmd_path, F_OK) == 0)
			break ;
		if (paths[i + 1])
			free(cmd_path);
	}
	ft_end_process(cmd_path, cmd, paths, env);
}

void	pipex(t_fd fds, char *argv[], char *env[])
{
	int		fd[2];
	int		pid;

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

int	main(int argc, char *argv[], char *envp[])
{
	t_fd	fds;

	if (argc != 5)
	{
		perror(strerror(22));
		exit(1);
	}
	fds.f_in = open(argv[1], O_RDONLY);
	fds.f_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fds.f_out < 0)
	{
		perror(strerror(9));
		exit(127);
	}
	pipex(fds, argv, envp);
	close(fds.f_in);
	close(fds.f_out);
	return (0);
}
