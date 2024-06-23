/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 02:45:28 by bjacobs           #+#    #+#             */
/*   Updated: 2023/01/18 15:19:53 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
#include "libft.h"

static char	*get_env_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_substr(env[i], 5, ft_strlen(env[i])));
		i++;
	}
	return (NULL);
}

static char	*search_path(char *path, char *cmd_name)
{
	char	**bins;
	char	*tmp;
	int		i;

	bins = ft_split(path, ':');
	if (!bins)
		return (NULL);
	i = 0;
	while (bins[i])
	{
		tmp = ft_strjoin(bins[i], "/");
		if (!tmp)
			return (ft_clear_arr(bins), NULL);
		free(bins[i]);
		bins[i] = tmp;
		tmp = ft_strjoin(bins[i], cmd_name);
		if (!tmp)
			return (ft_clear_arr(bins), NULL);
		if (!access(tmp, F_OK))
			return (ft_clear_arr(bins), tmp);
		free(tmp);
		i++;
	}
	return (ft_clear_arr(bins), cmd_name);
}

char	*get_cmd_path(char **env, char *cmd_name)
{
	char	*env_path;
	char	*cmd_path;

	if (!cmd_name)
		return (NULL);
	if (ft_strncmp("./", cmd_name, 2) == 0)
		return (cmd_name);
	env_path = get_env_path(env);
	if (!env_path)
		return (cmd_name);
	cmd_path = search_path(env_path, cmd_name);
	if (!cmd_path)
		return (free(env_path), NULL);
	return (free(env_path), cmd_path);
}
