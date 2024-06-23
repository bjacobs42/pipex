/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 01:27:12 by bjacobs           #+#    #+#             */
/*   Updated: 2023/01/11 20:24:01 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

t_pipex	init_pipex(char **argv, char **env, int argc)
{
	t_pipex	pipex;

	pipex.cmdc = argc - 3;
	pipex.pids = (int *)malloc(sizeof(int) * pipex.cmdc);
	if (!pipex.pids)
		return (perror("malloc 1 error"), pipex);
	pipex.pipes = mk_pipes(pipex.cmdc);
	if (!pipex.pipes)
		return (free(pipex.pids), pipex.pids = NULL, pipex);
	pipex.outfile = argv[argc - 1];
	pipex.infile = argv[1];
	pipex.env = env;
	return (pipex);
}

void	close_pipes_arr(int **pipes, int i, bool clean)
{
	if (!pipes)
		return ;
	while (i--)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		if (clean)
			free(pipes[i]);
	}
	if (clean)
	{
		free(pipes);
		pipes = NULL;
	}
}

int	**mk_pipes(int n)
{
	int	i;
	int	**pipes;

	n--;
	pipes = (int **)malloc(sizeof(int *) * n);
	if (!pipes)
		return (perror("malloc 2"), NULL);
	i = 0;
	while (i < n)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (close_pipes_arr(pipes, i, true), perror("malloc 3"), NULL);
		if (pipe(pipes[i]) == -1)
		{
			free(pipes[i]);
			close_pipes_arr(pipes, i, true);
			return (perror("pipes creation error"), NULL);
		}
		i++;
	}
	return (pipes);
}
