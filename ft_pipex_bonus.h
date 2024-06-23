/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pipex_bonus.h                                   :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 17:44:17 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/01/11 21:24:24 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_BONUS_H
# define FT_PIPEX_BONUS_H

# include <stdbool.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct t_pipex
{
	char	**env;
	char	*outfile;
	char	*infile;
	char	*limiter;
	int		**pipes;
	int		*pids;
	int		cmdc;
	int		flag;
}	t_pipex;

t_pipex	init_pipex(char **argv, char **env, int argc);

void	err_cleanup(char *error, t_pipex *pipex, bool print_err);
void	err_exit(char *error, int code, t_pipex *pipex, bool cleanup);
void	cmd_not_found(char *cmd);
void	close_pipes_arr(int **pipes, int i, bool clean);

int		**mk_pipes(int n);

char	*get_cmd_path(char **env, char *cmd_name);
char	**mk_args(char **env, char *cmd);

#endif
