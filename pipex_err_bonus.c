/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_err_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:13:47 by bjacobs           #+#    #+#             */
/*   Updated: 2023/01/11 21:25:27 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"
#include "libft.h"

void	err_cleanup(char *error, t_pipex *pipex, bool print_err)
{
	if (print_err)
		perror(error);
	if (pipex->limiter)
		free(pipex->limiter);
	close_pipes_arr(pipex->pipes, pipex->cmdc, true);
	free(pipex->pids);
}

void	cmd_not_found(char *cmd)
{
	char	*err_msg;

	err_msg = ft_strjoin(cmd, ": command not found...\n");
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	exit(127);
}

void	err_exit(char *error, int code, t_pipex *pipex, bool cleanup)
{
	if (cleanup)
		err_cleanup(error, pipex, true);
	else
		perror(error);
	exit(code);
}
