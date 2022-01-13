/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuccher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:51:00 by lbuccher          #+#    #+#             */
/*   Updated: 2022/01/12 17:08:52 by lbuccher         ###   ########.fr       */
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

void	process(char *argv, char *env[])
{
	int		i;
	char	*tmp;
	char	**cmd;
	char	**paths;
	char	*cmd_path;

	i = -1;
	cmd = ft_split(argv, ' ');
	paths = get_path(env);
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		if (ft_strncmp(cmd_path, cmd[0], ft_strlen(cmd_path)) == 0)
			break ;
		tmp = ft_strjoin(cmd_path, cmd[0]);
		free(cmd_path);
		cmd_path = tmp;
		if (!access(cmd_path, F_OK))
			break ;
		if (paths[i + 1])
			free(cmd_path);
	}
	ft_end_process(cmd_path, cmd, paths, env);
}

void	parent(t_fd fds, char **argv, char *env[], int fd[2])
{
	if (dup2(fds.f_out, STDOUT_FILENO) < 0 || dup2(fd[0], STDIN_FILENO) < 0)
		return (perror("fd"));
	close_pipe(fds, fd);
	process(argv[3], env);
}

void	child(t_fd fds, char **argv, char *env[], int fd[2])
{
	if (dup2(fds.f_in, STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
		return (perror("fd"));
	close_pipe(fds, fd);
	process(argv[2], env);
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
