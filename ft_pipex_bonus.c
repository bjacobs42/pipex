/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 21:58:59 by bjacobs       #+#    #+#                 */
/*   Updated: 2024/06/24 00:03:43 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"
#include "libft.h"
#include <sys/wait.h>

static int	here_doc(t_pipex *pipex)
{
	char	*s;
	char	*tmp;
	char	buff[421];
	int		bread;

	s = NULL;
	write(STDOUT_FILENO, "> ", 2);
	bread = read(STDIN_FILENO, buff, 420);
	while (ft_strncmp(buff, pipex->limiter, ft_strlen(pipex->limiter)) != 0)
	{
		buff[bread] = '\0';
		tmp = ft_strjoin(s, buff);
		free(s);
		s = tmp;
		write(STDOUT_FILENO, "> ", 2);
		bread = read(STDIN_FILENO, buff, 420);
	}
	write(pipex->pipes[0][1], s, ft_strlen(s));
	return (free(s), 0);
}

static void	change_stdio(t_pipex *pipex, int i)
{
	int	fd;

	if (i == 0 && !pipex->limiter)
		fd = open(pipex->infile, O_RDONLY);
	else
		fd = pipex->pipes[i][0];
	if (fd == -1)
		err_exit(pipex->infile, EXIT_FAILURE, pipex, true);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (i + 1 >= pipex->cmdc)
	{
		if (pipex->limiter)
			fd = open(pipex->outfile, O_CREAT | O_APPEND | O_WRONLY, 0664);
		else
			fd = open(pipex->outfile, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	}
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
	close_pipes_arr(pipex->pipes, pipex->cmdc, true);
	execve(exec_args[0], exec_args, pipex->env);
	exit(1);
}

static int	ft_pipex(t_pipex *pipex, char **argv)
{
	int	status;
	int	i;

	i = 0;
	if (pipex->limiter)
		here_doc(pipex);
	while (i < pipex->cmdc)
	{
		pipex->pids[i] = fork();
		if (pipex->pids[i] == -1)
			return (err_cleanup("fork error", pipex, true), -1);
		if (pipex->pids[i] == 0)
			exec_cmd(pipex, i, argv[i + 2]);
		i++;
	}
	close_pipes_arr(pipex->pipes, pipex->cmdc, true);
	i = 0;
	while (i < pipex->cmdc)
		waitpid(pipex->pids[i++], &status, 0);
	return (free(pipex->pids), status / 256);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		exit_code;

	if (argc > 1 && ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6)
		return (ft_putendl_fd("less than 5 arguments", STDERR_FILENO), 0);
	if (argc < 5)
		return (ft_putendl_fd("less than 4 arguments", STDERR_FILENO), 0);
	pipex = init_pipex(argv, env, argc);
	if (!pipex.pids || !pipex.pipes)
		return (1);
	if (pipex.limiter)
		argv++;
	exit_code = ft_pipex(&pipex, argv);
	if (exit_code == -1)
		return (1);
	if (pipex.limiter)
		free(pipex.limiter);
	return (exit_code);
}
