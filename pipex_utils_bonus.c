/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 01:27:12 by bjacobs           #+#    #+#             */
/*   Updated: 2023/01/10 22:01:31 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"
#include "libft.h"

char	**mk_args(char **env, char *cmd)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args)
		return (NULL);
	cmd_path = get_cmd_path(env, args[0]);
	if (!cmd_path)
		return (ft_clear_arr(args), NULL);
	if (cmd_path == args[0])
		return (args);
	free(args[0]);
	args[0] = cmd_path;
	return (args);
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

	pipes = (int **)malloc(sizeof(int *) * n);
	if (!pipes)
		return (perror("malloc 3 error"), NULL);
	i = 0;
	while (i < n)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (close_pipes_arr(pipes, i, true), perror("malloc 4"), NULL);
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

t_pipex	init_pipex(char **argv, char **env, int argc)
{
	t_pipex	pipex;

	pipex.outfile = argv[argc - 1];
	pipex.infile = argv[1];
	pipex.env = env;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		pipex.limiter = ft_strjoin(argv[2], "\n");
		if (!pipex.limiter)
			err_exit("malloc 1 error", EXIT_FAILURE, &pipex, false);
		pipex.cmdc = argc - 4;
	}
	else
	{
		pipex.limiter = NULL;
		pipex.cmdc = argc - 3;
	}
	pipex.pids = (int *)malloc(sizeof(int) * pipex.cmdc);
	if (!pipex.pids)
		return (perror("malloc 2 error"), free(pipex.limiter), pipex);
	pipex.pipes = mk_pipes(pipex.cmdc);
	if (!pipex.pipes)
		return (free(pipex.limiter), free(pipex.pids), pipex);
	return (pipex);
}
