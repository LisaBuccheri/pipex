/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuccher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 22:55:03 by lbuccher          #+#    #+#             */
/*   Updated: 2021/12/20 22:58:32 by lbuccher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	ft_matrix_len(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
		i++;
	return (i);
}

void	close_pipe(t_fd fds, int fd[2])
{
	close(fd[1]);
	close(fds.f_out);
	close(fd[0]);
	close(fds.f_in);
}

void	ft_free(char **paths, char **cmd)
{
	int	path_len;
	int	cmd_len;

	path_len = ft_matrix_len(paths);
	cmd_len = ft_matrix_len(cmd);
	while (paths && (path_len >= 0))
		free(paths[path_len--]);
	while (cmd && (cmd_len >= 0))
		free(cmd[cmd_len--]);
	if (paths)
		free(paths);
	if (cmd)
		free(cmd);
}

void	perror_cnf(char *str, char *cmd, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, cmd, ft_strlen(cmd));
	write(fd, "\n", 1);
}

void	ft_end_process(char *cmd_path, char **cmd, char **paths, char **env)
{
	if (ft_strncmp(cmd_path, cmd[0], ft_strlen(cmd_path)) == 0)
		cmd_path = cmd[0];
	execve(cmd_path, cmd, env);
	if (access(cmd_path, F_OK) != 0)
		perror_cnf("command not found: ", cmd[0], 2);
	free(cmd_path);
	ft_free(paths, cmd);
	exit(127);
}
