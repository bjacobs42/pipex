/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 21:58:59 by bjacobs       #+#    #+#                 */
/*   Updated: 2024/06/24 00:02:46 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
#include "libft.h"
#include <sys/wait.h>

static char	**mk_args(char **env, char *cmd)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args)
		return (NULL);
	if (!args[0])
		return (args[0] = ft_strdup(""), args);
	cmd_path = get_cmd_path(env, args[0]);
	if (!cmd_path)
		return (ft_clear_arr(args), NULL);
	if (cmd_path == args[0])
		return (args);
	free(args[0]);
	args[0] = cmd_path;
	return (args);
}

static void	change_stdio(t_pipex *pipex, int i)
{
	int	fd;

	if (i == -1)
		fd = open(pipex->infile, O_RDONLY);
	else
		fd = pipex->pipes[i][0];
	if (fd == -1)
		err_exit(pipex->infile, EXIT_FAILURE, pipex, true);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (i + 1 >= pipex->cmdc - 1)
		fd = open(pipex->outfile, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	else
		fd = pipex->pipes[i + 1][1];
	if (fd == -1)
		err_exit(pipex->infile, EXIT_FAILURE, pipex, true);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	exec_cmd(t_pipex *pipex, int i, char *cmd)
{
	char	**exec_args;

	change_stdio(pipex, i);
	exec_args = mk_args(pipex->env, cmd);
	if (!exec_args)
		err_exit(NULL, EXIT_FAILURE, pipex, true);
	if (access(exec_args[0], F_OK))
		cmd_not_found(cmd);
	if (access(exec_args[0], X_OK))
		err_exit(cmd, 126, pipex, true);
	close_pipes_arr(pipex->pipes, pipex->cmdc - 1, false);
	execve(exec_args[0], exec_args, pipex->env);
	exit(1);
}

static int	ft_pipex(t_pipex *pipex, char **argv)
{
	int	status;
	int	i;

	i = 0;
	while (i < pipex->cmdc)
	{
		pipex->pids[i] = fork();
		if (pipex->pids[i] == -1)
			return (err_cleanup("fork error", pipex, true), -1);
		if (pipex->pids[i] == 0)
			exec_cmd(pipex, i - 1, argv[i + 2]);
		i++;
	}
	close_pipes_arr(pipex->pipes, pipex->cmdc - 1, true);
	i = 0;
	while (i < pipex->cmdc)
		waitpid(pipex->pids[i++], &status, 0);
	return (free(pipex->pids), status / 256);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		exit_code;

	if (argc != 5)
		return (ft_putendl_fd("pipes: <infile> <executable> <executable> <outfile>", STDERR_FILENO), 0);
	pipex = init_pipex(argv, env, argc);
	if (!pipex.pids)
		return (1);
	exit_code = ft_pipex(&pipex, argv);
	if (exit_code == -1)
		return (1);
	return (exit_code);
}
