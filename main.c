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
